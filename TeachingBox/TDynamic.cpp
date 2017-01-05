#include "stdafx.h"
#include "TDynamic.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"
#include "DoubleValue.h"


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

//TDynamic::TDynamic(const TDynamic& variate)
//	: TVariate(variate)
//{
//	m_value = variate.m_value;
//
//}

TDynamic::TDynamic(const TSymbol& symbol, ValueType value )
	:TComplex(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX,TypeName() })
{
	MakeCommonValue(value);
}

const tDynamicConstraint& TDynamic::GetValue() const
{
	return GetSpecialValue();
}

void TDynamic::SetValue(const tDynamicConstraint& value)
{
	MakeCommonValue(value);
}

void TDynamic::MakeCommonValue(const ValueType& value)
{
	m_commonValues.clear();
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_Velocity));
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_Acceleration));
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_Deceleration));
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_PostureVelocity));
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_PostureAcceleration));
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_PostureDeceleration));
}

TDynamic::ValueType TDynamic::GetSpecialValue() const
{
	ValueType result{};
	result.m_Velocity = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[0]);
	result.m_Acceleration = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[1]);
	result.m_Deceleration = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[2]);
	result.m_PostureVelocity = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[3]);
	result.m_PostureAcceleration = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[4]);
	result.m_PostureDeceleration = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[5]);

	return result;
}

//
//void TDynamic::ReadValueFromStream(QDataStream& dataStream)
//{
//	dataStream >> m_value.m_Velocity;
//	dataStream >> m_value.m_Acceleration;
//	dataStream >> m_value.m_Deceleration;
//
//	dataStream >> m_value.m_PostureVelocity;
//	dataStream >> m_value.m_PostureAcceleration;
//	dataStream >> m_value.m_PostureDeceleration;
//}


TVariateRegister<TDynamic> TDynamic::m_register{ TypeName() };

TVariate* TDynamic::Clone() const
{
	return new TDynamic(*this);
}
//
//void TDynamic::WriteValueToStream(QDataStream& dataStream)const
//{
//	dataStream << m_value.m_Velocity;
//	dataStream << m_value.m_Acceleration;
//	dataStream << m_value.m_Deceleration;
//
//	dataStream << m_value.m_PostureVelocity;
//	dataStream << m_value.m_PostureAcceleration;
//	dataStream << m_value.m_PostureDeceleration;
//}

