#include "stdafx.h"
#include "TDouble.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditWithRegExpAndKeyboard.h"


inline
QString TDouble::TypeName()
{
	return "Double";
}

//TDouble::TDouble(const QString& scope, const QString& name, const double value)
//	:TVariate(scope, name, TSymbol::TYPE_DOUBLE)
//{
//	m_value = value;
//
//	Init();
//}

//TDouble::TDouble(QDataStream& dataStream) : TVariate(dataStream)
//{
//	dataStream >> m_value;
//
//}

TDouble::TDouble(const TDouble& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

}

TDouble::TDouble(const TSymbol& symbol, ValueType value /*= false*/)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_DOUBLE,TypeName() })
	, m_value(value)
{
}

double TDouble::GetValue()
{
	return m_value;
}

void TDouble::SetValue(const double value)
{
	m_value = value;
}

void TDouble::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TDouble::ReadValueFromStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}


TVariateRegister<TDouble> TDouble::m_register{ "Double" };

TVariate* TDouble::Clone() const
{
	return new TDouble(*this);
}

