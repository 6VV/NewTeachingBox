#include "stdafx.h"
#include "TVariate.h"
#include "TVariateManager.h"
#include "TreeWidgetItemWithVariate.h"
#include "TVariateWidget.h"
#include <assert.h>


TVariate::TVariate(QDataStream& dataStream) 
	: m_symbol(dataStream)
{
}

//TVariate::TVariate(const QString& scope, const QString& name, TSymbol::SymbolType type)
//	: m_symbol(scope, name, type, TSymbol::CATEGORY_VARIABLE)
//{
//
//}

TVariate::TVariate(const TVariate& variate)
	: m_symbol(variate.m_symbol)
{
}

TVariate::TVariate(const TSymbol& symbol)
	: m_symbol(symbol)
{

}

TVariate::~TVariate()
{
	delete m_variateWidget;
}

TSymbol TVariate::GetSymbol() const
{
	return m_symbol;
}

QString TVariate::GetScope() const
{
	return m_symbol.GetScope();
}

QString TVariate::GetName() const 
{
	return m_symbol.GetName();
}

TSymbol::SymbolType TVariate::GetType() const
{
	return m_symbol.GetType();
}

QString TVariate::GetTypeName() const
{
	return m_symbol.GetTypeName();
}

//void TVariate::SetName(const QString& name)
//{
//	m_symbol.SetName(name);
//}

void TVariate::Save()
{
	m_variateWidget->UpdateVariate();
	UpdateRamAndDatabaseFrom(*this);
}

void TVariate::WriteContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget)
{
	m_variateWidget->WriteContentIntoItem(parentItem, treeWidget);
}

void TVariate::WriteToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget,
	const TSymbol::SymbolType type)
{
	if (m_symbol.GetType() == type)
	{
		this->WriteToTreeWidgetItem(parentItem, treeWidget);
	}
}

void TVariate::WriteToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	m_variateWidget->WriteToTreeWidgetItem(parentItem, treeWidget);
}

void TVariate::WriteDataToStream(QDataStream& dataStream) const
{
	m_symbol.WriteToStream(dataStream);

	WriteValueToStream(dataStream);
}


void TVariate::UpdateFromVariate(const TVariate& variate)
{
	assert(typeid(variate) == typeid(*this));
	m_symbol = variate.m_symbol;
	UpdateFromValue(variate);
}

void TVariate::UpdateRamAndDatabaseFrom(const TVariate& variate) const
{
	TVariateManager::GetInstance()->UpdateVariate(m_symbol.GetScope(), m_symbol.GetName(), variate);
}

