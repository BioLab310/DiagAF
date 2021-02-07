#!/bin/bash
for((i=1;i<=1;i++))
do
	> ./EdCondirm_${i}
	for((j=1;j<=15;j++))
	do
		./PairEdConfirm -r data_${i}_ed_${j} -e $j >> ./EdCondirm_${i}
	done
done
