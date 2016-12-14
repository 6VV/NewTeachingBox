#include "stdafx.h"
#include "TBool.h"
#include "TreeWidgetItemWithVariate.h"
#include "TBoolWidget.h"


inline
QString TBool::TypeName()
{
	return "Bool";
}

//TBool::TBool(const QString& scope, const QString& name, const bool value)
//	:TVariate(scope, name, TSymbol::TYPE_BOOL), m_value(value)
//{
//	Init();
//}

TBool::TBool(QDataStream& dataStream) : TVariate(dataStream)
{
	dataStream >> m_value;

}

TBool::TBool(const TBool& variate)
	: TVariate(variate)
	, m_value(variate.m_value)
{
}


TBool::TBool(const TSymbol& symbol, ValueType value)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_BOOL,TypeName() })
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

void TBool::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TBool&>(variate).m_value;
}



TVariateRegister<TBool> TBool::m_register{ "Bool" };

TVariate* TBool::Clone() const
{
	return new TBool(*this);
}

