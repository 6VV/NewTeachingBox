#ifndef _TEACHING_BOX_BUTTON_GROUP_H_
#define _TEACHING_BOX_BUTTON_GROUP_H_

#include "QWidget"

class Button;
class QVBoxLayout;

class ButtonGroup:public QWidget
{
public:
	ButtonGroup(QList<Button*>& btnlist, Button* parentButton);
	~ButtonGroup();

private:
	void showEvent(QShowEvent *);

	void Init();

private:
	QList<Button*> m_btnList;
	QVBoxLayout* m_layout;
	Button* m_parentButton;
};

#endif