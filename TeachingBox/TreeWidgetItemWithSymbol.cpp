#include "stdafx.h"
#include "TreeWidgetItemWithSymbol.h"



TreeWidgetItemWithSymbol::TreeWidgetItemWithSymbol(const TSymbol& symbol, QTreeWidgetItem* parentItem)
	:QTreeWidgetItem(parentItem)
	, m_symbol(symbol)
{

}

TSymbol TreeWidgetItemWithSymbol::GetSymbol() const
{
	return m_symbol;
}

void TreeWidgetItemWithSymbol::SetSymbol(const TSymbol& symbol)
{
	m_symbol = symbol;
}
