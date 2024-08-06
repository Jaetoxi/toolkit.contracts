con_bbp=bbptest1
tnew $con_bbp
tset $con_bbp amaxapplybbp

tcli set account permission $con_bbp active --add-code

con_bps=amaxapplybps
tnew $con_bps
tset $con_bps amaxapplybps


# tnew bbpadmin
tpush $con_bbp init '["bbpadmin","AM7n5TBaSnZLkrn8yYk54YveYoyQujJaMGK546gPze1Vy5MsM3S6","'$con_bps'"]' -p $con_bbp
tpush $con_bps init '["bbpadmin","'$con_bbp'"]' -p $con_bps
tcli get table $con_bbp $con_bbp "global"
tcli get table $con_bps $con_bps "global"


bbp_owner1=bbp.owner1
tnew $bbp_owner1

bbp_owner2=bbp.owner2
tnew $bbp_owner2

plan_id=1
bbp_quota=24
tpush $con_bbp setplan '["'$plan_id'","'$bbp_quota'",1,[[["8,AMAX", "amax.token"], "1.00000000 AMAX"]], []]' -p $con_bbp


tcli get table amax.ntoken ad "accounts"
plan_id=2
bbp_quota=3
tpush $con_bbp setplan '["'$plan_id'","'$bbp_quota'", 1, [[["8,AMAX","amax.token"],"1.00000000 AMAX"]],[[[[1,0],"amax.ntoken"],[1,[1,0]]]]]' -p $con_bbp
plan_id=3
bbp_quota=3
tpush $con_bbp setplan '["'$plan_id'","'$bbp_quota'",1, [[["8,AMAX", "amax.token"],"1.00000000 AMAX"], [["6,MUSDT", "amax.mtoken"], "1.000000 MUSDT"]], []]' -p $con_bbp
tcli get table $con_bbp $con_bbp "plans"
plan_id=4
bbp_quota=3
tpush $con_bbp setplan '["'$plan_id'","'$bbp_quota'",3, [[["8,AMAX", "amax.token"],"1.00000000 AMAX"], [["6,MUSDT", "amax.mtoken"], "1.000000 MUSDT"]], []]' -p $con_bbp


tnew bbpvote11
tnew bbpvote21
tnew bbpvote31

tpush $con_bbp addvoters '{"voters":["bbpvote11","bbpvote21","bbpvote31"] }' -p $con_bbp
tcli get table $con_bbp $con_bbp "voters"


tcli get table $con_bbp $con_bbp "global"

tpush $con_bbp applybbp '["'$bbp_owner1'",1,"logo_uri","org_name", "org_info","mail","manifesto","url",1232, null]' -p $bbp_owner1
tcli get table $con_bbp $con_bbp "bbps"

tpush $con_bbp applybbp '["'$bbp_owner2'",4,"logo_uri","org_name", "org_info","mail","manifesto","url",1232, null]' -p $bbp_owner2

tcli push action amax.token  transfer '["amax", "'$bbp_owner1'", "10.00000000 AMAX", ""]' -p amax

tcli push action amax.token  transfer '["'$bbp_owner1'", "'$con_bbp'", "1.00001000 AMAX", ""]' -p $bbp_owner1

tcli get table $con_bbp $con_bbp "bbps"

tcli push action  $con_bbp tsetvoteridx '[18]' -p $con_bbp


voter=bbpvote11
tpush amax updateauth '{"account":"'$voter'","permission":"active","parent":"owner","auth":{"threshold":1,"keys":[],"waits":[],"accounts":[{"weight":1,"permission":{"actor":"'$con_bbp'","permission":"active"}}]}}' -p $voter


