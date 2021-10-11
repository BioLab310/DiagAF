#!/bin/bash
k=1
if [ ! -d Exp_Rslt  ];then
  mkdir Exp_Rslt
fi
if [ ! -d Exp_Rslt/FN  ];then
  mkdir Exp_Rslt/FN
else
  echo Exp_Rslt/FN exist
fi
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
  
