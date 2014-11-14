#!/bin/bash

##############################
#./test.sh n_amostras
##############################
declare path_bin="./release"
declare bin="huffmanCpp-O3"
declare path_file="/home/admin/Workspace/Files"
declare -a file=("0000001mb" "0000008mb" "0000064mb" "0000128mb" "0000256mb" "0000512mb" "0001024mb" "0002048mb" "0004096mb" "0008192mb" "0012288mb")

echo "=========================================="
echo "cpp"
echo "=========================================="

for i in "${file[@]}"
do
	echo "$i"
	echo "-------------------------"
	for j in `seq 1 $1`
	do
		echo "Amostra$j"
		$path_bin/$bin $path_file/$i
		echo
	done
	echo "-------------------------"
	echo
	echo
done
