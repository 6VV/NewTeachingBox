#include "stdafx.h"
#include "DialogNewAddress.h"
#include "Button.h"
#include "QBoxLayout"
#include "TeachingBoxContext.h"
#include "QRegExp"
#include "RegExp.h"
#include "WarningManager.h"
#include "IScreenNetwork.h"



DialogNewAddress::DialogNewAddress(QWidget* parent, IScreenNetwork* iScreenNetwork)
	:DialogParent(parent)
	, m_iScreenNetwork(iScreenNetwork)
	, m_lineEdit(new QLineEdit(this))
	, m_btnConfirm(new Button(this))
	, m_btnCancle(new Button(this))
{
	Init();
}

DialogNewAddress::~DialogNewAddress()
{

}

void DialogNewAddress::Init()
{
	InitLayout();
	InitSignalSlot();

	UpdateText();
}

inline
void DialogNewAddress::InitLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);

	m_btnConfirm->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
	m_btnCancle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

	QHBoxLayout* btnLayout = new QHBoxLayout(this);
	btnLayout->addStretch(1);
	btnLayout->addWidget(m_btnConfirm);
	btnLayout->addWidget(m_btnCancle);

	layout->addWidget(m_lineEdit);
	layout->addLayout(btnLayout);
}

inline
void DialogNewAddress::InitSignalSlot()
{
	connect(m_btnConfirm, SIGNAL(clicked()), this, SLOT(SlotOnConfirmClicked()));
	connect(m_btnCancle, SIGNAL(clicked()), this, SLOT(SlotOnCancleClicked()));
}

void DialogNewAddress::SlotOnConfirmClicked()
{
	QString address = m_lineEdit->text();

	if (!IsValidAddress(address))
	{
		WarningManager::Warning(this, "Wrong IP Address");
		return;
	}

	m_iScreenNetwork->OnNewAddress(address);

	Destory();
}

void DialogNewAddress::SlotOnCancleClicked()
{
	Destory();
}

bool DialogNewAddress::IsValidAddress(const QString& address)
{
	QRegExp regExp(RegExp::STR_REG_IP_ADDRESS);

	return regExp.exactMatch(address);
}

void DialogNewAddress::UpdateText()
{
	m_btnConfirm->setText(tr("Confirm"));
	m_btnCancle->setText(tr("Cancle"));
}

void DialogNewAddress::SetSize()
{
	QRect screenRect = TeachingBoxContext::GetInstance()->GetScreenRect();

	/*设置固定大小*/
	this->setFixedSize(screenRect.width() * 2 / 3, this->height());
}

inline
void DialogNewAddress::Destory()
{
	delete this;
}

