#ifndef _TEACHING_BOX_BUTTON_GROUP_H_
#define _TEACHING_BOX_BUTTON_GROUP_H_

#include "QWidget"

class QPushButton;
class QVBoxLayout;

class ButtonGroup:public QWidget
{
public:
	ButtonGroup(QList<QPushButton*>& btnlist, QPushButton* parentButton);
	~ButtonGroup();

private:
	void showEvent(QShowEvent *) override;

	void Init();

private:
	QList<QPushButton*> m_btnList;
	QVBoxLayout* m_layout;
	QPushButton* m_parentButton;
};

#endif