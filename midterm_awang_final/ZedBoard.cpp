#include <iostream>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <iostream> 
#include <sys/mman.h>
#include "ZedBoard.h"
using namespace std;

const unsigned gpio_size = 0xff;
const unsigned gpio_address = 0x400d0000;
// Member functions definitions including constructor
ZedBoard::ZedBoard(void) {
	fd = open( "/dev/mem", O_RDWR);
        pBase = (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);

	if (fd == -1)
	{
		std::cerr << "Error: Could not open event file - forgot sudo?\n";
		exit(1);
	}
}

// destructor for ZedBoard
ZedBoard::~ZedBoard(void) {
	cout << "Object is being deleted" << endl;
	munmap(pBase, gpio_size);
	close(fd);
}

/**
* Write a 4-byte value at the specified general-purpose I/O location.
*
* @parem offset Offset where device is mapped.
* @param value Value to be written.
*/
void ZedBoard::RegisterWrite(int offset, int value) {
	* (int *) (pBase + offset) = value;
}

/**
* Read a 4-byte value from the specified general-purpose I/O location.
*
* @param offset Offset where device is mapped.
* @return Value read.
*/
int ZedBoard::RegisterRead(int offset)
{
	return * (int *) (pBase + offset);
}

/** Changes the state of an LED (ON or OFF)
* @param ledNum LED number (0 to 7)
* @param state State to change to (ON or OFF)
*/
void ZedBoard::Write1Led(int ledNum, int state)
{
	if (ledNum >= 0 && ledNum <= 7) {
		int ledOffset = 300 + (ledNum * 4);
		RegisterWrite(ledOffset, state);
	} else {
		cout << "Error: led number is out of range" << endl;
	}
}

/** Set the state of the LEDs with the given value.
* @param value Value between 0 and 255 written to the LEDs
*/
void ZedBoard::WriteAllLeds(int value)
{
	for (int i = 0; i <  8; i++) {
		RegisterWrite(300 + (i * 4), (value / (1 << i)) % 2);
	}
}

/** Returns the integer representation of the button pressed.
*
* @return  0 if no push button is pressed, and a value between 1 and 5 if any push button is pressed
*/
int ZedBoard::PushButtonGet()
{
	for (int i = 0; i < 5; i++) {
		int offset = 364 + (i * 4);
		if (RegisterRead(offset) == 1) {
			//usleep(300000);
			return i + 1;
		}
	}
	usleep(300000);
	return 0;
}
