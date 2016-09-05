#include "stdafx.h"
#include "TreeWidgetItemWithVariate.h"
#include "TSymbol.h"
#include "TVariate.h"

TreeWidgetItemWithVariate::TreeWidgetItemWithVariate(QTreeWidgetItem* parentItem, TVariate* variate)
	:QTreeWidgetItem(parentItem), m_variate(variate)
{
	this->setText(0, variate->GetName());
	this->setText(1, TSymbol::Map_Type[variate->GetType()]);
	//this->setText(2, variate->GetScope());
}

TreeWidgetItemWithVariate::~TreeWidgetItemWithVariate()
{

}
