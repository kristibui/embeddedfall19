#include <iostream>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <iostream> 
#include "WiimoteAccel.h"
using namespace std;

// Member functions definitions including constructor
WiimoteAccel::WiimoteAccel(void) {
	fd = open("/dev/input/event0", O_RDONLY);
	if (fd == -1)
	{
		std::cerr << "Error: Could not open event file - forgot sudo?\n";
		exit(1);
	}
}

// destructor fpr WiimoteAccel
WiimoteAccel::~WiimoteAccel(void) {
	cout << "Object is being deleted" << endl;
	close(fd);
}

// function that listens for button events on wiimote
void WiimoteAccel::Listen() {
	int code;
	char buffer[16];
	while (true)
	{
		read(fd, buffer, 16);
		code = buffer[10];
		short acceleration = * (short *) (buffer + 12);
		AccelerationEvent(code, acceleration);
     	}
}

// prints out the acceleration values
void WiimoteAccel::AccelerationEvent(int code, int acceleration) {
	std::cout << "Code = " << code << ", acceleration = " << acceleration << '\n';
}

