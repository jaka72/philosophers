#!/bin/bash

# GRN="\e[38;5;40m" # only on Linux ???
# BLU="\e[38;5;51m"
# RED="\e[38;5;196m"
# RES="\e[0m"

BOLD="\033[0;1m"
RED="\033[0;31m"
CYN="\033[0;36m"
PRP="\033[0;35m"
GRN="\033[0;32m"
BLU="\033[0;34m"
BLUEBG="\033[44m"
WHT="\033[1;97m"
RES="\033[0m"


# README  README  README  #########################################################
#
#	On Mac, must be installed brew Coreutils, for gtimeout
#
#	Each output goes into file "output", temporarily.
# 	Time must be >= 5 seconds, otherwise nothing is stored into file "output"
# 	Tester checks last 2 lines when program was interupted by timeout. The last 2 lines
#    	must include "is" or "has", to be valid
#		These last lines go into file output_lastlines
#
#	SET VARIABLES:
	TIME=5		# How long to run each test (must be >= 5 secs)
	MEALS=2		# Max nr of meals (only for the last group of tests)
	CYCLES=1	# How many times to perform each group of tests 
#
###################################################################################

make re

echo "" > output_lastlines # TO CLEAR THE FILE FROM PREVIOUS OUTPUT

DIED="     died"
OK="${GRN} OK ${RES}"
KO="${RED} KO ${RES}"


check_last_lines() {
	local i="$1"
	LASTLINE=$( tail -n 2 output )
	echo "TEST $i" >> output_lastlines
	echo "$LASTLINE" >> output_lastlines
	if grep -q " is" <<< $LASTLINE || \
		grep -q " has" <<< $LASTLINE; then
		echo "" >> output_lastlines
		return 0
	fi
	return 1
}



# ## SHOULD DIE ##################################################

# ARGS=(	"1 800 200 200"\
# 		"2 200 200 200"\
# 		"2 310 200 100"\
# 		"4 310 200 100"\
# 		"4 200 205 200")
# ARRLEN=${#ARGS[@]}

# j=0
# while [ $j -lt $CYCLES ]
# 	do
# 	echo -e "${GRN}\n----------------------------------------------------------- ${RES}"
# 	echo -e    "${GRN}SHOULD DIE: ----------------------------------------------- ${RES}\n"
# 	echo -e "${GRN}     CYCLE $j ${RES}"
# 	i=0
# 	while [ $i -lt $ARRLEN ]
# 		do
# 			./philo ${ARGS[$i]} > output
# 			RET=$(grep -c 'died' output)
# 			if [ $RET = 1 ]; then
# 				echo -e "    ${ARGS[$i]} $DIED $OK \n"
# 			fi
# 			((i++))
# 	done
# 	((j++))
# done



# ## SHOULD NOT DIE,  ##################################################

# ARGS=(  "  4 410 200 200"\
# 		"  5 800 200 200"\
#  		"  5 600 150 150"\
#  		"100 800 200 200"\
#  		"105 800 200 200"\
#  		"200 800 200 200")
# ARRLEN=${#ARGS[@]}

# j=0
# while [ $j -lt $CYCLES ]
# do
# 	echo -e "\n${GRN}-------------------------------------------------------------- ${RES}"
# 	echo -e   "${GRN}SHOULD NOT DIE, $TIME secs -------------------------------------- ${RES}\n"
# 	echo -e "${GRN}     CYCLE $j ${RES}"
# 	echo "CYCLE $j" >> output_lastlines
# 	i=0
# 	while [ $i -lt $ARRLEN ]
# 	do
# 		echo -e -n "Test $i:	${ARGS[$i]}"
# 		#gtimeout $TIME ./philo	${ARGS[$i]}    > output ; sleep 1
# 		timeout $TIME ./philo	${ARGS[$i]}    > output ; sleep 1
# 		#sleep $TIME
# 		#killall philo
# 		python3 output_check_order.py
# 		ORDER=$?
# 		RET=$(grep -c 'died' output)
# 		check_last_lines $i
# 		CHECK=$?
# 		if [ $RET == 0 ] && [ $ORDER == 0 ]; then
# 			if [ $CHECK == 0 ]; then
# 				echo -e " .... $OK \n" ; sleep 1
# 			fi
# 		elif [ $RET = 1 ] && [ $ORDER == 0 ]; then
# 			echo -e " .... died $KO \n" ; sleep 1
# 		elif [ $RET = 1 ] && [ $ORDER == 1 ]; then
# 			echo -e " .... died $KO \n" ; sleep 1
# 		fi
# 		((i++))
# 	done
# 	((j++))
# done


###  SHOULD STOP AFTER x MEALS  ##################################################

ARGS=(  "  4 410 200 200"\
		"  5 800 200 200"\
 		"  5 600 150 150"\
 		"100 800 200 200"\
 		"105 800 200 200"\
 		"200 800 200 200")
ARRLEN=${#ARGS[@]}

j=0

while [ $j -lt $CYCLES ]
do
	echo -e "\n${GRN}--------------------------------------------------------------- ${RES}"
	echo -e   "${GRN}SHOULD STOP AFTER $MEALS MEALS -------------------------------------- ${RES}\n"
	echo -e "${GRN}     CYCLE $j ${RES}"	
	i=0
	while [ $i -lt $ARRLEN ]
	do
		echo -e -n "Test $i:  ${ARGS[$i]} $MEALS"     ; sleep 1
		./philo ${ARGS[$i]} $MEALS > output ; sleep 1
		RET=$(grep -c 'eating' output)
		MAX_EXPECTED_MEALS=$( echo ${ARGS[$i]} | head -n1 | awk '{print $1;}' )
		MAX_EXPECTED_MEALS=$(($MAX_EXPECTED_MEALS * $MEALS))

		if [ $RET == $MAX_EXPECTED_MEALS ]; then
				echo -e " .... $OK \n" ; sleep 1
		else
			echo -e " .... problem with nr of eaten meals $KO \n" ; sleep 1
		fi
		((i++))
	done
	((j++))
done

exit 0