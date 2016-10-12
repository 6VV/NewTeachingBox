#include "stdafx.h"
#include "TBoolWidget.h"
#include "TBool.h"



const QString TBoolWidget::STR_VALUE_TRUE = "TRUE";
const QString TBoolWidget::STR_VALUE_FALSE = "FALSE";

TBoolWidget::TBoolWidget(TBool* variate)
	:TVariateWidget(variate)
{

}

TBoolWidget::~TBoolWidget()
{

}

void TBoolWidget::ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList("Value"));

	QComboBox* comboValue = new QComboBox;
	comboValue->addItem(STR_VALUE_FALSE);
	comboValue->addItem(STR_VALUE_TRUE);

	auto value = static_cast<TBool*>(m_variate)->GetValue();

	if (value == true)
	{
		comboValue->setCurrentText(STR_VALUE_TRUE);
	}
	else
	{
		comboValue->setCurrentText(STR_VALUE_FALSE);
	}

	treeWidget->setItemWidget(item, 1, comboValue);

	connect(comboValue, SIGNAL(currentIndexChanged(const QString&)),
		this, SLOT(SlotOnValueChanged()));
}

void TBoolWidget::OnValueChanged()
{
	auto text = static_cast<QComboBox*>(sender())->currentText();
	bool value = false;

	if (text == STR_VALUE_TRUE)
	{
		value = true;
	}

	static_cast<TBool*>(m_variate)->SetValue(value);
}
