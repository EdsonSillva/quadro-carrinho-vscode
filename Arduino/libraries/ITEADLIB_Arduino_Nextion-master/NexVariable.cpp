/**
 * @file NexVariable.cpp
 *
 * The implementation of class NexText. 
 *
 * @author  huang xiaoming (email:<xiaoming.huang@itead.cc>)
 * @date    2016/9/13
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */
#include "NexVariable.h"

NexVariable::NexVariable(uint8_t pid, uint8_t cid, const char *name)
    :NexTouch(pid, cid, name)
{
}

uint32_t NexVariable::getValue(uint32_t *number)
{
	String cmd = String("get ");
//    if(getObjName() ==  "")
//		cmd += String("p[") + getObjPid() + String("].b[") + getObjCid() + String("]");
//	else
		cmd += getObjName();
	cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

uint32_t NexVariable::getValueByID(uint32_t *number)
{
    String cmd = String("get ");
    cmd += String("p[") + getObjPid() + String("].b[") + getObjCid() + String("]");
    cmd += ".val";
    sendCommand(cmd.c_str());
    return recvRetNumber(number);
}

bool NexVariable::setValue(uint32_t number)
{
    char buf[10] = {0};
	String cmd;		// Original e o que parece esqueceram de incluir o comando set
    //String cmd = String("set ");
    
    utoa(number, buf, 10);
    cmd += getObjName();
    cmd += ".val=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

bool NexVariable::setValueByID(uint32_t number)
{
    char buf[10] = {0};
	String cmd;		
    
    utoa(number, buf, 10);
    cmd += String("p[") + getObjPid() + String("].b[") + getObjCid() + String("]");
    cmd += ".val=";
    cmd += buf;

    sendCommand(cmd.c_str());
    return recvRetCommandFinished();
}

uint32_t NexVariable::getText(char *buffer, uint32_t len)
{
    String cmd;
    cmd += "get ";
    cmd += getObjName();
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}

uint32_t NexVariable::getTextByID(char *buffer, uint32_t len)
{
    String cmd;
    cmd += "get ";
    cmd += String("p[") + getObjPid() + String("].b[") + getObjCid() + String("]");
    cmd += ".txt";
    sendCommand(cmd.c_str());
    return recvRetString(buffer,len);
}


bool NexVariable::setText(const char *buffer)
{
    String cmd;
    cmd += getObjName();
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}

bool NexVariable::setTextByID(const char *buffer)
{
    String cmd;
    cmd += String("p[") + getObjPid() + String("].b[") + getObjCid() + String("]");
    cmd += ".txt=\"";
    cmd += buffer;
    cmd += "\"";
    sendCommand(cmd.c_str());
    return recvRetCommandFinished();    
}