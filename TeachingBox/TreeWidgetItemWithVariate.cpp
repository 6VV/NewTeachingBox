#include "stdafx.h"
#include "TreeWidgetItemWithVariate.h"
#include "TSymbol.h"
#include "TVariate.h"

TreeWidgetItemWithVariate::TreeWidgetItemWithVariate(QTreeWidgetItem* parentItem, TVariate* variate)
	:QTreeWidgetItem(parentItem), m_variate(variate)
{
	this->setText(1, variate->GetName());
	this->setText(0, TSymbol::Map_Type[variate->GetType()]);
	//this->setText(2, variate->GetScope());
}

TreeWidgetItemWithVariate::~TreeWidgetItemWithVariate()
{
	if (m_variate!=nullptr && m_isSave)
	{
		m_variate->Save();
	}
}

void TreeWidgetItemWithVariate::IsSave(bool isSave)
{
	m_isSave = isSave;
}

void TreeWidgetItemWithVariate::Variate(TVariate* variate)
{
	m_variate = variate;
}

