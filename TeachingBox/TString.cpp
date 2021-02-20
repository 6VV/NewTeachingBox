#include "stdafx.h"
#include "TString.h"
#include "TreeWidgetItemWithVariate.h"


QString TString::TypeName()
{
	return "String";
}

TString::TString(const TString& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

}

TString::TString(const TSymbol& symbol, ValueType value /*= 0*/)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_STRING,TypeName() })
	, m_value(value)
{
}

const TString::ValueType TString::GetValue() const
{
	return m_value;
}

void TString::SetValue(const ValueType& value)
{
	m_value = value;
}



void TString::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TString::ReadValueFromStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}


TVariateRegister<TString> TString::m_register{ "String" };

TVariate* TString::Clone() const
{
	return new TString(*this);
}
