#include "stdafx.h"
#include "TIntegerWidget.h"
#include "TInteger.h"
#include "LineEditWithRegExpAndKeyboard.h"



TIntegerWidget::TIntegerWidget(TInteger* variate)
	:TVariateWidget(variate)
{

}

TIntegerWidget::~TIntegerWidget()
{

}

void TIntegerWidget::UpdateVariate()
{
	static_cast<TInteger*>(m_variate)->SetValue(m_value);
}

void TIntegerWidget::WriteContentToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList{ "Value" });

	auto value = static_cast<TInteger*>(m_variate)->GetValue();
	LineEditWithRegExpAndKeyboard* lineEditValue = new LineEditWithRegExpAndKeyboard(
		QString::number(value), RegExp::STR_REG_INT);

	treeWidget->setItemWidget(item, 1, lineEditValue);

	connect(lineEditValue, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnValueChanged()));
}

void TIntegerWidget::OnValueChanged()
{
	m_value = static_cast<QLineEdit*>(sender())->text().toInt();
	//static_cast<TInteger*>(m_variate)->SetValue(value);
}
