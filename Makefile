diary : main.o memo.o calendar.o
	g++ -o diary main.o memo.o calendar.o

main.o : main.cpp
	g++ -c -o main.o main.cpp

memo.o : memo.cpp
	g++ -c -o memo.o memo.cpp

calendar.o : calendar.cpp
	g++ -c -o calendar.o calendar.cpp

clean :
	rm *.o diary

all :
	make clean
	make
