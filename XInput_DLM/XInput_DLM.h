/************************************************************************************
Copyright (c) Richie Zeng rfzeng@lbl.gov
Date: August 2011
Lawrence Berkeley National Lab

Allows the usage of XInput game controllers within IDL.

************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "export.h"
#pragma comment(lib, "XInput.lib")

#ifndef XINPUT_DLM_H
#define XINPUT_DLM_H


/* Handy macro to find the size of an array */
#define ARRLEN(arr) (sizeof(arr)/sizeof(arr[0]))

/*****XInput_Settings.cpp*****/
extern "C" {
//Updates the joystick and ensures it is connected
	IDL_VPTR JoyIsConnected(int argc, IDL_VPTR argv[], char *argk);

//Updates the joystick
	void JoyUpdate(int argc, IDL_VPTR argv[], char *argk);

//Gets the x,y value of the thumbsticks
	IDL_VPTR JoyGetLXY(int argc, IDL_VPTR argv[], char *argk);
	IDL_VPTR JoyGetRXY(int argc, IDL_VPTR argv[], char *argk);

//Gets the value of the two triggers
	IDL_VPTR JoyGetTrigger(int argc, IDL_VPTR argv[], char *argk);

//Gets the value of the DPAD ranging from 0-8 (going around in a circle)
	IDL_VPTR JoyGetDpad(int argc, IDL_VPTR argv[], char *argk);

//Gets the value of one specified button
	IDL_VPTR JoyGetOneButton(int argc, IDL_VPTR argv[], char *argk);

//Gets the value of all buttons in an array
//A,B,X,Y,LB,RB,LS,RS,Start,Back in that order
	IDL_VPTR JoyGetButtons(int argc, IDL_VPTR argv[], char *argk);

//Sets the vibration on both motors
	IDL_VPTR JoyVibrate(int argc, IDL_VPTR argv[], char *argk);

//Sets the vibration on the low frequenct (left) vibration motor
	IDL_VPTR JoyVibrateLow(int argc, IDL_VPTR argv[], char *argk);

//Sets the vibration on the high frequency (right) vibration motor
	IDL_VPTR JoyVibrateHigh(int argc, IDL_VPTR argv[], char *argk);

}

#endif
