#!/bin/bash
if [ ! -d EdDistribution  ];then
  mkdir EdDistribution
else
  echo dir exist
fi
for((i=1;i<=1;i++))
do
	> ./EdDistribution/EdDistribution_${i}
	for((j=1;j<=15;j++))
	do
		./GenPair1delins read_50_100L $j >> ./EdDistribution/EdDistribution_${i}
	done
done
