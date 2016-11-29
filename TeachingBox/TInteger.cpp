#include "stdafx.h"
#include "TInteger.h"
#include "TVariateType.h"
#include "RegExp.h"
#include "TSymbol.h"
#include "TreeWidgetItemWithVariate.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "TIntegerWidget.h"


inline
QString TInteger::TypeName()
{
	return "Integer";
}

//TInteger::TInteger(const QString& scope, const QString& name, const int value)
//	:TVariate(scope,name,TSymbol::TYPE_INTERGER)
//{
//	m_value = value;
//
//	Init();
//}

TInteger::TInteger(QDataStream& dataStream) :TVariate(dataStream)
{
	dataStream >> m_value;

	Init();
}

TInteger::TInteger(const TInteger& variate)
	: TVariate(variate)
	, m_value(variate.m_value)
{
	Init();
}

TInteger::TInteger(const TSymbol& symbol, ValueType value /*= 0*/)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_INTERGER,TypeName() })
	, m_value(value)
{
	Init();
}

int TInteger::GetValue()
{
	return m_value;
}

void TInteger::SetValue(const int value)
{
	m_value = value;
}

void TInteger::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TInteger::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TInteger&>(variate).m_value;
}


void TInteger::Init()
{
	m_variateWidget = new TIntegerWidget(this);
}


TVariate* TInteger::Clone() const
{
	return new TInteger(*this);
}


