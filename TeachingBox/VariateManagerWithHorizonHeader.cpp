#include "stdafx.h"
#include "VariateManagerWithHorizonHeader.h"
#include "TreeWidgetItemWithSymbol.h"
#include "TVariate.h"
#include <assert.h>
#include "VariateValueTreeWidgetItem.h"
#include "VariateWidgetMap.h"


VariateManagerWithHorizonHeader* VariateManagerWithHorizonHeader::GetInstance()
{
	static VariateManagerWithHorizonHeader variateManger;
	return &variateManger;
}

VariateManagerWithHorizonHeader::VariateManagerWithHorizonHeader()
{
	for (auto variateWidget:VariateWidgetMap::VaraiteWidgetMap())
	{
		connect(variateWidget.second.get(), &VariateValueTreeWidgetItem::SignalValueChanged, this, &VariateManagerWithHorizonHeader::SetSave);
	}
}

void VariateManagerWithHorizonHeader::InsertVariate(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* parentItem)
{
	TreeWidgetItemWithSymbol* variateItem = new TreeWidgetItemWithSymbol(variate->GetSymbol(), parentItem);
	variateItem->setText(0, variate->GetTypeName());
	variateItem->setText(1, variate->GetName());

	VariateWidgetMap::GetVariateWidget(variate->GetTypeName())->InsertVariate(variate, treeWidget, variateItem);
}

std::shared_ptr<TVariate> VariateManagerWithHorizonHeader::GetVariate(QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variateItem) == typeid(TreeWidgetItemWithSymbol));

	auto symbol = dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem)->GetSymbol();

	return VariateWidgetMap::GetVariateWidget(symbol.GetTypeName())->GetVariate(symbol, treeWidget, variateItem);
}

void VariateManagerWithHorizonHeader::UpdateWidget(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variateItem) == typeid(TreeWidgetItemWithSymbol));

	auto item = dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem);
	assert(newVariate->GetTypeName() == item->GetSymbol().GetTypeName());

	item->SetSymbol(newVariate->GetSymbol());
	VariateWidgetMap::GetVariateWidget(newVariate->GetTypeName())->UpdateWidgetValue(newVariate, treeWidget, variateItem);
}

void VariateManagerWithHorizonHeader::SetSave(QTreeWidgetItem* variateItem)
{
	if (variateItem == nullptr || typeid(*variateItem) != typeid(TreeWidgetItemWithSymbol))
	{
		return;
	}
	dynamic_cast<TreeWidgetItemWithSymbol*>(variateItem)->SetSave(true);
}

