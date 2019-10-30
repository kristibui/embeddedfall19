#include "GPIO.h"
#include "ZedBoard.h"
#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;

int main()
{
	
	/**
	int servo, start_position, end_position, rot_speed;
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
	cout << "Enter start position for servo in degrees:" << endl;
	cin >> start_position;
	if (start_position < 0 || start_position > 180) {
		cout << "Invalid position range" << endl;
		return 0;
	}

	cout << "Enter end position for servo in degrees:" << endl;
        cin >> end_position;
        if (end_position < 0 || end_position > 180) {
                cout << "Invalid position range" << endl;
                return 0;
        }

	cout << "Enter rotational speed in degrees per second:" << endl;
        cin >> rot_speed;
        if (start_position < 0 || end_position > 180) {
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
	while (true) {

		GPIO gpio(13);

		int start_on_time, end_on_time, start_position, end_position;
		start_position = 90;
		end_position = 90;
		start_on_time = (start_position * 10) + 600;
		end_on_time = (end_position * 10) + 600;
		// Generate PWM signal with 20ms period and 1.5ms on time.
		// Generate 400 periods, this will take 20ms * 400 iterations = 8s
		int periods, time, rot_speed;
		rot_speed = 15;
		time = (end_position - start_position) /  rot_speed;
		periods = time /  0.02;
	
		gpio.GeneratePWM(20000, start_on_time, 400);
	}
	**/
	
	// Done
	ZedBoard *zed_board = new ZedBoard;

	int ports[5] = {13, 10, 11, 12, 0};
	GPIO gpio13(ports[0]);
	GPIO gpio10(ports[1]);
	GPIO gpio11(ports[2]);
	GPIO gpio12(ports[3]);
        GPIO gpio0(ports[4]);

        int base_on_time, others_on_time, base_position, bicep_position;
	int wrist_on_time, wrist_position;
        base_position = 70;
	bicep_position = 90;
	wrist_position = 80;
	/**elbow_position = 90;
	wrist_position = 90;
        end_position = 90;**/
        base_on_time = (base_position * 10) + 600;
	wrist_on_time = (wrist_position * 10) + 600;
        others_on_time = (bicep_position * 10) + 600;

        // Generate PWM signal with 20ms period and 1.5ms on time.
        // Generate 400 periods, this will take 20ms * 400 iterations = 8s
        int periods, time, rot_speed;
        rot_speed = 15;
        //time = (end_position - start_position) /  rot_speed;
        //periods = time /  0.02;
	int userButton = zed_board->PushButtonGet();

	//cout << userButton << endl;
	while (zed_board->PushButtonGet() == 0) {
		//userButton = zed_board->PushButtonGet();
		cout << userButton << endl;
		//if (userButton == 0) {
		thread tbase(&GPIO::GeneratePWM, &gpio13, 20000, base_on_time, 100); 
		thread tbicep(&GPIO::GeneratePWM, &gpio10, 20000, others_on_time, 100);
		thread telbow(&GPIO::GeneratePWM, &gpio11, 20000, wrist_on_time, 100);
		thread twrist(&GPIO::GeneratePWM, &gpio12, 20000, wrist_on_time, 100);
	
		tbase.join();
		tbicep.join();
		telbow.join();
		twrist.join();
		/**} else if (userButton  == 5) {
			thread tbicep(&GPIO::GeneratePWM, &gpio10, 20000, end_on_time, 400);

			cout << "we here" << endl;
			//break;
		}**/
		//userButton = zed_board->PushButtonGet();
        }
	int bicep_end_time, base_end_time, wrist_end_time, gripper_end_time;
        bicep_end_time = (60 * 10) + 600;
	base_end_time = (120 * 10) + 600;
	wrist_end_time = (20 * 10) + 600;
	gripper_end_time = (40 * 10) + 600;
	//if (userButton  == 5) {
		thread tbase(&GPIO::GeneratePWM, &gpio13, 30000, base_end_time, 400);
        	thread tbicep(&GPIO::GeneratePWM, &gpio10, 60000, bicep_end_time, 800);
		thread telbow(&GPIO::GeneratePWM, &gpio11, 60000, bicep_end_time, 800);
                thread twrist(&GPIO::GeneratePWM, &gpio12, 60000, wrist_end_time, 800);
		//thread tgripper(&GPIO::GeneratePWM, &gpio0, 30000, gripper_end_time, 400);
		tbase.join();
                tbicep.join();
                telbow.join();
                twrist.join();
		gpio0.GeneratePWM(30000, gripper_end_time, 400);
		//tgripper.join();
                 //       cout << "we here" << endl;
	//}
	//gpio12.GeneratePWM(20000, start_on_time, 400);

	cout << "HERE" << endl;
	//gpio11.GeneratePWM(20000, start_on_time, 300);
	//gpio10.GeneratePWM(20000, start_on_time, 200);
	//gpio10.GeneratePWM(20000, start_on_time, 400);

	return 0;
}
