#! /bin/bash
echo "file count : " $#

for i in $* 
do
#sed -i 's/sendHumaxApplicationLoadedSignal/sendHbbTVBIApplicationLoadedSignal/g' $i
#sed -i 's/sendHumaxApplicationUnloadedSignal/sendHbbTVBIApplicationUnloadedSignal/g' $i
sed -i 's/\t/    /g' $i
done
echo "replacing file completed"
