#include "stdafx.h"
#include "TBool.h"
#include "TreeWidgetItemWithVariate.h"


inline
QString TBool::TypeName()
{
	return "Bool";
}



TBool::TBool(const TSymbol& symbol, ValueType value)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::BOOL,TypeName() })
	, m_value(value)
{
}

const TBool::ValueType TBool::GetValue() const
{
	return m_value;
}

void TBool::SetValue(const ValueType value)
{
	m_value = value;
}

void TBool::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TBool::ReadValueFromStream(QDataStream& dataStream) 
{
	dataStream >> m_value;
}


TVariateRegister<TBool> TBool::m_register{ "Bool" };

TVariate* TBool::Clone() const
{
	return new TBool(m_symbol,m_value);
}

