#include "stdafx.h"
#include "ComplexValueTreeWidgetItem.h"
#include "TComplex.h"
#include <assert.h>
#include "VariateValue.h"
#include "DoubleValue.h"
#include "TVariateFactory.h"
#include "IntegerValue.h"
#include "StringValue.h"
#include "RegExp.h"



std::shared_ptr<TVariate> ComplexValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem, int index /*= 0*/)
{
	auto newVariate=TVariateFactory::CreateVariate(symbol);
	//assert(typeid(*newVariate) == typeid(TComplex));
	auto result = std::dynamic_pointer_cast<TComplex>(newVariate);
	auto values=result->GetValues();

	for (size_t i = index; i < values.size() + index; ++i)
	{
		GetValue(values[i-index], treeWidget, variateItem->child(i));
	}

	result->SetValues(values);

	return result;
}

void ComplexValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TComplex));
	auto values = std::dynamic_pointer_cast<TComplex>(newVariate)->GetValues();

	for (size_t i = 0; i < values.size(); ++i)
	{
		UpdateValue(values[i], treeWidget, variateItem->child(i));
	}
}

void ComplexValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	//assert(typeid(*variate) == typeid(TComplex));
	auto names = std::dynamic_pointer_cast<TComplex>(variate)->GetValueNames();
	auto values = std::dynamic_pointer_cast<TComplex>(variate)->GetValues();

	assert(static_cast<size_t>(names.size()) == values.size());

	for (int i = 0; i < names.size();++i)
	{
		InsertValue(names.at(i), values.at(i), treeWidget, variateItem);
	}
}


void ComplexValueTreeWidgetItem::InsertValue(const QString& valueName, const std::shared_ptr<VariateValue> value, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	if (typeid(*value) == typeid(IntegerValue))
	{
		InsertInt(valueName, *std::dynamic_pointer_cast<IntegerValue>(value), treeWidget, variateItem);
	}
	else if (typeid(*value) == typeid(DoubleValue))
	{
		InsertDouble(valueName, *std::dynamic_pointer_cast<DoubleValue>(value), treeWidget, variateItem);
	}
	else if (typeid(*value) == typeid(StringValue))
	{
		InsertLineEdit(valueName, *std::dynamic_pointer_cast<StringValue>(value), RegExp::STR_REG_STRING_NAME,treeWidget, variateItem,false);
	}
}

void ComplexValueTreeWidgetItem::UpdateValue(const std::shared_ptr<VariateValue> value, QTreeWidget* treeWidget, QTreeWidgetItem* valueItem)
{
	if (typeid(*value) == typeid(IntegerValue))
	{
		dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->setText(
			QString::number(*std::dynamic_pointer_cast<IntegerValue>(value)));
	}
	else if (typeid(*value) == typeid(DoubleValue))
	{
		dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->setText(
			QString::number(*std::dynamic_pointer_cast<DoubleValue>(value)));
	}
	else if (typeid(*value) == typeid(StringValue))
	{
		dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->setText(
			*std::dynamic_pointer_cast<StringValue>(value));
	}
}

void ComplexValueTreeWidgetItem::GetValue(const std::shared_ptr<VariateValue> desValue, QTreeWidget* treeWidget, QTreeWidgetItem* valueItem)
{
	if (typeid(*desValue) == typeid(IntegerValue))
	{
		*std::dynamic_pointer_cast<IntegerValue>(desValue)=IntegerValue(dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->text().toInt());
	}
	else if (typeid(*desValue) == typeid(DoubleValue))
	{
		*std::dynamic_pointer_cast<DoubleValue>(desValue) = DoubleValue(dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->text().toInt());
	}
	else if (typeid(*desValue) == typeid(StringValue))
	{
		*std::dynamic_pointer_cast<StringValue>(desValue) = StringValue(dynamic_cast<QLineEdit*>(treeWidget->itemWidget(valueItem, 1))->text());
	}
}

VariateValueTreeWidgetBuilder<ComplexValueTreeWidgetItem> ComplexValueTreeWidgetItem::builder(TComplex::TypeName());
