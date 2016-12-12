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
	/*断开直接建立的所有连接*/
	disconnect(this, 0, 0, 0);

	assert(variateItem!=nullptr && typeid(*variateItem) == typeid(TreeWidgetItemWithSymbol));
	InsertVariateValue(variate, treeWidget, variateItem);

	connect(this, &VariateValueTreeWidgetItem::SignalValueChanged, [variateItem]{
		dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem)->SetSave(true);
	});
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
	connect(lineEdit, &QLineEdit::textChanged, [this]{
		emit(SignalValueChanged());
	});
}
