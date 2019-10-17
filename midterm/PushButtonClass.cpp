  
#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
using namespace std;

// class representing a ZedBoard that initializes, finalizes, reads and writes to a register
class ZedBoard
{
	char *pBase;
	int fd;
	public:
		ZedBoard()
		{
			fd = open( "/dev/mem", O_RDWR);
        		pBase = (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, gpio_address);
		}
		~ZedBoard()
		{
			munmap(pBase, gpio_size);
        		close(fd);
		}
		void RegisterWrite(int offset, int value)
		{
			* (int *) (pBase + offset) = value;
		}
		int RegisterRead(int offset)
		{
			return * (int *) (pBase + offset);
		}
};

/** Changes the state of an LED (ON or OFF)
* @param board Board for general-purpose I/O
* @param ledNum LED number (0 to 7)
* @param state State to change to (ON or OFF)
*/
void Write1Led(ZedBoard *board, int ledNum, int state);

/** Reads the value of a switch
* - Uses base address of I/O
* @param board Board for general-purpose I/O
* @param switchNum Switch number (0 to 7)
* @return Switch value read
*/
int Read1Switch(ZedBoard *board, int switchNum);

/** Set the state of the LEDs with the given value.
*
* @param board Board for general-purpose I/O
* @param value Value between 0 and 255 written to the LEDs
*/
void WriteAllLeds(ZedBoard *board, int value);

/** Reads all the switches and returns their value in a single integer.
*
* @param board Board for general-purpose I/O
* @return A value that represents the value of the switches
*/
int ReadAllSwitches(ZedBoard *board);

void Write1Led(ZedBoard *board, int ledNum, int state)
{
	if (ledNum >= 0 && ledNum <= 7) {
		int ledOffset = 300 + (ledNum * 4);
		board->RegisterWrite(ledOffset, state);
	} else {
		cout << "Error: led number is out of range" << endl;
	}
}

int Read1Switch(ZedBoard *board, int switchNum)
{
	if (switchNum >= 0 && switchNum <= 7) {
                int ledOffset = 332 + (switchNum * 4);
                return board->RegisterRead(ledOffset);
        } else {
                cout << "Error: switch number is out of range" << endl;
        	return -1;
	}
}

void WriteAllLeds(ZedBoard *board, int value)
{
	for (int i = 0; i <  8; i++) {
		int currentOffset = pow(2, i);
		board->RegisterWrite(300 + (i * 4), (value / (1 << i)) % 2);
	}
}

int ReadAllSwitches(ZedBoard *board)
{
	int catVal = 0;
	for (int i = 0; i < 8; i++) {
                if (Read1Switch(board, i) == 1) {
			catVal += 1 << i;
        	}
	}
	return catVal;
}

/** Returns the integer representation of the button pressed.
*
* @param board Board for general-purpose I/O
* @return  0 if no push button is pressed, and a value between 1 and 5 if any push button is pressed
*/
int PushButtonGet(ZedBoard *board)
{
	for (int i = 0; i < 5; i++) {
		int offset = 364 + (i * 4);
		if (board->RegisterRead(offset) == 1) {
			usleep(300000);
			return i + 1;
		}
	}
	usleep(300000);
	return 0;
}
