#ifndef _TEACHING_BOX_DIALOG_EIDT_USER_H_
#define _TEACHING_BOX_DIALOG_EIDT_USER_H_

#include "DialogParent.h"

class QLabel;
class QLineEdit;
class QComboBox;
class Button;
class QCheckBox;

class IUserManager;

class DialogEidtUser:public DialogParent
{
	Q_OBJECT

public:
	enum OperatorType
	{
		ADD,
		EDIT,
	};

public:
	DialogEidtUser(QWidget* parent,IUserManager* userManager,OperatorType type,const QString& name="");

protected:
	void showEvent(QShowEvent *e) override;

private:
	virtual void UpdateText() override;
	virtual void SetSize() override;

	void Init();
	void InitLayout();
	void InitSignalSlot();
	void InitUser();

private slots:
	void SlotOnButtonConfirmClicked();
	void SlotOnButtonCancleClicked();

private:
	IUserManager* m_userManager;
	OperatorType m_type = OperatorType::ADD;
	QString m_oldName;

	QLabel* m_lbName;
	QLabel* m_lbPassword;
	QLabel* m_lbConfirmPassword;
	QLabel* m_lbAuthority;
	QLabel* m_lbLanguage;

	QLineEdit* m_lineEditName;
	QLineEdit* m_lineEditPassword;
	QLineEdit* m_lineEditConfirmPassword;
	QComboBox* m_comboBoxAuthority;
	QComboBox* m_comboBoxLanguage;

	Button* m_btnConfirm;
	Button* m_btnCancel;
};

#endif