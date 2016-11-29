#include "stdafx.h"
#include "BoolValueTreeWidgetItem.h"
#include "TBool.h"
#include <assert.h>



const QString BoolValueTreeWidgetItem::TRUE_VALUE("True");

const QString BoolValueTreeWidgetItem::FALSE_VALUE("False");

VariateValueTreeWidgetBuilder<BoolValueTreeWidgetItem> BoolValueTreeWidgetItem::builder(TBool::TypeName());

std::shared_ptr<TVariate> BoolValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	auto comboBox = dynamic_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0), 1));

	bool value=false;
	if (comboBox->currentText()==TRUE_VALUE)
	{
		value = true;
	}

	return std::shared_ptr<TVariate>(new TBool(symbol, value));
}

void BoolValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TBool));

	auto valueItem = new QTreeWidgetItem(variateItem);
	valueItem->setText(0, "Value");

	QComboBox* comboBox = new QComboBox(treeWidget);
	comboBox->addItems({ TRUE_VALUE, FALSE_VALUE });

	auto value = dynamic_cast<TBool*>(variate.get())->GetValue();
	QString valueName = FALSE_VALUE;
	if (value)
	{
		valueName = TRUE_VALUE;
	}
	comboBox->setCurrentText(valueName);

	treeWidget->setItemWidget(valueItem, 1, comboBox);
}

void BoolValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TBool));

	auto value = dynamic_cast<TBool*>(newVariate.get())->GetValue();

	auto valueName = FALSE_VALUE;
	if (value)
	{
		valueName = TRUE_VALUE;
	}

	dynamic_cast<QComboBox*>(treeWidget->itemWidget(variateItem->child(0), 1))->setCurrentText(valueName);
}
