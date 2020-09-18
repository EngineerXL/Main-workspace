#!/bin/bash

# Converts .ged file into father() and mother() statements
# and writes to a.pl O(n^2)

touch basehusb.txt
touch basewife.txt

IFS=$'\n'
flag=0

husb=""
wife=""
chil=""
flaghusb=0
flagwife=0
flagchil=0
for i in `cat $1`
do
	len=${#i}
	if [[ "INDI" = ${i:$len-5:4} ]];
	then
		flag=1
	fi

	# Husband
	if [[ "HUSB" = ${i:2:4} ]];
	then
		ID=${i:7:$len-8}
		last=0
		for j in `cat $1`
		do
			lenn=${#j}
			if [[ "INDI" = ${j:$lenn-5:4} ]];
			then
				last=${j:2:9}
			fi
			if [[ ("NAME" = ${j:2:4}) && ($ID = $last) ]];
			then
				sub=${j:7:$lenn-8}
				husb=""
				for (( k=0; k<${#sub}; k++ ));
				do
					c="${sub:k:1}"
					if [[ ($c != " ") && ($c != ".") && ($c != "/") ]];
					then
						husb+="$c"
					fi
				done
			fi
		done
		if [[ $husb != "" ]];
		then
			let "flaghusb = 1"
		fi
	fi

	# Wife
	if [[ "WIFE" = ${i:2:4} ]];
	then
		ID=${i:7:$len-8}
		last=0
		for j in `cat $1`
		do
			lenn=${#j}
			if [[ "INDI" = ${j:$lenn-5:4} ]];
			then
				last=${j:2:9}
			fi
			if [[ ("NAME" = ${j:2:4}) && ($ID = $last) ]];
			then
				sub=${j:7:$lenn-8}
				wife=""
				for (( k=0; k<${#sub}; k++ ));
				do
					c="${sub:k:1}"
					if [[ ($c != " ") && ($c != ".") && ($c != "/") ]];
					then
						wife+="$c"
					fi
				done
			fi
		done
		if [[ $wife != "" ]];
		then
			let "flagwife = 1"
		fi
	fi

	# Children
	if [[ "CHIL" = ${i:2:4} ]];
	then
		ID=${i:7:$len-8}
		last=0
		for j in `cat $1`
		do
			lenn=${#j}
			if [[ "INDI" = ${j:$lenn-5:4} ]];
			then
				last=${j:2:9}
			fi
			if [[ ("NAME" = ${j:2:4}) && ($ID = $last) ]];
			then
				sub=${j:7:$lenn-8}
				chil=""
				for (( k=0; k<${#sub}; k++ ));
				do
					c="${sub:k:1}"
					if [[ ($c != " ") && ($c != ".") && ($c != "/") ]];
					then
						chil+="$c"
					fi
				done
			fi
		done
		if [[ $chil != "" ]];
		then
			let "flagchil = 1"
		fi
	fi

	if [[ "FAM" = ${i:$len-4:3} ]];
	then
		let "flaghusb = 0"
		let "flagwife = 0"
		let "flagchil = 0"
	fi

	if ((test $flaghusb -eq 1) && (test $flagwife -eq 1) && (test $flagchil -eq 1))
	then
		echo "father('${husb}', '${chil}')." >> basehusb.txt
		echo "mother('${wife}', '${chil}')." >> basewife.txt
		let "flagchil = 0"
	fi
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

rm basewife.txt basehusb.txt