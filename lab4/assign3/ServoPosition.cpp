#include "GPIO.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

int main()
{
	int servo, position;
	cout << "Enter a servo number between 1 and 5:" << endl;
	cout << "1: Base" << endl;
	cout << "2: Bicep" << endl;
	cout << "3: Elbow" << endl;
	cout << "4: Wrist" << endl;
	cout << "5: Gripper" << endl;
	cin >> servo;

	if(servo < 1 || servo > 5){
		cout << "Invalid servo number" << endl;
		return 0;
	}
	cout << "Enter position for servo in degrees:" << endl;
	cin >> position;
	if (position < 0 || position > 180) {
		cout << "Invalid position range" << endl;
		return 0;
	}
	int port;
	if (servo == 1) {
		port = 13;
	} else if (servo == 2) {
		port = 10;
	} else if (servo == 3) {
		port = 11;
	} else if (servo == 4) {
		port = 12;
	} else if (servo == 5) {
		port = 0;
	}
	// Open device file
	GPIO gpio(port);
	int on_time;
	on_time = (position * 10) + 600;
	// Generate PWM signal with 20ms period and 1.5ms on time.
	// Generate 400 periods, this will take 20ms * 400 iterations = 8s
	gpio.GeneratePWM(20000, on_time, 400);
	// Done
	return 0;
}
