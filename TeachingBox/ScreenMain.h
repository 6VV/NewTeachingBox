#ifndef _SCREEN_MAIN_H_
#define _SCREEN_MAIN_H_

#include "InternationalWidget.h"

class ScreenMain:public InternationalWidget
{
public:
	ScreenMain(QWidget* parent=0);
	~ScreenMain();
	
private:
	virtual void UpdateText() override;

};

#endif