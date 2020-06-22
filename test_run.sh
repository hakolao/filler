#!/bin/bash

MAPS=test/maps/*
PLAYERS=test/players/*
ME="./ohakola.filler"
FILLER_VM=test/filler_vm

if [ "$#" -ne 2 ]; then
	echo "You must enter exactly 2 command line arguments"
	echo "in the form: ./test_run.sh [p1/p2] [quick/thorough]"
	exit 0
fi

if [ $1 == "p1" ]; then
	echo "$ME: Player1"
elif [ $1 == "p2" ]; then
	echo "$ME: Player2"
else
	echo "First argument must be either p1 or p2"
	exit 0
fi

if [ $2 == "quick" ]; then
	echo "Quick run"
elif [ $2 == "thorough" ]; then
	echo "Thorough run"
else
	echo "Second argument must be either quick or thorough"
	exit 0
fi

make > /dev/null 2>&1 

if test -f results.txt; then
	rm results.txt
fi

GAMES=0
for m in $MAPS; do
	for p in $PLAYERS; do
		for i in {0..4}; do
			let GAMES++
		done;
	done;
	if [ $2 == "quick" ]; then
		break ;
	fi
done

RED='\033[0;31m'
NC='\033[0m'
GREEN='\033[0;32m'

P1WINS=0
P2WINS=0
COUNT=0
for m in $MAPS; do
	for p in $PLAYERS; do
		echo "Map $m Against $p"
		echo "Map $m Against $p" >> results.txt
		for i in {0..4}; do
			if [ $1 == "p2" ]; then
				./$FILLER_VM -f $m -p2 $ME -p1 $p > temp.txt
			else
				./$FILLER_VM -f $m -p1 $ME -p2 $p > temp.txt
			fi
			O=$(cat temp.txt | tail -n 2 | head -n 1)
			X=$(cat temp.txt | tail -n 2 | tail -n 1)
			# Make sure O and X contain their finish parts, otherwise there's been an error input in the game
			if [[ $O == *"== O"* ]]; then
				O=$(echo $O | cut -d " " -f 4)
			fi
			if [[ $X == *"== O"* ]]; then
				O=$(echo $X | cut -d " " -f 4)
			fi
			if [[ $X == *"== X"* ]]; then
				X=$(echo $X | cut -d " " -f 4)
			fi
			if [[ $O == *"== X"* ]]; then
				X=$(echo $O | cut -d " " -f 4)
			fi
			# Make sure O and X are numbers, otherwise there's been an error input in the game
			RE='^[0-9]+$'
			if ! [[ $O =~ $RE ]]; then
				O=0
			fi
			if ! [[ $X =~ $RE ]]; then
				X=0
			fi
			if [[ $O -gt $X ]]; then
				P1WINS=$(( P1WINS + 1 ))
			fi
			if [[ $X -gt $O ]]; then
				P2WINS=$(( P2WINS + 1 ))
			fi
			let COUNT++
			rm temp.txt
			if [ $1 == "p2" ]; then
				if [[ $X -gt $O ]]; then
					printf "${GREEN}Winner: YOU${NC} ${X} to ${O}\n"
					echo "Winner: YOU $X to $O" >> results.txt
				else
					if [[  $X -eq $O ]]; then
						printf "${GREEN}Even${NC} ${X} to ${O}\n"
						echo "Even $X to $O" >> results.txt
					else
						printf "${RED}Winner: ENEMY${NC} ${O} to ${X}\n"
						echo "Winner: ENEMY $O to $X" >> results.txt
					fi
				fi
			else
				if [[ $O -gt $X ]]; then
					printf "${GREEN}Winner: YOU${NC} ${O} to ${X}\n"
					echo "Winner: YOU $O to $X" >> results.txt
				else
					if [[  $O -eq $X ]]; then
						printf "${GREEN}Even${NC} ${O} to ${X}\n"
						echo "Even $O to $X" >> results.txt
					else
						printf "${RED}Winner: ENEMY${NC} ${X} to ${O}\n"
						echo "Winner: ENEMY $X to $O" >> results.txt
					fi
				fi
			fi
			SEED=$(cat filler.trace | head -n 1 | cut -d " " -f 3)
			if [ $1 == "p2" ]; then
				REPEAT="./$FILLER_VM -f $m -p2 $ME -p1 $p -s $SEED"
				REPEAT_VISUAL="./$FILLER_VM -f $m -p2 \"$ME visual\" -p1 $p -s $SEED"
			else
				REPEAT="./$FILLER_VM -f $m -p1 $ME -p2 $p -s $SEED"
				REPEAT_VISUAL="./$FILLER_VM -f $m -p1 \"$ME visual\" -p2 $p -s $SEED"
			fi
			echo "Play: make && $REPEAT" >> results.txt
			echo "Play visual: make && $REPEAT_VISUAL" >> results.txt
		done;
	done;
	if [ $2 == "quick" ]; then
		break ;
	fi
done

if [ $1 == "p2" ]; then
	RESULT=$(( (P2WINS * 100 / GAMES) ))
else
	RESULT=$(( (P1WINS * 100 / GAMES) ))
fi

echo ""
echo "-------" >> results.txt
echo "$ME won $RESULT percent of $GAMES games played" >> results.txt
RESULT_LINE=$(cat results.txt | tail -n 1)
if [ $RESULT -gt 50 ]; then
	printf "${GREEN}${RESULT_LINE}${NC}\nSee results.txt for more information\n"
else
	printf "${RED}${RESULT_LINE}${NC}\nSee results.txt for more information\n"
fi