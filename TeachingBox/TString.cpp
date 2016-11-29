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

TString::TString(QDataStream& dataStream) : TVariate(dataStream)
{
	dataStream >> m_value;

	Init();
}

TString::TString(const TString& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

TString::TString(const TSymbol& symbol, ValueType value /*= 0*/)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_STRING,TypeName() })
	, m_value(value)
{
	Init();
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

void TString::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TString&>(variate).m_value;
}


void TString::Init()
{
	m_variateWidget = new TStringWidget(this);
}


TVariate* TString::Clone() const
{
	return new TString(*this);
}
