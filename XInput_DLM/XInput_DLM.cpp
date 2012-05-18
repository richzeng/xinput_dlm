/************************************************************************************
Copyright (c) Richie Zeng rfzeng@lbl.gov
Date: August 2011
Lawrence Berkeley National Lab

Allows the usage of XInput game controllers within IDL.

************************************************************************************/

#include "XInput_DLM.h"


int IDL_Load(void)
{
/*Call the startup function to add the routines to IDL.*/

	//functions in the strings are to be recognized by IDL and must be in all caps
	static IDL_SYSFUN_DEF2 XInput_functions[] = {
		{(IDL_FUN_RET)JoyGetLXY, "JOYGETLXY", 1, 1, 0, 0},
		{(IDL_FUN_RET)JoyGetRXY, "JOYGETRXY", 1, 1, 0, 0},
		{(IDL_FUN_RET)JoyGetDpad, "JOYGETDPAD", 1, 1, 0, 0},
		{(IDL_FUN_RET)JoyGetButtons, "JOYGETBUTTONS", 1, 1, 0, 0},
		{(IDL_FUN_RET)JoyGetOneButton, "JOYGETONEBUTTON", 2, 2, 0, 0},
		{(IDL_FUN_RET)JoyGetTrigger, "JOYGETTRIGGER", 1, 1, 0, 0},
		{(IDL_FUN_RET)JoyIsConnected, "JOYISCONNECTED", 1, 1, 0, 0},
		{(IDL_FUN_RET)JoyVibrate, "JOYVIBRATE", 2, 2, 0, 0},
		{(IDL_FUN_RET)JoyVibrateHigh, "JOYVIBRATEHIGH", 2, 2, 0, 0},
		{(IDL_FUN_RET)JoyVibrateLow, "JOYVIBRATELOW", 2, 2, 0, 0},
	};

	static IDL_SYSFUN_DEF2 XInput_procedures[] = {
		{(IDL_SYSRTN_GENERIC) JoyUpdate, "JOYUPDATE", 1, 1, 0, 0},
	};

	return IDL_SysRtnAdd(XInput_functions, IDL_TRUE, ARRLEN(XInput_functions)) &&
		IDL_SysRtnAdd(XInput_procedures, IDL_FALSE, ARRLEN(XInput_procedures));
}