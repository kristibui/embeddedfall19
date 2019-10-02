myWiimoteAccel: main.o WiimoteAccel.o
	g++ main.o WiimoteAccel.o -o myWiimoteAccel

main.o: main.cpp WiimoteAccel.h
	g++ -g -Wall -c main.cpp

WiimoteAccel.o: WiimoteAccel.cpp WiimoteAccel.h
	g++ -g -Wall -c WiimoteAccel.cpp

clean:
	rm main.o WiimoteAccel.o myWiimoteAccel

