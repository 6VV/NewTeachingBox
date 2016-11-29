#include "stdafx.h"
#include "VariateTreeWidgetManager.h"
#include "TreeWidgetItemWithSymbol.h"
#include "TVariate.h"
#include <assert.h>
#include "VariateValueTreeWidgetItem.h"


void VariateTreeWidgetManager::InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	TreeWidgetItemWithSymbol* variateItem = new TreeWidgetItemWithSymbol(variate->GetSymbol(), parentItem);
	variateItem->setText(0, variate->GetTypeName());
	variateItem->setText(1, variate->GetName());

	GetVariateWidget(variate->GetTypeName())->InsertVariateValue(variate, treeWidget, variateItem);
}



std::shared_ptr<TVariate> VariateTreeWidgetManager::GetVariate(QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variateItem) == typeid(TreeWidgetItemWithSymbol));

	auto symbol = dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem)->GetSymbol();

	return GetVariateWidget(symbol.GetTypeName())->GetVariate(symbol, treeWidget, variateItem);
}

void VariateTreeWidgetManager::UpdateWidget(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variateItem) == typeid(TreeWidgetItemWithSymbol));

	auto item = dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem);
	assert(newVariate->GetTypeName() == item->GetSymbol().GetTypeName());

	item->SetSymbol(newVariate->GetSymbol());
	GetVariateWidget(newVariate->GetTypeName())->UpdateWidgetValue(newVariate, treeWidget, variateItem);
}

VariateTreeWidgetManager::VariateWidgetMapType& VariateTreeWidgetManager::VaraiteWidgetMap()
{
	static VariateWidgetMapType map{};
	return map;
}

inline
std::shared_ptr<VariateValueTreeWidgetItem> VariateTreeWidgetManager::GetVariateWidget(const QString& type)
{
	auto iter = VaraiteWidgetMap().find(type);
	assert(iter != VaraiteWidgetMap().end());
	return iter->second;
}
