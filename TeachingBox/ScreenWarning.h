#ifndef _TEACHING_BOX_SCREEN_WARNING_H_
#define _TEACHING_BOX_SCREEN_WARNING_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenWarning.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/16
//  Description:    警告界面，显示警告信息。警告信息根据其严重程度分为不同类别，以不同颜色及图标显示。警告信息目前并不存储于数据库中。
		当出现警告时，会在本界面显示警告信息，警告信息级别分为普通信息、警告信息、错误信息，其严重程度依次增加。
		警告信息状态分为无需处理、未处理、已处理。普通信息无需处理，警告信息、错误信息需要处理，处理完某一问题后，点击Confirm键可将其状态设为已解决。
		警告信息上限为1000，当超过上限时，按照以下规则自动删除警告信息数据：
		（1）若存在普通信息或已解决信息，则按照时间顺序依次删除此类信息；
		（2）若无普通信息或已解决信息，则提示用户解决问题。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ScreenMainParent.h"
#include "QTableView"

class WarningModel;
class DateDelegate;

class ScreenWarning :public ScreenMainParent
{
	Q_OBJECT

public:
	ScreenWarning(QWidget* parent = nullptr);

private:
	virtual QList<QWidget*> GetButtonList() override;
	virtual QLayout* GetMainLayout() override;
	virtual void UpdateText() override;

private:
	QTableView* m_warningWidget;
	DateDelegate* m_dateDelegate;
	WarningModel* m_model;

	Button* m_btnConfirm;
	Button* m_btnConfirmAll;
	Button* m_btnDelete;
	Button* m_btnDeleteAll;
};

#endif