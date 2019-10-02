#include <iostream>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <iostream> 
#include "WiimoteBtns.h"
using namespace std;

// Main function for the program
int main() {
	WiimoteBtns myWiimote;

	myWiimote.Listen();

	return 0;
}
