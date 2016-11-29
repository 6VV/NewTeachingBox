#include "stdafx.h"
#include "VariateValueTreeWidgetItem.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "RegExp.h"
#include "TSymbol.h"



VariateValueTreeWidgetItem::~VariateValueTreeWidgetItem()
{

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
	treeWidget->setItemWidget(valueItem, 1, new LineEditWithRegExpAndKeyboard(value, regExp));
}
