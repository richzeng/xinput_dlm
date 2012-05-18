/************************************************************************************
Copyright (c) Richie Zeng, rfzeng@lbl.gov
Lawrence Berkeley National Lab

Allows the usage of XInput game controllers within IDL.

************************************************************************************/

#include <windows.h>
#include <XInput.h> // XInput API

#include "XInput_DLM.h"



struct CONTROLER_STATE
{
  XINPUT_STATE state;
	XINPUT_VIBRATION vibration;
};

CONTROLER_STATE g_Controllers[4]; //can control up to 4 controllers

/*****Checks to see if the joystick is connected*****/
IDL_VPTR JoyIsConnected(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	bool isConnected = ((XInputGetState( id, &g_Controllers[id].state )) == ERROR_SUCCESS);
	return IDL_GettmpLong(isConnected);
}

/*****Gets the state of the specified controller*****/
void JoyUpdate(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	XInputGetState(id, &g_Controllers[id].state);
}

/*****Vibrates using both the left and right motors*****/
IDL_VPTR JoyVibrate(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	int power = IDL_LongScalar(argv[1]);
	
	g_Controllers[id].vibration.wLeftMotorSpeed = power;
	g_Controllers[id].vibration.wRightMotorSpeed = power;
	XInputSetState(id, &g_Controllers[id].vibration);

	return IDL_GettmpLong(1);
}

/*****Vibrates using the low frequency motor*****/
IDL_VPTR JoyVibrateLow(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	int power = IDL_LongScalar(argv[1]);
	
	g_Controllers[id].vibration.wLeftMotorSpeed = power;
	XInputSetState(id, &g_Controllers[id].vibration);
	return IDL_GettmpLong(1);
}

/*****Vibrates using the high frequency motor*****/
IDL_VPTR JoyVibrateHigh(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	int power = IDL_LongScalar(argv[1]);
	
	g_Controllers[id].vibration.wRightMotorSpeed = power;
	XInputSetState(id, &g_Controllers[id].vibration);
	return IDL_GettmpLong(1);
}

/*****Returns a 2 element array with the X,Y positions of the left thumbstick*****/
IDL_VPTR JoyGetLXY(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	short *coordArray;
	IDL_VPTR rtnArray;
	IDL_LONG n[IDL_MAX_ARRAY_DIM]; //3rd paramater of IDL_MakeTempArray must be of IDL_LONG[] type
	n[0]=2; //n becomes the size of the array in each of the dimensions
	coordArray = (short*) IDL_MakeTempArray(IDL_TYP_INT, 1, n, IDL_ARR_INI_ZERO, &rtnArray);
	coordArray[0] = g_Controllers[id].state.Gamepad.sThumbLX;
	coordArray[1] = g_Controllers[id].state.Gamepad.sThumbLY;
	return rtnArray;
}

/*****Returns a 2 element array with the X,Y positions of the right thumbstick*****/
IDL_VPTR JoyGetRXY(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	short *coordArray;
	IDL_VPTR rtnArray;
	IDL_LONG n[IDL_MAX_ARRAY_DIM]; //3rd paramater of IDL_MakeTempArray must be of IDL_LONG[] type
	n[0]=2;
	coordArray = (short*) IDL_MakeTempArray(IDL_TYP_INT, 1, n, IDL_ARR_INI_ZERO, &rtnArray);
	coordArray[0] = g_Controllers[id].state.Gamepad.sThumbRX;
	coordArray[1] = g_Controllers[id].state.Gamepad.sThumbRY;
	return rtnArray;
}

/*****Returns a 2 elelment array containing the values of the left and right trigger ranging from 0-255*****/
IDL_VPTR JoyGetTrigger(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	short *trgArray;
	IDL_VPTR rtnArray;
	IDL_LONG n[IDL_MAX_ARRAY_DIM];
	n[0]=2;
	trgArray = (short*) IDL_MakeTempArray(IDL_TYP_INT, 1, n, IDL_ARR_INI_ZERO, &rtnArray);
	trgArray[0] = g_Controllers[id].state.Gamepad.bLeftTrigger;
	trgArray[1] = g_Controllers[id].state.Gamepad.bRightTrigger;
	return rtnArray;
}

/*****Returns an int from 0-8 depending on which direction the D-Pad is pressed*****/
IDL_VPTR JoyGetDpad(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	WORD wButtons = g_Controllers[id].state.Gamepad.wButtons;

	bool right = ((wButtons & XINPUT_GAMEPAD_DPAD_RIGHT)!= 0);
	bool up = ((wButtons & XINPUT_GAMEPAD_DPAD_UP)!= 0);
	bool left = ((wButtons & XINPUT_GAMEPAD_DPAD_LEFT)!= 0);
	bool down = ((wButtons & XINPUT_GAMEPAD_DPAD_DOWN)!= 0);

	if (!right&&!left&&!up&&!down)
		return IDL_GettmpInt(0);
	else if (right && !up && !down)
		return IDL_GettmpInt(1);
	else if (right && up)
		return IDL_GettmpInt(2);
	else if (up && !right && !left)
		return IDL_GettmpInt(3);
	else if (up && left)
		return IDL_GettmpInt(4);
	else if (left && !up && !down)
		return IDL_GettmpInt(5);
	else if (left && down)
		return IDL_GettmpInt(6);
	else if (down && !left && !right)
		return IDL_GettmpInt(7);
	else if (down && right)
		return IDL_GettmpInt(8);
	else
		return IDL_GettmpInt(0);
}

/*****Returns a the value of one requested button as 0 or 1*****/
IDL_VPTR JoyGetOneButton(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	WORD wButtons = g_Controllers[id].state.Gamepad.wButtons;

	IDL_ENSURE_STRING(argv[1]);
	char button[10];
	strcpy(button,IDL_STRING_STR(&argv[1]->value.str));
	
	if (strcmp("A",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_A)!= 0);
	else if (strcmp("B",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_B)!= 0);
	else if (strcmp("X",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_X)!= 0);
	else if (strcmp("Y",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_Y)!= 0);
	else if (strcmp("LB",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)!= 0);
	else if (strcmp("RB",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)!= 0);
	else if (strcmp("LS",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_LEFT_THUMB)!= 0);
	else if (strcmp("RS",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)!= 0);
	else if (strcmp("Back",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_BACK)!= 0);
	else if (strcmp("Start",button)==0)
		return IDL_GettmpLong((wButtons & XINPUT_GAMEPAD_START)!= 0);
	else
		return IDL_GettmpLong(0);
}

/*****Returns a 10 element array of 0,1 values for 10 available buttons*****/
IDL_VPTR JoyGetButtons(int argc, IDL_VPTR argv[], char *argk)
{
	IDL_ENSURE_SCALAR(argv[0]);
	int id = IDL_LongScalar(argv[0]);
	WORD wButtons = g_Controllers[id].state.Gamepad.wButtons;
	short *coordArray;
	IDL_VPTR rtnArray;
	IDL_LONG n[IDL_MAX_ARRAY_DIM]; //3rd paramater of IDL_MakeTempArray must be of IDL_LONG[] type
	n[0]=10;
	coordArray = (short*) IDL_MakeTempArray(IDL_TYP_INT, 1, n, IDL_ARR_INI_ZERO, &rtnArray);
	
	coordArray[0] = ((wButtons & XINPUT_GAMEPAD_A)!= 0);
	coordArray[1] = ((wButtons & XINPUT_GAMEPAD_B)!= 0);
	coordArray[2] = ((wButtons & XINPUT_GAMEPAD_X)!= 0);
	coordArray[3] = ((wButtons & XINPUT_GAMEPAD_Y)!= 0);
	coordArray[4] = ((wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER)!= 0);
	coordArray[5] = ((wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER)!= 0);
	coordArray[6] = ((wButtons & XINPUT_GAMEPAD_LEFT_THUMB)!= 0);
	coordArray[7] = ((wButtons & XINPUT_GAMEPAD_RIGHT_THUMB)!= 0);
	coordArray[8] = ((wButtons & XINPUT_GAMEPAD_BACK)!= 0);
	coordArray[9] = ((wButtons & XINPUT_GAMEPAD_START)!= 0);

	return rtnArray;
}