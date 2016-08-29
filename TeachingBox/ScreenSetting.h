#ifndef _SCREEN_SETTING_H_
#define _SCREEN_SETTING_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenSetting.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/01
//  Description:	登录界面，包括用户登录及系统基本设置方面
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/01
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class Button;
class QGroupBox;
class QComboBox;
class QCheckBox;
class QLabel;

class ScreenSetting:public InternationalWidget
{
	Q_OBJECT
public:
	ScreenSetting(QWidget* parent);
	ScreenSetting(const ScreenSetting&);
	ScreenSetting& operator=(const ScreenSetting&);
	~ScreenSetting();

private:
	virtual void UpdateText() override;

	void Init();
	QGroupBox* CreateBoxLogin();
	QGroupBox* CreateBoxSystemSettings();
	QGroupBox* CreateBoxRobotControlAuthority();
	QGroupBox* CreateBoxLockScreenSetting();

private slots:
	void showEvent(QShowEvent *) override;

	void SlotChangeLanguage(int index);

private:
	QGroupBox* m_groupboxLogin;
	QGroupBox* m_groupboxSystemSettings;
	QGroupBox* m_groupboxRobotControlAuthority;
	QGroupBox* m_groupboxDispaySettings;

	/*登录窗口*/
	QLabel* m_lbUser;
	QComboBox* m_cmbUser;
	QLabel* m_lbAuthority;
	QLabel* m_lbAuthorityValue;
	Button* m_btnLogout;

	/*系统窗口*/
	QLabel* m_lbLanguage;
	QComboBox* m_cmbLanguage;
	QLabel* m_lbDate;
	QLabel* m_lbDateValue;
	QLabel* m_lbTime;
	QLabel* m_lbTimeValue;

	/*机器人控制权限窗口*/
	QLabel* m_lbControlAuthority;
	QCheckBox* m_checkboxControlAuthority;
	QLabel* m_lbDevice;
	QLabel* m_lbDeviceValue;
	QLabel* m_lbDeviceIp;
	QLabel* m_lbDeviceIpValue;

	/*显示设置窗口*/
	QLabel* m_lbLockScreen;
	Button* m_btnLockScreen;
};

#endif