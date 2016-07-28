#ifndef _SCREEN_MAIN_H_
#define _SCREEN_MAIN_H_

#include "QStackedWidget"
#include "ScreenFactory.h"

class ScreenMain:public QStackedWidget
{
	Q_OBJECT

public:
	ScreenMain(QWidget* parent);
	~ScreenMain();

private:
	void Init();

private:
	ScreenFactory m_screenFactory;
};

#endif