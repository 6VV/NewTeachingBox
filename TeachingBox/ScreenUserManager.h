#ifndef _TEACHING_BOX_USER_MANAGER_H_
#define _TEACHING_BOX_USER_MANAGER_H_

#include "InternationalWidget.h"

class QTableWidget;
class Button;

class ScreenUserManager:public InternationalWidget
{
	Q_OBJECT

public:
	ScreenUserManager(QWidget* parent);
	~ScreenUserManager();

private:
	QLayout* GetButtonLayout();
	QLayout* GetMainLayout();

	void Init();
	void InitLayout();

	virtual void UpdateText() override;

private:
	const char* CLASS_NAME = "ScreenUserManager";

	QTableWidget* m_tableWidget;
	Button* m_btnEdit;
	Button* m_btnNew;
	Button* m_btnDelete;
};

#endif