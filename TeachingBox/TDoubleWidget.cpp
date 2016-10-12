#include "stdafx.h"
#include "TDoubleWidget.h"
#include "TDouble.h"
#include "LineEditWithRegExpAndKeyboard.h"



TDoubleWidget::TDoubleWidget(TDouble* variate)
	:TVariateWidget(variate)
{

}

TDoubleWidget::~TDoubleWidget()
{

}

void TDoubleWidget::ReadContentTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	QTreeWidgetItem* item = new QTreeWidgetItem(parentItem, QStringList("Value"));

	auto value = static_cast<TDouble*>(m_variate)->GetValue();
	LineEditWithRegExpAndKeyboard* lineEditValue = new LineEditWithRegExpAndKeyboard(
		QString::number(value), RegExp::STR_REG_FLOAT);

	treeWidget->setItemWidget(item, 1, lineEditValue);

	connect(lineEditValue, SIGNAL(textChanged(const QString&)), this, SLOT(SlotOnValueChanged()));
}

void TDoubleWidget::OnValueChanged()
{
	auto value = static_cast<QLineEdit*>(sender())->text().toDouble();
	static_cast<TDouble*>(m_variate)->SetValue(value);
}
