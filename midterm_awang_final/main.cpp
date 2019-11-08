#include "GPIO.h"
#include "ZedBoard.h"
#include <iostream>
#include <stdlib.h>
#include <thread>
using namespace std;

int main()
{

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

  	base_on_time = (base_position * 10) + 600;
	wrist_on_time = (wrist_position * 10) + 600;
  	others_on_time = (bicep_position * 10) + 600;

  	int periods, time, rot_speed;
  	rot_speed = 15;

	int userButton = zed_board->PushButtonGet();

	// Wait for user to press center button on ZedBoard, arm is up straight
	while (zed_board->PushButtonGet() == 0) {

		cout << userButton << endl;

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
	}

	// 1) Grab the first bottle
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

	tbase.join();
  	tbicep.join();
  	telbow.join();
  	twrist.join();

	wrist_end_time = (145 * 10) + 600;

	thread tbasegrab(&GPIO::GeneratePWM, &gpio13, 10000, base_end_time, 100);
  	thread tbicepgrab(&GPIO::GeneratePWM, &gpio10, 10000, bicep_end_time, 100);
  	thread telbowgrab(&GPIO::GeneratePWM, &gpio11, 10000, elbow_end_time, 100);
	thread twristgrab(&GPIO::GeneratePWM, &gpio12, 10000, wrist_end_time, 100);
	thread tgrip(&GPIO::GeneratePWM, &gpio0, 10000, gripper_end_time, 100);

	tbasegrab.join();
	tbicepgrab.join();
	telbowgrab.join();
	twristgrab.join();
	tgrip.join();

	// Robot has grabbed first bottle

	elbow_end_time = (60 *10) + 600;
	wrist_end_time = (20 * 10) + 600;
	bicep_end_time = (80 * 10) + 600;
	base_end_time = (90 * 10) + 600;

	// 2) Throw the first bottle
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

	// 3) Grab the second bottle
	thread tbasegrab2(&GPIO::GeneratePWM, &gpio13, 20000, base_end_time, 100);
	thread tbicepgrab2(&GPIO::GeneratePWM, &gpio10, 20000, bicep_end_time, 100);
	thread telbowgrab2(&GPIO::GeneratePWM, &gpio11, 20000, elbow_end_time, 100);
  	thread twristgrab2(&GPIO::GeneratePWM, &gpio12, 20000, wrist_end_time, 100);

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

	// 4) Throw the second bottle
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

	return 0;
}
