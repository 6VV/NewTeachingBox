#ifndef _TEACHING_BOX_SCREEN_MAIN_H_
#define _TEACHING_BOX_SCREEN_MAIN_H_

#include "QStackedWidget"
#include <memory>

class ScreenFactory;

class ScreenMain:public QStackedWidget
{
	Q_OBJECT

public:
	ScreenMain(QWidget* parent);
	~ScreenMain();

private:
	void Init();

private:
	std::unique_ptr<ScreenFactory> m_screenFactory;
};

#endif