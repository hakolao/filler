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

# https://unix.stackexchange.com/questions/415421/linux-how-to-create-simple-progress-bar-in-bash
prog() {
	local w=80 p=$1;  shift
	printf -v dots "%*s" "$(( $p*$w/100 ))" ""; dots=${dots// /.};
	printf "\r\e[K|%-*s| %3d %% %s" "$w" "$dots" "$p" "$*"; 
}

GAMES=0
for m in $MAPS; do
	for p in $PLAYERS; do
		let GAMES++
	done;
	if [ $2 == "quick" ]; then
		break ;
	fi
done

P1WINS=0
P2WINS=0
COUNT=0
for m in $MAPS; do
	for p in $PLAYERS; do
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
		if [[ $O -ge $X ]]; then
			P1WINS=$(( P1WINS + 1 ))
		fi
		if [[ $X -ge $O ]]; then
			P2WINS=$(( P2WINS + 1 ))
		fi
		let COUNT++
		prog "$(( (COUNT * 100 / GAMES) ))"
		rm temp.txt
		echo "O: $O" >> results.txt
		echo "X: $X" >> results.txt
		if [ $1 == "p2" ]; then
			REPEAT="./$FILLER_VM -f $m -p2 $ME -p1 $p"
		else
			REPEAT="./$FILLER_VM -f $m -p1 $ME -p1 $p"
		fi
		echo "===== Repeat: make && $REPEAT" >> results.txt
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
echo "$ME won $RESULT% of $GAMES games played" >> results.txt
cat results.txt
rm results.txt