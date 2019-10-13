myGPIO: ServoPosition.o GPIO.o
	g++ ServoPosition.o GPIO.o -o myGPIO

ServoPosition.o: ServoPosition.cpp GPIO.h
	g++ -g -Wall -c ServoPosition.cpp

GPIO.o: GPIO.cpp GPIO.h
	g++ -g -Wall -c GPIO.cpp

clean:
	rm ServoPosition.o GPIO.o myGPIO
