myGPIO: main.o GPIO.o ZedBoard.o
	g++ main.o -std=c++0x -pthread GPIO.o ZedBoard.o -o myGPIO

main.o: main.cpp GPIO.h ZedBoard.h
	g++ -g -Wall -c -std=c++0x -pthread main.cpp

GPIO.o: GPIO.cpp GPIO.h
	g++ -g -Wall -c GPIO.cpp

ZedBoard.o: ZedBoard.cpp ZedBoard.h
	g++ -g -Wall -c ZedBoard.cpp

clean:
	rm *.o myGPIO
