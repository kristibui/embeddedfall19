#include <iostream>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <iostream> 
#include "WiimoteAccel.h"
using namespace std;

// Main function for the program
int main() {
	WiimoteAccel myWiimote;

	myWiimote.Listen();

	return 0;
}
