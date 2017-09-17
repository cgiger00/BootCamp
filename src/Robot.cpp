#include <iostream>
#include <memory>
#include <string>

#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Lib830.h"
#include "input/GamepadF310.h"


class Robot: public frc::IterativeRobot {

public:
	/*
	enum is a user defined type (in this case an AutonMode), 
	that can only have a specific set of values 
	*/
	enum AutonMode { /* add enum values here */};

private:
		
		/*
		these are the number pins for the four motors that control the drive train,
		name and assign them the correct pins according to how the motors are plugged in 
		in the roboRIO 
		EX: static const int LEFT_FRONT_PWM = 0;
		*/
		static const int /*name*/ = /*int*/; 
		static const int /*name*/ = /*int*/; 
		static const int /*name*/ = /*int*/; 
		static const int /*name*/ = /*int*/; 

		/*
		FIRST provides us with a set of useful tools when it comes to programming, one of
		which is a class for driving the Robot called Robot Drive. 
		In order to use this class, we must make declare a RobotDrive object and give it a name
		*/

		/* 
		the * indicates that drive is a pointer, so this space in the computer memory 'points'
		to the actual 'value' of drive, used so we can call functions on the object, not copies
		of it
		*/
		RobotDrive *drive;

		/*
		Now we need to create controller objects, we use the class GamepadF310 for these,
		and typically name them pilot and copilot, for this we will only need a pilot
		*/
		
		Lib830::GamepadF310 * pilot;

		SendableChooser<AutonMode*> *chooser;

		Timer *timer;

		CameraServer *server;
		cs::UsbCamera camera;


	void RobotInit() {

		/* 
		we use the 'new' operator so that the objects we have made will outlive the current
		scope (so out side of RobotInit()), so they have dynamic allocation, until we 
		explicitly delete them
		*/

		/*
		VictorSPs are the type of motor controllers we use here, we also use others like 
		Victors, Talons, and Sparks, etc, but the computer doesn't know what motor to control
		so we have to give them the pin numbers, that we had named above
		*/

		drive = new RobotDrive(
			new VictorSP(/*name*/),
			new VictorSP(/*name*/),
			new VictorSP(/*name*/),
			new VictorSP(/*name*/)
		);

		pilot = new Lib830::GamepadF310(0);

		chooser = new SendableChooser<AutonMode*>();
		chooser->AddDefault("", new AutonMode(/*enum value*/));
		chooser->AddObject("", new AutonMode(/*enum value*/));
		SmartDashboard::PutData("Auton Modes", chooser);

		timer = new Timer();
		server = CameraServer::GetInstance();
		camera = server->StartAutomaticCapture();
	}

	/* 
	in auton we are going to make the robot drive forward for 5 seconds then stop OR
	do nothing depending on which option you choose
	*/
	void AutonomousInit() {
		timer->Reset();
		timer->Start();

	}

	void AutonomousPeriodic() {
		
		AutonMode mode = *chooser->GetSelected();

		float time = timer->Get();
		float speed = 0.0;

		if (mode == /*name*/) {
			if (time < 5.0) {
				speed = /*choose a value between 0.0 and 1.0*/;
			}
			else {
				speed = 0.0; /*this is redundant, think why it is*/
			}

		}

		/*
		arcade drive takes three arguments, speed, turn, and squared inputs (true or false,
		the choice of slower but more precise movement)
		*/
		drive->ArcadeDrive(/*speed*/, /*turn value*/, /*true/false*/);
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		/*
		we want to get the speed from the controller, so we can get it from the joystick,
		it returns a value between 0 and 1, which we can set to speed. 
		In order to get this value, you must reference the Gamepad object you made (called pilot),
		and call either the LeftY() or RightY() method
		*/
		float speed = /*pilot-> LeftY() OR pilot->RightY() OR idk whatever you guys want, you can be creative*/;
		/*
		the turn value is acquired in a similar fashion, but instead of Left/Right Y, use
		LeftX() or RightX()
		*/
		float turn = /* */;


		drive->ArcadeDrive(/*speed*/, /*turn*/, /*true/false*/);

		/*
		we put values on the smartdashboard usually when running programs, 
		using this syntax, make it so the driver can see the speed they are going at
		*/
		SmartDashboard::PutNumber("enter a name for this", /*get the current speed*/);

	}

	void TestPeriodic() {
	}


};

START_ROBOT_CLASS(Robot)
