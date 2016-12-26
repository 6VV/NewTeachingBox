#ifndef _TEACHING_BOX_COMPLEX_VALUE_TREE_WIDGET_ITEM_H_
#define _TEACHING_BOX_COMPLEX_VALUE_TREE_WIDGET_ITEM_H_

#include "VariateValueTreeWidgetItem.h"
#include "VariateValueTreeWidgetBuilder.h"

class VariateValue;

class ComplexValueTreeWidgetItem:public VariateValueTreeWidgetItem
{
public:
	virtual std::shared_ptr<TVariate> GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem, int index = 0) override;

	virtual void UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

	virtual void InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem) override;

private:
	void InsertValue(const QString& valueName, const std::shared_ptr<VariateValue> value, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem);
	void UpdateValue(const std::shared_ptr<VariateValue> value, QTreeWidget* treeWidget, QTreeWidgetItem* valueItem);
	void GetValue(const std::shared_ptr<VariateValue> desValue, QTreeWidget* treeWidget, QTreeWidgetItem* valueItem);

private:
	static VariateValueTreeWidgetBuilder<ComplexValueTreeWidgetItem> builder;
};

#endif