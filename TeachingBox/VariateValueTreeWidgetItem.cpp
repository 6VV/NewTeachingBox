#include "stdafx.h"
#include "VariateValueTreeWidgetItem.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "RegExp.h"
#include "TSymbol.h"
#include "TreeWidgetItemWithSymbol.h"
#include "TVariateManager.h"
#include <assert.h>



VariateValueTreeWidgetItem::~VariateValueTreeWidgetItem()
{
}


void VariateValueTreeWidgetItem::InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	InsertVariateValue(variate, treeWidget, variateItem);

}

void VariateValueTreeWidgetItem::InsertComboBox(const QString& valueName, const QStringList& itemTexts, const QString& currentText, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	QComboBox* comboBox = new QComboBox(treeWidget);
	comboBox->addItems(itemTexts);

	QTreeWidgetItem* item = new QTreeWidgetItem(parentItem);
	item->setText(0, valueName);
	treeWidget->setItemWidget(item, 1, comboBox);
	comboBox->setCurrentText(currentText);

	connect(comboBox, &QComboBox::currentTextChanged, [this, parentItem]{emit(SignalValueChanged(parentItem)); });
}

void VariateValueTreeWidgetItem::InsertInt(const QString& valueName, int value, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	InsertLineEdit(valueName, QString::number(value), RegExp::STR_REG_INT, treeWidget, parentItem);
}

void VariateValueTreeWidgetItem::InsertDouble(const QString& valueName, double value, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	InsertLineEdit(valueName, QString::number(value), RegExp::STR_REG_FLOAT, treeWidget, parentItem);
}

int VariateValueTreeWidgetItem::GetInt(QTreeWidget* treeWidget, QTreeWidgetItem* valueItem)
{
	return dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->text().toInt();
}

double VariateValueTreeWidgetItem::GetDouble(QTreeWidget* treeWidget, QTreeWidgetItem* valueItem)
{
	return dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->text().toDouble();
}

inline
void VariateValueTreeWidgetItem::InsertLineEdit(const QString& valueName, const QString& value, const QString& regExp, 
	QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	QTreeWidgetItem* valueItem = new QTreeWidgetItem(parentItem);
	valueItem->setText(0, valueName);
	auto lineEdit = new LineEditWithRegExpAndKeyboard(value, regExp);
	treeWidget->setItemWidget(valueItem, 1, lineEdit);
	connect(lineEdit, &QLineEdit::textChanged, [this, parentItem]{
		emit(SignalValueChanged(parentItem));
	});
}
