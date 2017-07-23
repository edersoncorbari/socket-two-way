#!/bin/sh

run="python2 select.py"
count=0

while [ $count -lt 1000 ]
do
   ${run} 
   echo "Total iteraction: $count"
   count=`expr $count + 1`
done

