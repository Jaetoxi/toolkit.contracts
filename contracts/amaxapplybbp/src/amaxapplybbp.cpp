#include <amaxapplybbp/amaxapplybbp.hpp>

#include <math.hpp>
#include <utils.hpp>
#include "mdao.info/mdao.info.db.hpp"

namespace amax {


namespace db {

    template<typename table, typename Lambda>
    inline void set(table &tbl,  typename table::const_iterator& itr, const eosio::name& emplaced_payer,
            const eosio::name& modified_payer, Lambda&& setter )
   {
        if (itr == tbl.end()) {
            tbl.emplace(emplaced_payer, [&]( auto& p ) {
               setter(p, true);
            });
        } else {
            tbl.modify(itr, modified_payer, [&]( auto& p ) {
               setter(p, false);
            });
        }
    }

    template<typename table, typename Lambda>
    inline void set(table &tbl,  typename table::const_iterator& itr, const eosio::name& emplaced_payer,
               Lambda&& setter )
   {
      set(tbl, itr, emplaced_payer, eosio::same_payer, setter);
   }

}// namespace db


using namespace std;
using namespace amax;
using namespace mdao;



   void amaxapplybbp::applybbp(
                  const name&      owner,
                  const uint32_t&   plan_id,
                  const string&     logo_uri,
                  const string&     org_name,
                  const string&     org_info,
                  const string&     email,
                  const string&     manifesto,
                  const string&     url,
                  const uint32_t&   location,
                  const std::optional<eosio::public_key> pub_mkey){
      require_auth( owner );
      _set_producer(owner, plan_id, logo_uri, org_name, org_info, email, manifesto, url, location, pub_mkey);
   }

   // void amaxapplybbp::updatebbp(const name& owner,
   //                            const uint32_t& plan_id,
   //                            const string& logo_uri,
   //                            const string& org_name,
   //                            const string& org_info,
   //                            const name& dao_code,
   //                            const string& reward_shared_plan,
   //                            const string& manifesto,
   //                            const string& issuance_plan){

   //    require_auth( owner );
   //    auto bbp_itr = _producer_tbl.find(owner.value);
   //    CHECKC( bbp_itr != _producer_tbl.end(),err::RECORD_EXISTING,"Application submitted:" + owner.to_string())

   //    _set_producer(owner,logo_uri,org_name,org_info,dao_code,reward_shared_plan,manifesto,issuance_plan);
   // }

   void amaxapplybbp::_set_producer(
                  const name&      owner,
                  const uint32_t&   plan_id,
                  const string&     logo_uri,
                  const string&     org_name,
                  const string&     org_info,
                  const string&     email,
                  const string&     manifesto,
                  const string&     url,
                  const uint32_t&   location,
                  const std::optional<eosio::public_key> pub_mkey){
      auto plan_itr = _plan_t.find(plan_id);
      CHECKC( plan_itr != _plan_t.end(), err::RECORD_NOT_FOUND, "plan not found symbol" )

      CHECKC( logo_uri.size() <= MAX_LOGO_SIZE ,err::OVERSIZED ,"logo size must be <= " + to_string(MAX_LOGO_SIZE))
      CHECKC( org_name.size() <= MAX_TITLE_SIZE ,err::OVERSIZED ,"org_name size must be <= " + to_string(MAX_TITLE_SIZE))
      CHECKC( org_info.size() <= MAX_TITLE_SIZE ,err::OVERSIZED ,"org_info size must be <= " + to_string(MAX_TITLE_SIZE))

      auto bbp_itr = _bbp_t.find(owner.value);
      if(bbp_itr !=  _bbp_t.end() && (bbp_itr->status != ProducerStatus::INIT)){
         CHECKC( false, err::STATUS_ERROR, "Information cant been changed")
      } 

      if(bbp_itr ==_bbp_t.end()){
         //update plan
         db::set(_plan_t, plan_itr, _self, [&]( auto& p, bool is_new ) {
            p.required_bbp_quota =  plan_itr->required_bbp_quota + 1;
         });
      }


      db::set(_bbp_t, bbp_itr, _self, [&]( auto& p, bool is_new ) {
         if (is_new) {
            p.owner        = owner;
            p.created_at   = current_time_point();
            p.status       = ProducerStatus::INIT;
         }
         p.plan_id               = plan_id;
         p.logo_uri              = logo_uri;
         p.org_name              = org_name;
         p.org_info              = org_info;
         p.manifesto             = manifesto;
         p.email                 = email;
         p.url                   = url;
         p.location              = location;
         p.updated_at            = current_time_point();
         if(pub_mkey.has_value()) 
            p.mkey               = pub_mkey.value();
         else 
            p.mkey              = _gstate.bbp_mkey;
      });
   }

   [[eosio::on_notify("amax.mtoken::transfer")]]
   void amaxapplybbp::onrecv_mtoken( name from, name to, asset quantity, string memo ){

   }

   [[eosio::on_notify("amax.token::transfer")]]
   void amaxapplybbp::onrecv_amax( name from, name to, asset quantity, string memo ){
      if (from == get_self()) { return; }
      if (to != _self) { return; }
      auto from_bank = get_first_receiver();

      _on_receive_asset(from, to, from_bank, quantity, nasset{0, nsymbol{1, 1}});
   }

   void amaxapplybbp::_on_receive_asset(const name& from, const name& to, const name& from_bank,
          const asset& quantity, const nasset& nquantity) {
         
      auto bbp_itr = _bbp_t.find(from.value);
      CHECKC( bbp_itr != _bbp_t.end(), err::STATUS_ERROR, "bbp not found:" + from.to_string())
      //进行中
      CHECKC( bbp_itr->status == ProducerStatus::INIT, err::STATUS_ERROR, "Information cant been changed")
      CHECKC( quantity.symbol == AMAX_SYMBOL, err::SYMBOL_MISMATCH, "Invalid symbol" )

      auto plan_itr = _plan_t.find(bbp_itr->plan_id);
      CHECKC( plan_itr != _plan_t.end(), err::RECORD_NOT_FOUND, "plan not found symbol" )

      auto quants = bbp_itr->quants;
      auto nfts = bbp_itr->nfts;

      if(quantity.amount > 0){
         const auto& symb = extended_symbol(quantity.symbol, from_bank);
         CHECKC( plan_itr->quants.find(symb) != plan_itr->quants.end(), err::SYMBOL_MISMATCH, "Invalid symbol" );

         //check project symbol required
         auto plan_quants = plan_itr->quants;
         CHECKC(plan_quants.count(symb) > 0, err::RECORD_NOT_FOUND, "plan not found symbol: ")
         if(quants.count(symb) == 0){ 
            quants[symb] = quantity;
         } else {
            quants[symb] += quantity;
         }
      } else if(nquantity.amount > 0) {
         const auto& symb = extended_nsymbol(nquantity.symbol, from_bank);
         CHECKC( plan_itr->nfts.find(symb) != plan_itr->nfts.end(), err::SYMBOL_MISMATCH, "Invalid symbol" );

         //check project symbol required
         auto plan_nfts = plan_itr->nfts;
         CHECKC(plan_nfts.count(symb) > 0, err::RECORD_NOT_FOUND, "plan not found symbol: ")
         if(nfts.count(symb) == 0){ 
            nfts[symb] = nquantity;
         } else {
            nfts[symb] += nquantity;
         }
      } else {
         CHECKC(false, err::PARAM_ERROR, "Invalid param: " + quantity.to_string())
      }
   
      auto check_ret = _check_request_quant(plan_itr->quants, quants, plan_itr->min_sum_quant);
      auto nft_check_ret =  _check_request_nft(plan_itr->nfts, nfts);
      if( check_ret == CHECK_UNFINISHED || nft_check_ret == CHECK_UNFINISHED ) {
         db::set(_bbp_t, bbp_itr, _self, [&]( auto& p, bool is_new ) {
            p.quants = quants;
            p.nfts = bbp_itr->nfts;
            p.updated_at = current_time_point();
         });
         return;
      }
      
      //paid finished
      db::set(_bbp_t, bbp_itr, _self, [&]( auto& p, bool is_new ) {
         p.quants = quants;
         // p.nfts = bbp_itr->nfts;
         if(check_ret == CHECK_FINISHED && nft_check_ret == CHECK_FINISHED){
            p.status = ProducerStatus::FINISHED;
         } else {
            p.status = ProducerStatus::REFUNDING;
         }
         p.updated_at = current_time_point();
      });
      //allocate a partner
      _gstate.voter_idx++;
      auto voter_itr = _voter_t.find(_gstate.voter_idx);
      CHECKC( voter_itr != _voter_t.end(), err::RECORD_NOT_FOUND, "voter not found" )
      db::set(_voter_t, voter_itr, _self, [&]( auto& p, bool is_new ) {
         p.bbp_account = from;
         p.updated_at = current_time_point();
      });

      //todo: transfer to owner
      _call_set_producer(from, from_bank, voter_itr->voter_account, quantity);

      db::set(_plan_t, plan_itr, _self, [&]( auto& p, bool is_new ) {
         p.finish_bbp_quota = plan_itr->finish_bbp_quota + 1;
      });
   }

   void amaxapplybbp::_call_set_producer(
            const name& owner, const name& from_bank,
            const name& voter_account, const asset& quantity){
      //transfer to voter
      TRANSFER( from_bank, voter_account, quantity, "bbp");

   
      //add producer
      auto itr = _bbp_t.find(owner.value);
      CHECKC( itr !=  _bbp_t.end(),err::RECORD_NOT_FOUND ,"bbp not found:" + owner.to_string())
      amaxapplybps::addproducer_action addproducer_act(_gstate.bps_contract, {get_self(), "active"_n});
      addproducer_act.send(get_self(), owner, itr->mkey, itr->url, itr->location, 0);

      //CHECKC(false, err::STATUS_ERROR, "Invalid status->add producer")
      //add vote 
      auto vote_quant = asset(quantity.amount/10000, VOTE_SYMBOL);
      amax_system::addvote_action add_vote_act(_gstate.sys_contract, {voter_account, "active"_n});
      add_vote_act.send(voter_account, vote_quant);

      //vote 
      amax_system::vote_action vote_act(_gstate.sys_contract, {voter_account, "active"_n});
      std::vector<name> producers;
      producers.push_back(owner);
      vote_act.send( voter_account,producers);
   }
   
   [[eosio::on_notify("amax.ntoken::transfer")]]
   void amaxapplybbp::onrecv_nft( name from, name to, nasset quantity, string memo ){
      if (from == get_self()) { return; }
      if (to != _self) { return; }
      
      auto from_bank = get_first_receiver();
      
      _on_receive_asset(from, to, from_bank, asset(0, AMAX_SYMBOL), quantity );

   }

}//namespace amax
