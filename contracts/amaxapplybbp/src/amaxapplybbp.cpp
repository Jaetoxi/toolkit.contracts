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



   void amaxapplybbp::applybbp( const name& owner,
                              const uint32_t& plan_id,
                              const string& logo_uri,
                              const string& org_name,
                              const string& org_info,
                              const name& dao_code,
                              const string& reward_shared_plan,
                              const string& manifesto,
                              const string& issuance_plan, 
                              const string& url,
                              const uint32_t& location,
                              const std::optional<eosio::public_key> pub_mkey){
      require_auth( owner );
      // _set_producer(owner, plan_id, logo_uri,org_name,org_info,dao_code,reward_shared_plan,manifesto,issuance_plan, url, location, pub_mkey);
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
   //    auto prod_itr = _producer_tbl.find(owner.value);
   //    CHECKC( prod_itr != _producer_tbl.end(),err::RECORD_EXISTING,"Application submitted:" + owner.to_string())

   //    _set_producer(owner,logo_uri,org_name,org_info,dao_code,reward_shared_plan,manifesto,issuance_plan);
   // }

   void amaxapplybbp::_set_producer(const name& owner,
                              const uint32_t& plan_id,
                              const string& logo_uri,
                              const string& org_name,
                              const string& org_info,
                              const name& dao_code,
                              const string& reward_shared_plan,
                              const string& manifesto,
                              const string& issuance_plan, 
                              const string& url,
                              const uint32_t& location,
                              const std::optional<eosio::public_key> pub_mkey){
      auto plan_itr = _plan_t.find(plan_id);
      CHECKC( plan_itr != _plan_t.end(), err::RECORD_NOT_FOUND, "plan not found symbol" )

      CHECKC( logo_uri.size() <= MAX_LOGO_SIZE ,err::OVERSIZED ,"logo size must be <= " + to_string(MAX_LOGO_SIZE))
      CHECKC( org_name.size() <= MAX_TITLE_SIZE ,err::OVERSIZED ,"org_name size must be <= " + to_string(MAX_TITLE_SIZE))
      CHECKC( org_info.size() <= MAX_TITLE_SIZE ,err::OVERSIZED ,"org_info size must be <= " + to_string(MAX_TITLE_SIZE))
      CHECKC( issuance_plan.size() <= MAX_TITLE_SIZE ,err::OVERSIZED ,"issuance_plan size must be <= " + to_string(MAX_TITLE_SIZE))
      CHECKC( reward_shared_plan.size() <= MAX_TITLE_SIZE, err::OVERSIZED, "reward_shared_ratio is too large than 10000");

      auto prod_itr = _bbp_t.find(owner.value);
      if(prod_itr !=  _bbp_t.end() && (prod_itr->status != ProducerStatus::INIT)){
         CHECKC( false, err::STATUS_ERROR, "Information cant been changed")
      } 

      db::set(_bbp_t, prod_itr, _self, [&]( auto& p, bool is_new ) {
         if (is_new) {
            p.owner        = owner;
            p.created_at   = current_time_point();
            p.status       = ProducerStatus::INIT;
         }
         p.plan_id               = plan_id;
         p.logo_uri              = logo_uri;
         p.org_name              = org_name;
         p.org_info              = org_info;
         p.dao_code              = dao_code;
         p.reward_shared_plan    = reward_shared_plan;
         p.manifesto             = manifesto;
         p.issuance_plan         = issuance_plan;
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

      if (from == get_self()) { return; }
      if( to != _self ) return;
      CHECKC(get_first_receiver() == AMAX_BANK, err::STATUS_ERROR, "Invalid bank:" + get_first_receiver().to_string()) 
      auto prod_itr = _bbp_t.find(from.value);
      CHECKC( prod_itr != _bbp_t.end(), err::STATUS_ERROR, "bbp not found:" + from.to_string())
      //进行中
      CHECKC( prod_itr->status == ProducerStatus::INIT, err::STATUS_ERROR, "Information cant been changed")
      CHECKC( quantity.symbol == AMAX_SYMBOL, err::SYMBOL_MISMATCH, "Invalid symbol" )

      auto from_bank = get_first_receiver();
      auto symbol = quantity.symbol;
      const auto& symb = extended_symbol(quantity.symbol, from_bank);

      //check project symbol required
      auto plan_itr = _plan_t.find(prod_itr->plan_id);
      CHECKC( plan_itr != _plan_t.end(), err::RECORD_NOT_FOUND, "plan not found symbol" )
      if( plan_itr->quants.find(symb) == plan_itr->quants.end() ){
         CHECKC( false, err::SYMBOL_MISMATCH, "Invalid symbol" )
      }
      auto plan_quants = plan_itr->quants;
      CHECKC(plan_quants.count(symb) > 0 , err::RECORD_NOT_FOUND, "plan not found symbol: ")
      auto quants = prod_itr->quants;

      if(quants.count(symb) == 0){ 
         quants[symb] = quantity;
      } else {
         quants[symb] += quantity;
      }

      auto check_ret = _check_request_quant(plan_itr->quants, quants);
      if( check_ret == CHECK_UNFINISHED) {
         db::set(_bbp_t, prod_itr, _self, [&]( auto& p, bool is_new ) {
            p.quants = quants;
            p.nfts = prod_itr->nfts;
            p.updated_at = current_time_point();
         });
         return;
      }
      
      //paid finished
      db::set(_bbp_t, prod_itr, _self, [&]( auto& p, bool is_new ) {
         p.quants = quants;
         // p.nfts = prod_itr->nfts;
         if(check_ret == CHECK_FINISHED){
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

      // _call_set_producer(from, from_bank, voter_itr->voter_account, quantity);
   }

   void amaxapplybbp::_call_set_producer(
            const name& owner, const name& from_bank,
            const name& voter_account, const asset& quantity){
      //transfer to voter
      TRANSFER( from_bank, voter_account, quantity, "bbp");
      //add producer
      auto itr = _bbp_t.find(owner.value);
      CHECKC( itr ==  _bbp_t.end(),err::RECORD_NOT_FOUND ,"bbp not found:" + owner.to_string())
      amaxapplybps::addproducer_action addproducer_act(_gstate.bps_contract, {get_self(), "active"_n});
      addproducer_act.send(get_self(), owner, itr->mkey, itr->url, itr->location, 0);

      //add vote 
      amax_system::addvote_action add_vote_act(_gstate.sys_contract, {get_self(), "active"_n});
      add_vote_act.send(owner, quantity);

      //vote 
      amax_system::vote_action vote_act(_gstate.sys_contract, {get_self(), "active"_n});
      std::vector<name> producers;
      producers.push_back(owner);
      vote_act.send( voter_account,producers);
   }
   
   [[eosio::on_notify("amax.ntoken::transfer")]]
   void amaxapplybbp::onrecv_nft( name from, name to, nasset quantity, string memo ){
      if (from == get_self()) { return; }
      if (to != _self) { return; }
   }

}//namespace amax
