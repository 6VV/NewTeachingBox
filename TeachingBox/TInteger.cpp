﻿#include "stdafx.h"
#include "TInteger.h"
#include "RegExp.h"
#include "TSymbol.h"
#include "TreeWidgetItemWithVariate.h"
#include "LineEditWithRegExpAndKeyboard.h"


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

//TInteger::TInteger(QDataStream& dataStream) :TVariate(dataStream)
//{
//	dataStream >> m_value;
//
//}

TInteger::TInteger(const TInteger& variate)
	: TVariate(variate)
	, m_value(variate.m_value)
{
}

TInteger::TInteger(const TSymbol& symbol, ValueType value /*= 0*/)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_INTERGER,TypeName() })
	, m_value(value)
{
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

void TInteger::ReadValueFromStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}

TVariateRegister<TInteger> TInteger::m_register{"Integer"};

TVariate* TInteger::Clone() const
{
	return new TInteger(*this);
}


