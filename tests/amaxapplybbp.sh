con_bbp=bbp1
tnew $con_bbp
tset $con_bbp amaxapplybbp

con_bps=bps1
tnew $con_bps
tset $con_bps amaxapplybps

tpush $con_bbp

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

tnew bbpadmin
tpush $con_bbp init '["bbpadmin","AM7n5TBaSnZLkrn8yYk54YveYoyQujJaMGK546gPze1Vy5MsM3S6","'$con_bps'"]' -p $con_bbp

tcli get table $con_bbp $con_bbp "global"

tpush $con_bbp applybbp '["'$bbp_owner1'",1,"logo_uri","org_name", "org_info","daocode1","reward_shared_plan","manifesto","issuance_plan","url",1232, null]' -p $bbp_owner1
tcli get table $con_bbp $con_bbp "bbps"

tcli push action amax.token  transfer '["amax", "'$coin_bbp'", "1.00000000 AMAX", ""]' -p $bbp_owner1

tcli push action amax.token  transfer '["'$bbp_owner1'", "'$coin_bbp'", "1.00000000 AMAX", ""]' -p $bbp_owner1


