#include "stdafx.h"
#include "ScreenUser.h"
#include "QTableWidget"
#include "TeachingBoxContext.h"



ScreenUser::ScreenUser(QWidget* parent)
	:InternationalWidget(parent)
	, m_tableWidget(new QTableWidget(this))
{
	Init();
}

ScreenUser::~ScreenUser()
{

}

void ScreenUser::showEvent(QShowEvent *)
{
	User user = TeachingBoxContext::GetInstance()->GetUser();
	m_tableWidget->setItem(0, 0, new QTableWidgetItem(user.GetName()));
	m_tableWidget->setItem(0, 2, new QTableWidgetItem(QString::number(user.GetAuthority())));
}

void ScreenUser::UpdateText()
{
	/*添加表头*/
	QStringList strList;
	strList << QCoreApplication::translate(CLASS_NAME,"User")
		<< QCoreApplication::translate(CLASS_NAME, "Address")
		<< QCoreApplication::translate(CLASS_NAME, "Authority")
		<< QCoreApplication::translate(CLASS_NAME, "Control");
	m_tableWidget->setHorizontalHeaderLabels(strList);
}

void ScreenUser::Init()
{
	/*平均分布各行*/
	m_tableWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	/*设置行列*/
	m_tableWidget->setRowCount(1);
	m_tableWidget->setColumnCount(4);

	QHBoxLayout* layoutMain = new QHBoxLayout(this);
	layoutMain->setMargin(0);
	layoutMain->addWidget(m_tableWidget);

	UpdateText();
}
