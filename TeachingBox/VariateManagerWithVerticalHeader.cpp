#include "stdafx.h"
#include "VariateManagerWithVerticalHeader.h"
#include "TVariate.h"
#include "VariateWidgetMap.h"
#include "VariateValueTreeWidgetItem.h"
#include "LineEditWithRegExpAndKeyboard.h"


VariateManagerWithVerticalHeader* VariateManagerWithVerticalHeader::GetInstance()
{
	static VariateManagerWithVerticalHeader variateManager;
	return &variateManager;
}

void VariateManagerWithVerticalHeader::InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	if (parentItem==nullptr)
	{
		parentItem = treeWidget->invisibleRootItem();
	}

	/*名字节点*/
	auto nameItem = new QTreeWidgetItem(treeWidget);
	nameItem->setText(0, "Name");
	treeWidget->setItemWidget(nameItem, 1, new LineEditWithRegExpAndKeyboard("",RegExp::STR_REG_STRING_NAME,treeWidget));

	/*作用域节点*/
	auto scopeItem = new QTreeWidgetItem(treeWidget);
	scopeItem->setText(0, "Scope");
	auto scopeLineEdit = new QLineEdit(variate->GetScope(),treeWidget);
	scopeLineEdit->setEnabled(false);
	treeWidget->setItemWidget(scopeItem, 1, scopeLineEdit);

	/*类型节点*/
	auto typeItem = new QTreeWidgetItem(treeWidget);
	typeItem->setText(0, "Type");
	auto typeLineEdit = new QLineEdit(variate->GetTypeName(),treeWidget);
	typeLineEdit->setEnabled(false);
	treeWidget->setItemWidget(typeItem, 1, typeLineEdit);

	VariateWidgetMap::GetVariateWidget(variate->GetTypeName())->InsertVariate(variate, treeWidget, parentItem);
}

std::shared_ptr<TVariate> VariateManagerWithVerticalHeader::GetVariate(QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	auto name = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0), 1))->text();
	auto scope = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(1), 1))->text();
	auto type = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(2), 1))->text();

	return VariateWidgetMap::GetVariateWidget(type)->GetVariate(TSymbol{ scope, name }, treeWidget, variateItem,3);
}

void VariateManagerWithVerticalHeader::UpdateWidget(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	newVariate;
	treeWidget;
	variateItem;
}
