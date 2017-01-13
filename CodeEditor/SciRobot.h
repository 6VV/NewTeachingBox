#ifndef _SCI_ROBOT_H_
#define _SCI_ROBOT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    SciRobot.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/13
//  Description:    自定义sciApi，用于控制自动完成
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/13
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "..\QScintilla_gpl-2.9.3\Qt4Qt5\Qsci\qsciapis.h"

class SciRobot :public QsciAPIs
{
	Q_OBJECT
public:
	SciRobot(QsciLexer* lexer);

	void updateKeywords(const QStringList& keywords);
	void updateVariates(const QStringList &entries);

private:
	QStringList m_keywords;
};

#endif