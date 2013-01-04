#pragma config(Hubs,  S1, HTMotor,  HTMotor,  none,     none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     sensor_1,       sensorNone)
#pragma config(Sensor, S3,     sensor_2,       sensorNone)
#pragma config(Sensor, S4,     sensor_3,       sensorNone)
#pragma config(Motor,  motorA,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorB,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  motorC,           ,             tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C1_1,     FrontL,        tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C1_2,     FrontR,        tmotorTetrix, openLoop, reversed)
#pragma config(Motor,  mtr_S1_C2_1,     RearL,         tmotorTetrix, openLoop)
#pragma config(Motor,  mtr_S1_C2_2,     RearR,         tmotorTetrix, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

// Code generated by 'ROBOTC' configuration wizard
#include "JoystickDriver.c"  //Include file to "handle" the Bluetooth messages.
#include "global vars-6121.h"
#include "enums-6121.h"
#include "low-level functions-6121.h"
#include "high-level functions-6121.h"

// Reconcile the joystick scale of 0 to 128
// with the Motor scale of 0 to 100
int scaleForMotor(int joyValue)
{
	// Note that the Motor can take a max value of 100
  // But we're playing it safe and staying at 80 only
	const int MAX_MOTOR_VAL = 80;

	// The joystick value is +127 to -128
	const float MAX_JOY_VAL = 128;

	const int DEADZONE = 15;

	if (abs(joyValue) < DEADZONE)
		return 0;

	int direction = joyValue / abs(joyValue);
	float ratio = ( (joyValue * joyValue) / (MAX_JOY_VAL * MAX_JOY_VAL) );
	int scaledVal = (ratio * MAX_MOTOR_VAL) * direction;

	return scaledVal;
}


task main()
{
	// CATH: Make sure you choose "Joystick Control - Competition"
  // This is in (Robot)->(Debugger Windows)->
	waitForStart();

	int powerL = 0;
	int powerR = 0;
	int liftPower = 0;

	while (true)
	{
		Joystick_UpdateData();

		// These should be zeroed after every loop. In the case that there
		// isn't input, the robot won't keep moving at the last speed it had.
		powerL = 0;
		powerR = 0;

		//Put something in the NXT LCD screen (just for grins)
		nxtDisplayTextLine(2, "Catherine Program");

		/*
		// Y-axis code:
		if ( 	abs(joystick.joy1_y1) > g_JoystickThreshold ||
				abs(joystick.joy1_y2) > g_JoystickThreshold )
		{
			powerL = joystick.joy1_y1;
			powerR = joystick.joy1_y2;
		}

		// Last check: if LB/RB is pressed, fine-tune the power level.
		if ( (Joystick_Button(BUTTON_LB)||Joystick_Button(BUTTON_RB)) ==true )
		{
			powerL /= g_FineTuneFactor;
			powerR /= g_FineTuneFactor;
		}
		if (Joystick_Button(BUTTON_X)) {
			liftPower = 75;
		}
		else if (Joystick_Button(BUTTON_A)) {
			liftPower = -75;
		}
		else {
			liftPower = 0;
		}
		if (Joystick_Button(BUTTON_LT)) {
			liftPower *= 2;
		}
		*/

		/*
		//CATH: New code
		//Control the FrontL and FrontR motors using the LT,RT,LB,RB buttons
		//LB & RB to go forward
		//LT & RT to go backward
		//*
		powerL = powerR = 0;
		if (Joystick_Button(BUTTON_LT)) {
			powerL = 80;
		}
		if (Joystick_Button(BUTTON_RT)) {
			powerR = 80;
		}
			if (Joystick_Button(BUTTON_LB)) {
			powerL = -80;
		}
		if (Joystick_Button(BUTTON_RB)) {
			powerR = -80;
		}
		*/



/*
		//CATH: New code
		//Control the FrontL and FrontR motors using the Top Hat
		powerL = powerR = 0;
		if(joystick.joy1_TopHat == 0) {
  		powerL = powerR = -50; //forward
  		nxtDisplayTextLine(0, "forward");
		} else if(joystick.joy1_TopHat == 4) {
			powerL = powerR = 50; //reverse
  		nxtDisplayTextLine(0, "reverse");
  	} else if(joystick.joy1_TopHat == 6) {
  		powerL =  50; //backward
  		powerR = -50; //forward
  		nxtDisplayTextLine(0, "left turn");
  	} else if(joystick.joy1_TopHat == 2) {
  	  powerL = -50; //forward
  		powerR =  50; //backward
  		nxtDisplayTextLine(0, "right turn");
		} else {
  		powerL = powerR = 0; //off
  		nxtDisplayTextLine(0, "stop");
		}
*/


		//CATH: New code
		//Control the FrontL and FrontR motors using the joysticks.
		//One joystick for the left; the other for the right.
    powerL = -1 * scaleForMotor(joystick.joy1_y1);
    powerR = -1 * scaleForMotor(joystick.joy1_y2);

    // Last check: if LB/RB is pressed, fine-tune the power level.
		if ( (Joystick_Button(BUTTON_LB)||Joystick_Button(BUTTON_RB)) ==true )
		{
			powerL /= g_FineTuneFactor;
			powerR /= g_FineTuneFactor;
		}

    nxtDisplayTextLine(3, "Left  is %d", powerL);
    nxtDisplayTextLine(4, "Right is %d", powerR);



		// These are the ones closest to the motor controllers
		Motor_SetPower(FrontL, powerL);
		Motor_SetPower(FrontR, powerR);

		// These are the ones closest to the NXT.
		// Controlled by the A and X buttons.
		Motor_SetPower(RearL, powerL);
		Motor_SetPower(RearR, powerR);
	}
}