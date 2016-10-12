#ifndef _TEACHING_BOX_T_INTERPRETER_THREAD_H_
#define _TEACHING_BOX_T_INTERPRETER_THREAD_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TInterpreterThread.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/14
//  Description:	用于在
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"

class TInterpreterThread:public QObject
{
	Q_OBJECT

public slots:
	void SlotExecuteNextCommand();
	
	void SlotAutoExecute();
	void SlotStepExecute();
	void SlotStopExecute();

private:
	void SendEndCommand();
};

#endif