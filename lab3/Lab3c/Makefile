myWiimoteAccel: main.o WiimoteAccel.o ZedBoard.o
	g++ main.o WiimoteAccel.o ZedBoard.o -o myWiimoteAccel

main.o: main.cpp WiimoteAccel.h ZedBoard.h
	g++ -g -Wall -c main.cpp

WiimoteAccel.o: WiimoteAccel.cpp WiimoteAccel.h
	g++ -g -Wall -c WiimoteAccel.cpp

ZedBoard.o: ZedBoard.cpp ZedBoard.h
	g++ -g -Wall -c ZedBoard.cpp

clean:
	rm *.o myWiimoteAccel

