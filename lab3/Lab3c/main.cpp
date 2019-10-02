#include <iostream>
#include <stdlib.h> 
#include <fcntl.h> 
#include <unistd.h> 
#include <iostream> 
#include <math.h>
#include "WiimoteAccel.h"
#include "ZedBoard.h"
using namespace std;

class WiimoteToLed: public WiimoteAccel {
	private:
		ZedBoard *board;
	public:
		WiimoteToLed(ZedBoard *zed_board)
		{
			board = zed_board;
		}

		void AccelerationEvent(int code, int acceleration)
		{
			if (code != 3) return;

			int truncated_accel;

			if (acceleration > 100) {
				truncated_accel = 100;
			}
			else if (acceleration < -100) {
				truncated_accel = -100;
			}
			else {
				truncated_accel = acceleration;
			}

			int numberLeds;

			numberLeds =  abs(truncated_accel) / 12;

			board->WriteAllLeds(pow(2, numberLeds) - 1);
		}
};

// Main function for the program
int main()
{
	// Instantiate ZedBoard object statically
	ZedBoard zed_board;

	// Instantiate WiimoteToLed object statically, passing a pointer to the
	// recently created ZedBoard object.
	WiimoteToLed wiimote_to_led(&zed_board);

	// Enter infinite loop listening to events. The overridden function
	// WiimoteToLed::AccelerationEvent() will be invoked when the user moves
	// the Wiimote.
	wiimote_to_led.Listen();

	// Unreachable code, previous function has an infinite loop
	return 0;
}
