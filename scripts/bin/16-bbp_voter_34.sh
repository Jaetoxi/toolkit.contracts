votequant=600.0000
mpush="amcli -u http://sh-amnod.vmi.amax.dev:18188 push action"
bbp_array=()
while read line; do
  bbp_array+=("$line")
done < ./13-bbp_list_34.txt

voter_array=()
while read line; do
  voter_array+=("$line")
done < ./13-bbp-voter_34.txt 
mpkey=""

for i in "${!voter_array[@]}"; do
    voter=${voter_array[$i]}
    bbps=${bbp_array[$i]}
    $mpush amaxapplybps addproducer '["'amaxapplybps'","'$voter'","'$mpkey'","",0, 0]' -p amaxapplybps
    $mpush amax addvote '["'$voter'", "'$votequant' VOTE"]' -p $voter
    $mpush amax vote '["'$voter'", "['$bbps']"]' -p $voter
done