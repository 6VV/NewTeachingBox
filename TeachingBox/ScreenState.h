#ifndef _SCREEN_HEAD_H_
#define _SCREEN_HEAD_H_

#include "InternationalWidget.h"
#include "QLabel"

class Layout;

class ScreenState:public InternationalWidget
{
public:
	ScreenState(QWidget* parent=0);
	~ScreenState();

private:
	virtual void UpdateText() override;

	void Init();
	void InitLayout();
	QLayout* GetFirstLayout();
	QLayout* GetSecondLayout();

private:
	class LabelWithBorder :public QLabel
	{
	public:
		LabelWithBorder(QWidget* parent = 0);
		LabelWithBorder(const QString& text, QWidget* parent = 0);

	private:
		void Init();
	};

	LabelWithBorder* m_lbOperationMode;	/*操作模式*/
	LabelWithBorder* m_lbServo;			/*机器人状态*/
	LabelWithBorder* m_lbCoordinate;		/*参考坐标系*/
	LabelWithBorder* m_lbTool;			/*工具手*/
	LabelWithBorder* m_lbSpeedPersent;	/*机器人速度*/
	LabelWithBorder* m_lbLogo;			/*商标*/

	LabelWithBorder* m_lbProjectAndProgram;		/*项目与程序*/
	LabelWithBorder* m_lbProgramState;			/*程序状态*/
	LabelWithBorder* m_lbProgramRunningMode;		/*同上*/
	LabelWithBorder* m_lb3;				/*用户自定义*/
	LabelWithBorder* m_lb4;				/*同上*/
	LabelWithBorder* m_lb5;				/*同上*/
	LabelWithBorder* m_lbSpace;			/*空间监控*/
	LabelWithBorder* m_lbSecurityState;	/*安全状态*/
	LabelWithBorder* m_lbUserAuthority;	/*用户权限*/
	LabelWithBorder* m_lbCurrentTime;	/*当前时间*/
};

#endif