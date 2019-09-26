#include <iostream>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
using namespace std;
// Physical base address of GPIO
const unsigned gpio_address = 0x400d0000;
// Length of memory-mapped IO window
const unsigned gpio_size = 0xff;
const int gpio_led1_offset = 0x12C; // Offset for LED1
const int gpio_led2_offset = 0x130; // Offset for LED2
const int gpio_led3_offset = 0x134; // Offset for LED3
const int gpio_led4_offset = 0x138; // Offset for LED4
const int gpio_led5_offset = 0x13C; // Offset for LED5
const int gpio_led6_offset = 0x140; // Offset for LED6
const int gpio_led7_offset = 0x144; // Offset for LED7
const int gpio_led8_offset = 0x148; // Offset for LED8
const int gpio_sw1_offset = 0x14C; // Offset for Switch 1
const int gpio_sw2_offset = 0x150; // Offset for Switch 2
const int gpio_sw3_offset = 0x154; // Offset for Switch 3
const int gpio_sw4_offset = 0x158; // Offset for Switch 4
const int gpio_sw5_offset = 0x15C; // Offset for Switch 5
const int gpio_sw6_offset = 0x160; // Offset for Switch 6
const int gpio_sw7_offset = 0x164; // Offset for Switch 7
const int gpio_sw8_offset = 0x168; // Offset for Switch 8
const int gpio_pbtnl_offset = 0x16C; // Offset for left push button
const int gpio_pbtnr_offset = 0x170; // Offset for right push button
const int gpio_pbtnu_offset = 0x174; // Offset for up push button
const int gpio_pbtnd_offset = 0x178; // Offset for down push button
const int gpio_pbtnc_offset = 0x17C; // Offset for center push button 


/** Changes the state of an LED (ON or OFF)
* @param pBase base address of I/O
* @param ledNum LED number (0 to 7)
* @param state State to change to (ON or OFF)
*/
void Write1Led(char *pBase, int ledNum, int state);

/** Reads the value of a switch
* - Uses base address of I/O
* @param pBase base address of I/O
* @param switchNum Switch number (0 to 7)
* @return Switch value read
*/
int Read1Switch(char *pBase, int switchNum);

/** Set the state of the LEDs with the given value.
*
* @param pBase Base address for general-purpose I/O
* @param value Value between 0 and 255 written to the LEDs
*/
void WriteAllLeds(char *pBase, int value);

/** Reads all the switches and returns their value in a single integer.
*
* @param pBase Base address for general-purpose I/O
* @return A value that represents the value of the switches
*/
int ReadAllSwitches(char *pBase);

/**
* Write a 4-byte value at the specified general-purpose I/O location.
*
* @param pBase Base address returned by 'mmap'.
* @parem offset Offset where device is mapped.
* @param value Value to be written.
*/
void RegisterWrite(char *pBase, int offset, int value)
{
	* (int *) (pBase + offset) = value;
}
/**
* Read a 4-byte value from the specified general-purpose I/O location.
*
* @param pBase Base address returned by 'mmap'.
* @param offset Offset where device is mapped.
* @return Value read.
*/
int RegisterRead(char *pBase, int offset)
{
	return * (int *) (pBase + offset);
}
/**
* Initialize general-purpose I/O
* - Opens access to physical memory /dev/mem
* - Maps memory at offset 'gpio_address' into virtual address space
*
* @param fd File descriptor passed by reference, where the result
* of function 'open' will be stored.
* @return Address to virtual memory which is mapped to physical,
* or MAP_FAILED on error.
*/
char *Initialize(int *fd)
{
	*fd = open( "/dev/mem", O_RDWR);
	return (char *) mmap(NULL, gpio_size, PROT_READ | PROT_WRITE, MAP_SHARED,
	*fd, gpio_address);
}
/**
* Close general-purpose I/O.
*
* @param pBase Virtual address where I/O was mapped.
* @param fd File descriptor previously returned by 'open'.
*/
void Finalize(char *pBase, int fd)
{
	munmap(pBase, gpio_size);
	close(fd);
}

void Write1Led(char *pBase, int ledNum, int state)
{
	if (ledNum >= 0 && ledNum <= 7) {
		int ledOffset = 300 + (ledNum * 4);
		RegisterWrite(pBase, ledOffset, state);
	} else {
		cout << "Error: led number is out of range" << endl;
	}
}

int Read1Switch(char *pBase, int switchNum)
{
	if (switchNum >= 0 && switchNum <= 7) {
                int ledOffset = 332 + (switchNum * 4);
                return RegisterRead(pBase, ledOffset);
        } else {
                cout << "Error: switch number is out of range" << endl;
        	return -1;
	}
}

void WriteAllLeds(char *pBase, int value)
{
	for (int i = 0; i <  8; i++) {
		int currentOffset = pow(2, i);
		RegisterWrite(pBase, 300 + (i * 4), (value / (1 << i)) % 2);
	}
}

int PushButtonGet(char *pBase)
{
	for (int i = 0; i < 5; i++) {
		int offset = 364 + (i * 4);
		//cout << "Register read: " << i << " =" << RegisterRead(pBase, offset) << endl;
		if (RegisterRead(pBase, offset) == 1) {
			usleep(300000);
			return i + 1;
		}
	}
	usleep(300000);
	return 0;
}

int ReadAllSwitches(char *pBase)
{
	int catVal = 0;
	for (int i = 0; i < 8; i++) {
                if (Read1Switch(pBase, i) == 1) {
			catVal += 1 << i;
        	}
	}
	return catVal;
}

int main()
{
	// Initialize
	int fd;
	char *pBase = Initialize(&fd);
	// Check error
	if (pBase == MAP_FAILED)
	{
		cerr << "Mapping I/O memory failed - Did you run with 'sudo'?\n";
		exit(1); // Returns 1 to the operating system;
	}
	// ************** Put your code here **********************
	/**
	int userLedNum, userState;

	cout << "Please enter LED number from 0 to 7 to write: ";
	cin >> userLedNum;
	cout << "Please enter 0 or 1 for the state: ";
	cin >> userState;

	Write1Led(pBase, userLedNum, userState);

	int userReadNum;
	cout << "Please enter LED number from 0 to 7 to read: ";
	cin >> userReadNum;
	int readUser = Read1Switch(pBase, userReadNum);
	cout << readUser << endl;

	int allValue;
	cout << "Enter a value less than 256: " << endl; 
	cin >> allValue; 
	WriteAllLeds(pBase, allValue);
	cout << "Write all LEDs value = " << allValue << endl; 


	cout << "Read all switches: " << ReadAllSwitches(pBase) << endl;
	**/
	int buttonStates[5];
	int count = 0;
	int countTime = 0;
	while (countTime < 3) {
		int userButton = PushButtonGet(pBase);
		if (userButton  == 0) {
			for (int i = 0; i < 5; i++) {
				buttonStates[i] = 0;
			}
		}
		else if (userButton == 1 && buttonStates[0] != 1) {
			buttonStates[0] = 1;
			count<<= 1;
			cout << "Count: " << count << endl;
		}
		else if (userButton == 2 && buttonStates[1] != 1) {
			buttonStates[1] = 1;
			count>>= 1;
			cout << "Count: " << count << endl;
		}
		else if (userButton == 3 && buttonStates[2] != 1) {
                        buttonStates[2] = 1;
                        count += 1;
			cout << "Count: " << count << endl;
                }
		else if (userButton == 4 && buttonStates[3] != 1) {
                        buttonStates[3] = 1;
                        count -= 1;
			cout << "Count: " << count << endl;
                }
		else if (userButton == 5 && buttonStates[4] != 1) {
                        buttonStates[4] = 1;
                        count = ReadAllSwitches(pBase);
			cout << "Count: " << count << endl;
                }
		WriteAllLeds(pBase, count);
	}
	// Done
	Finalize(pBase, fd);
}
