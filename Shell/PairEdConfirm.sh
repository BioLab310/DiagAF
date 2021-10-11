#!/bin/bash
for((i=1;i<=N;i++))
do
	> ./EdCondirm_${i}
	for((j=1;j<=15;j++))
	do
		./PairEdConfirm -r ${data_1toN_with_different_T} -e $j >> ./EdCondirm_${i}
	done
done
