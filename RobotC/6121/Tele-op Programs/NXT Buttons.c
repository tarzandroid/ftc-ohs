#pragma config(Hubs,  S1, HTServo,  HTMotor,  HTMotor,  none)
#pragma config(Sensor, S1,     ,               sensorI2CMuxController)
#pragma config(Sensor, S2,     infrared,       sensorHiTechnicIRSeeker1200)
#pragma config(Sensor, S3,     weight,         sensorLightInactive)
#pragma config(Sensor, S4,     touch,          sensorTouch)
#pragma config(Motor,  motorA,          motor_A,       tmotorNXT, openLoop)
#pragma config(Motor,  motorB,          motor_B,       tmotorNXT, openLoop)
#pragma config(Motor,  motorC,          motor_C,       tmotorNXT, openLoop)
#pragma config(Motor,  mtr_S1_C2_1,     motor_L,       tmotorTetrix, PIDControl, reversed, encoder)
#pragma config(Motor,  mtr_S1_C2_2,     motor_R,       tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_1,     motor_lift,    tmotorTetrix, PIDControl, encoder)
#pragma config(Motor,  mtr_S1_C3_2,     motor_G,       tmotorTetrix, openLoop)
#pragma config(Servo,  srvo_S1_C1_1,    servo_IR,             tServoStandard)
#pragma config(Servo,  srvo_S1_C1_2,    servo_force,          tServoStandard)
#pragma config(Servo,  srvo_S1_C1_3,    servo_ramp,           tServoStandard)
#pragma config(Servo,  srvo_S1_C1_4,    servo4,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_5,    servo5,               tServoNone)
#pragma config(Servo,  srvo_S1_C1_6,    servo6,               tServoNone)
// Code generated by 'ROBOTC' configuration wizard


task main()
{
	while (true)
	{
		if (nNxtButtonPressed == 3)	//orange button
		{
			motor[motor_L] = 100;
			motor[motor_R] = 100;
			wait1Msec(100);
			motor[motor_L] = 0;
			motor[motor_R] = 0;
		}
		if (nNxtButtonPressed == 2)	//left arrow button
		{
			motor[motor_L] = -100;
			motor[motor_R] = 100;
			wait1Msec(100);
			motor[motor_L] = 0;
			motor[motor_R] = 0;
		}
		if (nNxtButtonPressed == 1)	//right arrow button
		{
			motor[motor_L] = 100;
			motor[motor_R] = -100;
			wait1Msec(100);
			motor[motor_L] = 0;
			motor[motor_R] = 0;
		}
	}
}