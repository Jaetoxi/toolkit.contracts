#include <amax.applybp.hpp>
#include <amaxapplybps/amaxapplybps.hpp>

#include <math.hpp>
#include <utils.hpp>

namespace amax {

using namespace std;
using namespace amax;

#define CHECKC(exp, code, msg) \
   { if (!(exp)) eosio::check(false, string("[[") + to_string((int)code) + string("]] ")  \
                                    + string("[[") + _self.to_string() + string("]] ") + msg); }

   void amaxapplybps::addproducer(const name& submiter,
                              const name& owner,
                              const string& logo_uri,
                              const string& org_name,
                              const string& org_info,
                              const name& dao_code,
                              const string& reward_shared_plan,
                              const string& manifesto,
                              const string& issuance_plan){
      require_auth( submiter );
      CHECKC( submiter == _gstate.admin || submiter == _gstate.bbp_contract,err::NO_AUTH,
               "Missing required authority of admin" )
      amax_applybp::addproducer_action addproducer_act( _gstate.bpapply_contract, {_self, "active"_n} );
      addproducer_act.send(_self,  owner, logo_uri, org_name, org_info, dao_code, reward_shared_plan, manifesto, issuance_plan);
   }

}//namespace amax
