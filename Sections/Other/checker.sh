if !(g++ g.cpp -o g && g++ --std=c++11 c1.cpp -o c1 && g++ c2.cpp -o c2)
then
	exit
fi

echo read
read N

i=1
while [ $i -le $N ];
do
    echo $i
	echo $i | ./g | ./c1 > a
	echo $i | ./g | ./c2 > b
	if ! diff a b
	then
		echo $i | ./g > $i.txt
        cat a >> $i.txt
        cat b >> $i.txt
	fi
	i=$((i+1))
done
