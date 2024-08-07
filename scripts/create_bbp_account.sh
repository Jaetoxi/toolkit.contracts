#!/bin/bash
cat voter.txt | while IFS= read -r line; do
  # 在这里对每一行的内容做操作
    echo "-----------create account: $line ------------"
    acct=$line
    creator=bbp
    owner=amax.dao@active
    activer=bbpadmin@active
    amcli -u http://sh-amnod.vmi.amax.dev:18188 system newaccount --stake-net "0.005000 AMAX" --stake-cpu "0.005000 AMAX" --buy-ram-kbytes 4 $creator $acct $owner $activer -p bbp
done