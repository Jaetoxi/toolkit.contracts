con_bbp=bbp2
tnew $con_bbp
tset $con_bbp amaxapplybbp

con_bps=bps2
tnew $con_bps
tset $con_bps amaxapplybps



# tnew bbpadmin
tpush $con_bbp init '["bbpadmin","AM7n5TBaSnZLkrn8yYk54YveYoyQujJaMGK546gPze1Vy5MsM3S6","'$con_bps'"]' -p $con_bbp
tpush $con_bps init '["bbpadmin","'$con_bbp'"]' -p $con_bps
tcli get table $con_bps $con_bps "global"


bbp_owner1=bbp.owner1
tnew $bbp_owner1

plan_id=1;
bbp_quota=240

tpush $con_bbp setplan1 '["'$plan_id'","'$bbp_quota'" ]' -p $con_bbp
tcli get table $con_bbp $con_bbp "plans"

tnew bbpvote1
tnew bbpvote2
tnew bbpvote3

tpush $con_bbp addvoters '{"voters":["bbpvote2","bbpvote2","bbpvote3"] }' -p $con_bbp
tcli get table $con_bbp $con_bbp "voterlist"


tcli get table $con_bbp $con_bbp "global"

tpush $con_bbp applybbp '["'$bbp_owner1'",1,"logo_uri","org_name", "org_info","daocode1","reward_shared_plan","manifesto","issuance_plan","url",1232, null]' -p $bbp_owner1
tcli get table $con_bbp $con_bbp "bbps"

tcli push action amax.token  transfer '["amax", "'$bbp_owner1'", "10.00000000 AMAX", ""]' -p amax

tcli push action amax.token  transfer '["'$bbp_owner1'", "'$con_bbp'", "1.00001000 AMAX", ""]' -p $bbp_owner1

tcli get table $con_bbp $con_bbp "bbps"

tcli push action  $con_bbp tsetvoteridx '[18]' -p $con_bbp

