#ifndef _TEACHING_BOX_LABEL_WITH_BORDER_H_
#define _TEACHING_BOX_LABEL_WITH_BORDER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    LabelWithBorder.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	带边框的label控件，文本居中
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QLabel"

class LabelWithBorder :public QLabel
{
	Q_OBJECT

private:
	const int BORDER_WIDTH = 1;

protected:
	const QString ORIGIN_STYLE_SHEET = ".LabelWithBorder{border: "+QString::number(BORDER_WIDTH)+" groove gray; background-color: rgba(255, 193, 245, 0%);}";

public:
	LabelWithBorder(QWidget* parent = 0);
	LabelWithBorder(const QString& text, QWidget* parent = 0);
	virtual ~LabelWithBorder() = default;

	int GetBorderWidth() const;

private:
	void Init();
};

#endif