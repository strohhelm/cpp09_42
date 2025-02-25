// #! /bin/bash

// # amount=1000
// # counter=1
// # exit=0
// # prog=1
// # while [ $counter -le $amount ]
// # do
// # 	# echo hallo
// # 	./PmergeMe `jot -r 3000 1 10000 | tr '\n' ' '` > /dev/null
// # 	if [ "$(echo $?)" -ne 0 ]
// # 		then
// # 			$exit = 1
// # 			break
// # 	fi
// # 	prog=$(($counter * 100 / $amount))
// # 		echo -ne "\r Progress:"
// # 	 	printf '%0.s█' $(seq 0 $prog)
// # 		last=$(( 100 - $prog))
// # 		printf '%0.s ' $(seq 1 $last)
// # 		echo -ne "($counter / $amount)"
// # 	counter=$(($counter + 1))
// # done

// # if [ $exit -eq "0" ]
// # 	then
// # 		echo
// # 		echo "Hurray! all " $amount " tests were successful!"
// # 	else
// # 		echo "Oh shit you fucked up!"
// # fi