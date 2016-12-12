#include "stdafx.h"
#include "TreeWidgetItemWithSymbol.h"
#include "VariateManagerWithHorizonHeader.h"
#include "TVariateManager.h"



TreeWidgetItemWithSymbol::TreeWidgetItemWithSymbol(const TSymbol& symbol, QTreeWidgetItem* parentItem)
	:QTreeWidgetItem(parentItem)
	, m_symbol(symbol)
{

}

TreeWidgetItemWithSymbol::~TreeWidgetItemWithSymbol()
{
}

TSymbol TreeWidgetItemWithSymbol::GetSymbol() const
{
	return m_symbol;
}

bool TreeWidgetItemWithSymbol::IsSave() const
{
	return m_isSave;
}

void TreeWidgetItemWithSymbol::SetSymbol(const TSymbol& symbol)
{
	m_symbol = symbol;
}

void TreeWidgetItemWithSymbol::SetSave(bool isSave)
{
	m_isSave = isSave;
}
