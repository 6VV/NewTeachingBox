#ifndef _TEACHING_BOX_SCREEN_NETWORK_H_
#define _TEACHING_BOX_SCREEN_NETWORK_H_

#include "InternationalWidget.h"

class QListWidget;
class Button;

class ScreenNetwork:public InternationalWidget
{
	Q_OBJECT

public:
	ScreenNetwork(QWidget* parent);
	~ScreenNetwork();

private:
	virtual void UpdateText() override;

	void Init();
	void InitLayout();

private:
	QListWidget* m_listWidgetHost;
	Button* m_btnAdd;
	Button* m_btnDelete;
	Button* m_btnConnect;
};

#endif