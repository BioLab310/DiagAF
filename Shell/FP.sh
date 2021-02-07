#!/bin/bash
#m=1  
k=1
for((m=1;m<=4;m++))   
do
	> ./Exp_Rslt/FP/Method${m}Data${k}Rslt
	echo "data_${k} method : $m" >> ./Exp_Rslt/FP/Method${m}Data${k}Rslt
	for((i=1;i<=10;i++))
	do
		echo "tor : ${i}"  >> ./Exp_Rslt/FP/Method${m}Data${k}Rslt
		for((j=${i}+1;j<=${i}+5;j++))
		do
		    echo "ed : ${j}" >> ./Exp_Rslt/FP/Method${m}Data${k}Rslt
		    ./FPEXEC data_${k}_ed_${j} ${i} $m >> ./Exp_Rslt/FP/Method${m}Data${k}Rslt
		done
	    echo ------------------------------------- >> ./Exp_Rslt/FP/Method${m}Data${k}Rslt
	done
done
  
