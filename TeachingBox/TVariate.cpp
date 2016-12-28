#include "stdafx.h"
#include "TVariate.h"
#include "TVariateManager.h"
#include "TreeWidgetItemWithVariate.h"
#include <assert.h>


//TVariate::TVariate(QDataStream& dataStream) 
//	: m_symbol(dataStream)
//{
//}

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

void TVariate::ReadDataFromStream(QDataStream& dataStream)
{
	m_symbol.ReadDataFromStream(dataStream);
	ReadValueFromStream(dataStream);
}

//void TVariate::SetName(const QString& name)
//{
//	m_symbol.SetName(name);
//}


void TVariate::WriteDataToStream(QDataStream& dataStream) const
{
	m_symbol.WriteToStream(dataStream);

	WriteValueToStream(dataStream);
}



void TVariate::UpdateRamAndDatabaseFrom(const TVariate& variate) const
{
	TVariateManager::GetInstance()->UpdateVariate(std::shared_ptr<TVariate>(variate.Clone()));
}

