#!/bin/bash
k=1
for((m=1;m<=4;m++))
do
	> ./Exp_Rslt/FN/Method${m}Data${k}Rslt
	echo "data_${k} SHDEX: " >> ./Exp_Rslt/FN/Method${m}Data${k}Rslt
	for((i=6;i<=10;i++))
	do
		echo "tor : ${i}"  >> ./Exp_Rslt/FN/Method${m}Data${k}Rslt
		for((j=${i}-5;j<=${i}-1;j++))
		do
		    echo "ed : ${j}" >> ./Exp_Rslt/FN/Method${m}Data${k}Rslt
		    ./FNEXEC data_${k}_ed_${j} ${i} $m >> ./Exp_Rslt/FN/Method${m}Data${k}Rslt
		done
	    echo ------------------------------------- >> ./Exp_Rslt/FN/Method${m}Data${k}Rslt
	done
done
  
