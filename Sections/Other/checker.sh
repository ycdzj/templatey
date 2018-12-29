if !(g++ g.cpp -o g.out && g++ --std=c++11 c1.cpp -o c1.out && g++ c2.cpp -o c2.out)
then
	exit
fi

echo read
read N

RF=rand.txt
i=1
while [ $i -le $N ];
do
	FN=a${i}.txt
	echo $i > $RF
	./g.out < $RF > $FN
	./c1.out < $FN > c1.txt
	./c2.out < $FN > c2.txt
	if diff c1.txt c2.txt
	then
		echo pass
		rm $FN
	fi
	i=$((i+1))
done
