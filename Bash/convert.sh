#!/bin/bash

# Converts .ged file into father() and mother() statements
# and writes to a.pl O(n^2)

touch basenames.txt
touch basehusb.txt
touch basewife.txt

IFS=$'\n'

husb=""; wife=""; chil=""
found_husb=0; found_wife=0; found_chil=0
flag_husb=0; flag_wife=0; flag_chil=0, flag=0
for i in `cat $1`
do
	len=${#i}

	# Write indicator and name lines into another file
	# to search for them faster
	if [[ ("INDI" = ${i:$len-5:4}) || ("NAME" = ${i:2:4}) ]];
	then
		echo $i >> basenames.txt
	fi

	if [[ "HUSB" = ${i:2:4} ]];
	then
		let "flag_husb = 1"; let "flag = 1"
	fi

	if [[ "WIFE" = ${i:2:4} ]];
	then
		let "flag_wife = 1"; let "flag = 1"
	fi

	if [[ "CHIL" = ${i:2:4} ]];
	then
		let "flag_chil = 1"; let "flag = 1"
	fi

	if (test $flag -eq 1)
	then
		ID=${i:7:$len-8}
		last_id=0
		name=""
		for j in `cat basenames.txt`
		do
			lenn=${#j}
			if [[ "INDI" = ${j:$lenn-5:4} ]];
			then
				last_id=${j:2:9}
			fi
			if [[ ("NAME" = ${j:2:4}) && ($ID = $last_id) ]];
			then
				sub=${j:7:$lenn-8}
				for (( k=0; k<${#sub}; k++ ));
				do
					c="${sub:k:1}"
					if [[ ($c != " ") && ($c != ".") && ($c != "/") ]];
					then
						name+="$c"
					fi
				done
				break
			fi
		done
		if [[ $name != "" ]];
		then
			if (test $flag_husb -eq 1)
			then
				let "found_husb = 1";
				husb=$name
			fi
			if (test $flag_wife -eq 1)
			then
				let "found_wife = 1";
				wife=$name
			fi
			if (test $flag_chil -eq 1)
			then
				let "found_chil = 1";
				chil=$name
			fi
		fi
	fi

	# Another family?
	if [[ "FAM" = ${i:$len-4:3} ]];
	then
		let "found_husb = 0"; let "found_wife = 0"; let "found_chil = 0"
	fi

	# More than one child? flagchil = 0
	if ((test $found_husb -eq 1) && (test $found_wife -eq 1) && (test $found_chil -eq 1))
	then
		echo "father('${husb}', '${chil}')." >> basehusb.txt
		echo "mother('${wife}', '${chil}')." >> basewife.txt
		let "found_chil = 0"
	fi
	let "flag_husb = 0"; let "flag_wife = 0"; let "flag_chil = 0"; let "flag = 0"
done

touch base.txt
echo > base.txt

for i in `cat basehusb.txt`
do
	echo $i >> base.txt
done

echo >> base.txt

for i in `cat basewife.txt`
do
	echo $i >> base.txt
done

rm basenames.txt basewife.txt basehusb.txt