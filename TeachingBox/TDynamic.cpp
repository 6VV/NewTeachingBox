#include "stdafx.h"
#include "TDynamic.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"


inline
QString TDynamic::TypeName()
{
	return "Dynamic";
}


//TDynamic::TDynamic(QDataStream& dataStream) : TVariate(dataStream)
//{
//	ReadValueFromStream(dataStream);
//
//}

TDynamic::TDynamic(const TDynamic& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

}

TDynamic::TDynamic(const TSymbol& symbol, ValueType value )
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX,TypeName() })
	, m_value(value)
{
}

const tDynamicConstraint& TDynamic::GetValue() const
{
	return m_value;
}

void TDynamic::SetValue(const tDynamicConstraint& value)
{
	m_value = value;
}

void TDynamic::ReadValueFromStream(QDataStream& dataStream)
{
	dataStream >> m_value.m_Velocity;
	dataStream >> m_value.m_Acceleration;
	dataStream >> m_value.m_Deceleration;

	dataStream >> m_value.m_PostureVelocity;
	dataStream >> m_value.m_PostureAcceleration;
	dataStream >> m_value.m_PostureDeceleration;
}


TVariateRegister<TDynamic> TDynamic::m_register{ TypeName() };

TVariate* TDynamic::Clone() const
{
	return new TDynamic(*this);
}

void TDynamic::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value.m_Velocity;
	dataStream << m_value.m_Acceleration;
	dataStream << m_value.m_Deceleration;

	dataStream << m_value.m_PostureVelocity;
	dataStream << m_value.m_PostureAcceleration;
	dataStream << m_value.m_PostureDeceleration;
}

