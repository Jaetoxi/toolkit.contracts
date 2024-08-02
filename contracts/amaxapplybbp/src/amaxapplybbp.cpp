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

#define CHECKC(exp, code, msg) \
   { if (!(exp)) eosio::check(false, string("[[") + to_string((int)code) + string("]] ")  \
                                    + string("[[") + _self.to_string() + string("]] ") + msg); }


   void amaxapplybbp::applybbp( const name& owner,
                              const uint32_t& plan_id,
                              const string& logo_uri,
                              const string& org_name,
                              const string& org_info,
                              const name& dao_code,
                              const string& reward_shared_plan,
                              const string& manifesto,
                              const string& issuance_plan){
      require_auth( owner );
      _set_producer(owner, plan_id, logo_uri,org_name,org_info,dao_code,reward_shared_plan,manifesto,issuance_plan);
   }

   void amaxapplybbp::updatebbp(const name& owner,
                              const uint32_t& plan_id,
                              const string& logo_uri,
                              const string& org_name,
                              const string& org_info,
                              const name& dao_code,
                              const string& reward_shared_plan,
                              const string& manifesto,
                              const string& issuance_plan){

      require_auth( owner );
      auto prod_itr = _producer_tbl.find(owner.value);
      CHECKC( prod_itr != _producer_tbl.end(),err::RECORD_EXISTING,"Application submitted:" + owner.to_string())

      _set_producer(owner,logo_uri,org_name,org_info,dao_code,reward_shared_plan,manifesto,issuance_plan);
   }

   void amaxapplybbp::_set_producer(const name& owner,
                              const uint32_t& plan_id,
                              const string& logo_uri,
                              const string& org_name,
                              const string& org_info,
                              const name& dao_code,
                              const string& reward_shared_plan,
                              const string& manifesto,
                              const string& issuance_plan){
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
            p.owner        =  owner;
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
      if( get_first_receiver() != MT_BANK ) return;
      auto prod_itr = _bbp_t.find(owner.value);
   
      CHECKC( prod_itr !=  _bbp_t.end(), err::STATUS_ERROR, "Information cant been changed")
      //进行中
      CHECK((prod_itr->status != ProducerStatus::INIT))
      CHECKC( quantity.symbol == AMAX_SYMBOL, err::SYMBOL_INVALID, "Invalid symbol" )

      auto from_bank = get_first_receiver();
      auto symbol = quantity.symbol;
      const auto& symb = extended_symbol(quantity.symbol, from_bank);

      //check project symbol required
      CHECKC( prod_itr->plan_id != 0, err::SYMBOL_INVALID, "Invalid symbol" )
      auto plan_itr = _plan_tbl.find(prod_itr->plan_id);
      CHECKC( plan_itr != _plan_tbl.end(), err::RECORD_NOT_FOUND, "plan not found symbol" )
      if( plan_itr->quants.find(symb) == plan_itr->quants.end() ){
         CHECKC( false, err::SYMBOL_INVALID, "Invalid symbol" )
      }
      auto require_qunt = plan_itr->quants[symb];
      if(prod_itr->quants[symb] == null) {
         prod_itr->quants[symb] = quantity;
      } else {
         prod_itr->quants[symb] += quantity;
      }
      if(!(_check_request_quant(plan_itr->quants, prod_itr->quants) &&
      _check_request_nft(plan_itr->nfts, prod_itr->nfts))) {
         db::set(_bbp_t, prod_itr, _self, [&]( auto& p, bool is_new ) {
            p.quants = prod_itr->quants;
            p.nfts = prod_itr->nfts;
            p.updated_at = current_time_point();
         });
         return;
      }
      //paid finished
      db::set(_bbp_t, prod_itr, _self, [&]( auto& p, bool is_new ) {
         p.quants = prod_itr->quants;
         p.nfts = prod_itr->nfts;
         p.status = ProducerStatus::APPROVED;
         p.updated_at = current_time_point();
      });
      //allocate a partner
      _gstate.voter_idx++;
      auto voter_itr = _voter_t.find(_gstate.voter_idx);
      CHECKC( voter_itr != _voter_t.end(), err::RECORD_NOT_FOUND, "voter not found" )
      db::set(_voter_t, voter_itr, _self, [&]( auto& p, bool is_new ) {
         p.bbp_account = owner;
         p.updated_at = current_time_point();
      });

      //todo: transfer to owner
      TRANSFER( from_bank, voter_itr->voter_account, require_qunt, "bbp");

      _set_producer(owenr);
   }

   void amaxapplybbp::_set_producer(const name& owner){
      auto prod_itr = _bbp_t.find(owner.value);
      CHECKC( prod_itr ==  _bbp_t.end(),err::RECORD_NOT_FOUND ,"bbp not found:" + owner.to_string())

   }

   boolean amaxapplybbp::_check_request_quant(
                     const& map<extend_symbol, asset>       plan_quants,
                     const& map<extend_symbol, asset>       quants) {
      for(auto& [symb, quant] : plan_quants) {
         if(quants.find(symb) == quants.end()) {
            return false;
         }
         if(quants[symb] < quant) {
            return false;  
         }
      }
      return true;
   }

   boolean amaxapplybbp::_check_request_nft(
                     const& map<extended_nsymbol, nasset>       plan_nfts,
                     const& map<extended_nsymbol, nasset>       nfts) {
      for(auto& [symb, quant] : plan_nfts) {
         if(quants.find(symb) == nfts.end()) {
            return false;
         }
         if(quants[symb] < nfts) {
            return false;  
         }
      }
      return true;
   }

   
   [[eosio::on_notify("amax.ntoken::transfer")]]
   void amaxapplybbp::onrecv_nft( name from, name to, nasset quantity, string memo ){
      if (from == get_self()) { return; }
      if (to != _self) { return; }
   }


}//namespace amax
