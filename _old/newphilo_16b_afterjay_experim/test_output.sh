#!/bin/bash

GRN="\e[38;5;40m"
BLU="\e[38;5;51m"
RED="\e[38;5;196m"
RES="\e[0m"

# README
# Time has to be more >= 5 seconds, otherwise nothing is stored into file "output"
# Tester checks last 2 lines when program was interupted by timeout. The last 2 lines
#    need to include "is" or "has", to be valid


#make re 





MEALS=20
DIED="     died"
OK="${GRN} OK ${RES}"
KO="${RED} KO ${RES}"


echo "" > output_lastlines

check_last_lines() {
	local i="$1"
	LASTLINE=$( tail -n 2 output )
	echo "TEST $i" >> output_lastlines
	echo "$LASTLINE" >> output_lastlines
	if grep -q " is" <<< $LASTLINE || \
		grep -q " has" <<< $LASTLINE; then
		echo "" >> output_lastlines
		#echo -e $GRN" ------------- YES"$RES
		return 0
	fi

	#echo -e $RED" ----------- STH WRONG"$RES
	return 1
}





# ## SHOULD DIE ##################################################
# ARGS=(  "1 800 200 200"\
#  		"2 200 200 200"\
#  		"2 310 200 100"\
#  		"4 310 200 100"\
#  		"4 200 205 200")

# echo -e "\n${BLU} ----------------------------------------------------------- ${RES}"
# echo -e    "${BLU}SHOULD DIE: ----------------------------------------------- ${RES}\n"
# i=0
# while [ $i -le 4 ]
# do
# 	./philo ${ARGS[$i]} $MEALS > output
# 	RET=$(grep -c 'died' output)
# 	if [ $RET = 1 ]; then
# 		echo -e ".... ${ARGS[$i]} $DIED $OK \n"
# 	fi
# 	 ((i++))
# done





# ## SHOULD NOT DIE,  ##################################################
MEALS=2
TIME=5
ARGS=(  "  4 410 200 200"\
		"  5 800 200 200"\
 		"  5 600 150 150"\
 		"100 800 200 200"\
 		"105 800 200 200"\
 		"200 800 200 200")

echo -e "\n${BLU}------------------------------------------------------------- ${RES}"
echo -e   "${BLU}SHOULD NOT DIE, $TIME secs -------------------------------------- ${RES}\n"
i=0
while [ $i -le 5 ]
do
#	echo -e -n "Test $i:  ${ARGS[$i]} $MEALS"     ; sleep 1
#	timeout 1 ./philo ${ARGS[$i]} $MEALS > output ; sleep 1
	echo -e -n "Test $i:	${ARGS[$i]}"
	timeout $TIME ./philo	${ARGS[$i]}    > output ; sleep 1
	RET=$(grep -c 'died' output)
	check_last_lines $i
	CHECK=$?
	if [ $RET = 0 ]; then
		if [ $CHECK == 0 ]; then
			echo -e " .... $OK \n" ; sleep 1
		fi
	elif [ $RET = 1 ]; then
		echo -e " .... died $KO \n" ; sleep 1
	fi
	((i++))
done

