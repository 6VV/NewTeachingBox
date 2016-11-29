#ifndef _TEACHING_BOX_REMOTE_PARSER_H_
#define _TEACHING_BOX_REMOTE_PARSER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RemoteParser.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/10
//  Description:	用于解析远程控制器发来的指令
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/10
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"
#include "DataStruct.h"

class RemoteParser:public QObject
{
	Q_OBJECT

public:
	RemoteParser(QObject* parent=nullptr);
	~RemoteParser();

	void ParseCommands(QByteArray& commands) const;
	
private:
	void ParseOneCommand(QByteArray& command) const;
	tTeachCmdAttribute* GetAttribute(char* command) const;
	void SplitCommand(QList<QByteArray>& commandList, QByteArray& commands) const;

	void SendNextCommand() const;		/*发送下一条指令*/
	void RefreshLineNumber(const tTeachCmdAttribute& attribute) const;	/*命令反馈*/
	void OnReceivePosition(QByteArray& command) const;	/*获取位置*/
};

#endif