#include <iostream>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <iostream> 
#include "WiimoteBtns.h"
using namespace std;

// Member functions definitions including constructor
WiimoteBtns::WiimoteBtns(void) {
	fd = open("/dev/input/event2", O_RDONLY);
	if (fd == -1)
	{
		std::cerr << "Error: Could not open event file - forgot sudo?\n";
		exit(1);
	}
}

// destructor fpr WiimoteBtns
WiimoteBtns::~WiimoteBtns(void) {
	cout << "Object is being deleted" << endl;
	close(fd);
}

// function that listens for button events on wiimote
void WiimoteBtns::Listen() {
	int code, value;
	char buffer[32];
	while (true)
	{
		read(fd, buffer, 32);
		code = buffer[10];
		value = buffer[12];
		ButtonEvent(code, value);
     	}
}

// prints out the button values
void WiimoteBtns::ButtonEvent(int code, int value) {
	std::cout << "Code = " << code << ", value = " << value << '\n';
}

