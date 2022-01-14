#!/bin/bash
if [ $1 != "--no-compile" ]
then
    make clean 1> rm.out 2> rm.out
    make all 1> rm.out
fi

# Set colors 
red=`tput setaf 1`
green=`tput setaf 2`
reset=`tput sgr0`

cd bin
echo ""
echo "############### Executing tests ###############"
for i in 1 2 3 4 5
do
    ./programa < ../input/$i.in > ../output/$i-result.out
    diff -y ../output/$i.out ../output/$i-result.out > ../output/$i-diff.out
    if [ $? -eq 0 ]
    then
        echo "|> Test status for input number $i: ${green}PASSED! (V)${reset}"
    else
        echo "|> Test status for input number $i: ${red}FAILED! (X)${reset}"
    fi
done
echo "###############################################"
echo ""
cd ..

make clean 1> rm.out 2> rm.out
rm rm.out