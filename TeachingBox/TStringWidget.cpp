#include "stdafx.h"
#include "TStringWidget.h"
#include "TString.h"



TStringWidget::TStringWidget(TString* variate)
	:TVariateWidget(variate)
{

}

TStringWidget::~TStringWidget()
{

}

void TStringWidget::ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList("Value"));

	QLineEdit* lineEditValue = new QLineEdit(static_cast<TString*>(m_variate)->GetValue());

	treeWidget->setItemWidget(item, 1, lineEditValue);

	connect(lineEditValue, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnValueChanged()));
}

void TStringWidget::OnValueChanged()
{
	static_cast<TString*>(m_variate)->SetValue(static_cast<QLineEdit*>(sender())->text());
}
