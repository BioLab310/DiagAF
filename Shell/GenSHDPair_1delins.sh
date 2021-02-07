#!/bin/bash
for((i=1;i<=1;i++))
do
	> ./EdDistribution/EdDistribution_${i}
	for((j=1;j<=15;j++))
	do
		./GenSHDPair_1delins data_${i} $j >> ./EdDistribution/EdDistribution_${i}
	done
done
