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
#include "KeyboardInterface.h"

class Button;
class QGroupBox;
class QComboBox;
class QCheckBox;
class QLabel;
class User;

class ScreenSetting:public InternationalWidget,public KeyboardInterface
{
	Q_OBJECT
public:
	ScreenSetting(QWidget* parent);
	ScreenSetting(const ScreenSetting&);
	ScreenSetting& operator=(const ScreenSetting&);
	~ScreenSetting();

private:
	virtual void UpdateText() override;

	void UpdateState(const User& user);

	void Init();
	QGroupBox* CreateBoxLogin();
	QGroupBox* CreateBoxSystemSettings();
	QGroupBox* CreateBoxRobotControlAuthority();
	QGroupBox* CreateBoxLockScreenSetting();

private slots:
	void showEvent(QShowEvent *) override;
	void hideEvent(QHideEvent *event) override;

	void SlotChangeLanguage(int index);

	virtual void KeyboardEdit(const QString& text) override;

private:
	QGroupBox* m_groupboxLogin;
	QGroupBox* m_groupboxSystemSettings;
	QGroupBox* m_groupboxRobotControlAuthority;
	QGroupBox* m_groupboxDispaySettings;

	/*登录窗口*/
	QLabel* m_lbUser;
	QComboBox* m_cmbUser;
	QLabel* m_lbAuthority;
	QLineEdit* m_ltAuthorityValue;
	Button* m_btnLogout;

	/*系统窗口*/
	QLabel* m_lbLanguage;
	QComboBox* m_cmbLanguage;
	QLabel* m_lbDate;
	QLineEdit* m_ltDateValue;
	QLabel* m_lbTime;
	QLineEdit* m_ltTimeValue;

	/*机器人控制权限窗口*/
	QLabel* m_lbControlAuthority;
	QCheckBox* m_checkboxControlAuthority;
	QLabel* m_lbDevice;
	QLineEdit* m_ltDeviceValue;
	QLabel* m_lbDeviceIp;
	QLineEdit* m_ltDeviceIpValue;

	/*显示设置窗口*/
	QLabel* m_lbLockScreen;
	Button* m_btnLockScreen;
	QLabel* m_lbLockTime;
	QLineEdit* m_ltLockTimeValue;
};

#endif