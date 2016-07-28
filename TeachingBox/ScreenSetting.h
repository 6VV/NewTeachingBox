#ifndef _SCREEN_SETTING_H_
#define _SCREEN_SETTING_H_

#include "ScreenMainParent.h"

class Button;
class QGroupBox;

class ScreenSetting:public ScreenMainParent
{
	friend class ScreenFactory;

private:
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