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
		thread tgripper(&GPIO::GeneratePWM, &gpio0, 20000, wrist_on_time, 100);
		tbase.join();
		tbicep.join();
		telbow.join();
		twrist.join();
		tgripper.join();
		/**} else if (userButton  == 5) {
			thread tbicep(&GPIO::GeneratePWM, &gpio10, 20000, end_on_time, 400);

			cout << "we here" << endl;
			//break;
		}**/
		//userButton = zed_board->PushButtonGet();
        }
	// grab first bottle
	int bicep_end_time, base_end_time, elbow_end_time, wrist_end_time, gripper_end_time;
        bicep_end_time = (90 * 10) + 600;
	base_end_time = (120 * 10) + 600;
	wrist_end_time = (120 * 10) + 600;
	gripper_end_time = (30 * 10) + 600;
	elbow_end_time = (135 * 10) + 600; 
	thread tbase(&GPIO::GeneratePWM, &gpio13, 30000, base_end_time, 100);
       	thread tbicep(&GPIO::GeneratePWM, &gpio10, 30000, bicep_end_time, 100);
	thread telbow(&GPIO::GeneratePWM, &gpio11, 30000, elbow_end_time, 100);
        thread twrist(&GPIO::GeneratePWM, &gpio12, 30000, wrist_end_time, 100);
		//thread tgripper(&GPIO::GeneratePWM, &gpio0, 60000, wrist_on_time, 800);
	tbase.join();
        tbicep.join();
        telbow.join();
        twrist.join();
		//tgripper.join();

		//gpio12.GeneratePWM(30000, wrist_end_time, 100);
		//gpio0.GeneratePWM(30000, gripper_end_time, 400);
	//thread tbase1(&GPIO::GeneratePWM, &gpio13, 30000, base_end_time, 100);
        //thread tbicep1(&GPIO::GeneratePWM, &gpio10, 30000, bicep_end_time, 100);
        //thread telbow1(&GPIO::GeneratePWM, &gpio11, 30000, bicep_end_time, 100);
	wrist_end_time = (145 * 10) + 600;
	thread tbasegrab(&GPIO::GeneratePWM, &gpio13, 10000, base_end_time, 100);
        thread tbicepgrab(&GPIO::GeneratePWM, &gpio10, 10000, bicep_end_time, 100);
        thread telbowgrab(&GPIO::GeneratePWM, &gpio11, 10000, elbow_end_time, 100);
	thread twristgrab(&GPIO::GeneratePWM, &gpio12, 10000, wrist_end_time, 100);
		//twrist.join();
	thread tgrip(&GPIO::GeneratePWM, &gpio0, 10000, gripper_end_time, 100);
	tbasegrab.join();
	tbicepgrab.join();
	telbowgrab.join();
	twristgrab.join();
	tgrip.join();
	// grabbed first bottle
	
	elbow_end_time = (60 *10) + 600;
	wrist_end_time = (20 * 10) + 600;
	//gripper_end_time = (70 * 10) + 600;
	bicep_end_time = (80 * 10) + 600;
	base_end_time = (90 * 10) + 600;
	thread tbasethrow1(&GPIO::GeneratePWM, &gpio13, 20000, base_end_time, 50);
        thread tbicepthrow1(&GPIO::GeneratePWM, &gpio10, 20000, bicep_end_time, 50);
	thread telbowthrow1(&GPIO::GeneratePWM, &gpio11, 20000, elbow_end_time, 50);
        thread twristthrow1(&GPIO::GeneratePWM, &gpio12, 20000, wrist_end_time, 50);
	thread tgripthrow1before(&GPIO::GeneratePWM, &gpio0, 5000, gripper_end_time, 80);

	gripper_end_time = (70 * 10) + 600;
	thread tgripthrow1(&GPIO::GeneratePWM, &gpio0, 20000, gripper_end_time, 50);
	tgripthrow1before.join();
	tbasethrow1.join();
	tbicepthrow1.join();
	telbowthrow1.join();
	twristthrow1.join();
	tgripthrow1.join();

	elbow_end_time = (40 * 10) + 600;
	gripper_end_time = (30 * 10) + 600;
	wrist_end_time = (10 * 10) + 600;
	thread tbasegrab2(&GPIO::GeneratePWM, &gpio13, 20000, base_end_time, 100);
	thread tbicepgrab2(&GPIO::GeneratePWM, &gpio10, 20000, bicep_end_time, 100);
	thread telbowgrab2(&GPIO::GeneratePWM, &gpio11, 20000, elbow_end_time, 100);
        thread twristgrab2(&GPIO::GeneratePWM, &gpio12, 20000, wrist_end_time, 100);
		//thread tgripgrab2(&GPIO::GeneratePWM, &gpio0, 20000, gripper_end_time, 100);
	tbasegrab2.join();
	tbicepgrab2.join();
	telbowgrab2.join();
	twristgrab2.join();


	thread tbasegrab21(&GPIO::GeneratePWM, &gpio13, 20000, base_end_time, 100);
        thread tbicepgrab21(&GPIO::GeneratePWM, &gpio10, 20000, bicep_end_time, 100);
        thread telbowgrab21(&GPIO::GeneratePWM, &gpio11, 20000, elbow_end_time, 100);
	thread twristgrab21(&GPIO::GeneratePWM, &gpio12, 20000, wrist_end_time, 100);
	thread tgripgrab2(&GPIO::GeneratePWM, &gpio0, 20000, gripper_end_time, 100);
	tbasegrab21.join();
        tbicepgrab21.join();
        telbowgrab21.join();
	twristgrab21.join();
	tgripgrab2.join();

	base_end_time = (60 * 10) + 600;
	wrist_end_time = (60 * 10) + 600;
	elbow_end_time = (70 * 10) + 600;
	bicep_end_time = (50 * 10) + 600;
	//gripper_end_time = (70 * 10) + 600;
	thread tgripthrow2before(&GPIO::GeneratePWM, &gpio0, 5000, gripper_end_time, 50);
	thread tbasethrow2(&GPIO::GeneratePWM, &gpio13, 20000, base_end_time, 100);
        thread tbicepthrow2(&GPIO::GeneratePWM, &gpio10, 20000, bicep_end_time, 100);
        thread telbowthrow2(&GPIO::GeneratePWM, &gpio11, 20000, elbow_end_time, 100);
        thread twristthrow2(&GPIO::GeneratePWM, &gpio12, 20000, wrist_end_time, 60);
	gripper_end_time = (70 * 10) + 600;
	thread tgripthrow2(&GPIO::GeneratePWM, &gpio0, 20000, gripper_end_time, 100);
	
	tgripthrow2before.join();
	tbasethrow2.join();
	tbicepthrow2.join();
	telbowthrow2.join();
	twristthrow2.join();
	tgripthrow2.join();
	//tbasethrow1.join();
	//tbicepthrow1.join();
	         //       cout << "we here" << endl;
	//}
	//gpio12.GeneratePWM(20000, start_on_time, 400);

	cout << "HERE" << endl;
	//gpio11.GeneratePWM(20000, start_on_time, 300);
	//gpio10.GeneratePWM(20000, start_on_time, 200);
	//gpio10.GeneratePWM(20000, start_on_time, 400);

	return 0;
}
