#!/bin/bash
if [ ! -d EdDistribution  ];then
  mkdir EdDistribution
else
  echo dir exist
fi
for((i=1;i<=N;i++))
do
	> ./EdDistribution/EdDistribution_${i}
	for((j=1;j<=15;j++))
	do
		${GenDataMethod} ${data_1toN} ${Threhold} >> ./EdDistribution/EdDistribution_${i}
	done
done
