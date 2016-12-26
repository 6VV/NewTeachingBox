#include "stdafx.h"
#include "TString.h"
#include "TreeWidgetItemWithVariate.h"
#include "TStringWidget.h"


inline
QString TString::TypeName()
{
	return "String";
}

//TString::TString(const QString& scope, const QString& name, const QString& value)
//	:TVariate(scope,name,TSymbol::TYPE_STRING)
//{
//	m_value = value;
//
//	Init();
//}
//
//TString::TString(QDataStream& dataStream) : TVariate(dataStream)
//{
//	dataStream >> m_value;
//
//}

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
