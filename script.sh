i=0
while [ $i -ne 1000 ]
do
        i=$(($i+1))
       curl http://www.boredapi.com/api/activity/  | python3 -c "import sys, json; print(json.load(sys.stdin)['activity'])">> jobs 
done
