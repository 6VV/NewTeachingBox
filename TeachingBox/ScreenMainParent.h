#ifndef _SCREEN_MAIN_PARENT_H_
#define _SCREEN_MAIN_PARENT_H_

#include "QList"
#include "InternationalWidget.h"

class QHBoxLayout;
class QPushButton;
class Button;

class ScreenMainParent:public InternationalWidget
{
private:
	const int HEAD_HEIGHT_RATIO = 6;
	const int BOTTOM_HEIGHT_RATIO = 1;

protected:
	const int BUTTON_MAX_NUM = 6;

public:
	ScreenMainParent(QWidget* parent);
	virtual ~ScreenMainParent();

protected:
	void UpdateButtonList(QList<QPushButton*> btnList);

private:
	void Init();

protected:
	QHBoxLayout* m_layoutMain;
	QHBoxLayout* m_layoutButtons;

private:
	Button* m_btnBack;
};

#endif