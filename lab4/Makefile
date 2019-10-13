myGPIO: main.o GPIO.o
	g++ main.o GPIO.o -o myGPIO

main.o: main.cpp GPIO.h
	g++ -g -Wall -c main.cpp

GPIO.o: GPIO.cpp GPIO.h
	g++ -g -Wall -c GPIO.cpp

clean:
	rm main.o GPIO.o myGPIO
