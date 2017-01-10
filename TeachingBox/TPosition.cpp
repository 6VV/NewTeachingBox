#include "stdafx.h"
#include "TPosition.h"
#include "DataStruct.h"
#include "DoubleValue.h"


QString TPosition::TypeName()
{
	return "Position";
}

TComplex::ValueType TPosition::ToCommonValue(const tAxesAllPositions& value)
{
	TComplex::ValueType values{};
	for (auto v : value.m_AxisPosition)
	{
		values.push_back(std::make_shared<DoubleValue>(v));
	}

	return values;

}

//TPosition::TPosition(const TSymbol& symbol, ValueType value)
//	:TComplex(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX, TypeName() })
//{
//	MakeCommonValue(value);
//	m_valueNames = { "Axis1", "Axis2", "Axis3", "Axis4", "Axis5", "Aixs6" };
//}

//void TPosition::SetValue(const tAxesAllPositions& value)
//{
//	MakeCommonValue(value);
//}

//void TPosition::MakeCommonValue(const ValueType& value)
//{
//	m_commonValues.clear();
//	for (auto v : value.m_AxisPosition)
//	{
//		m_commonValues.push_back(std::make_shared<DoubleValue>(v));
//	}
//}

//TVariateRegister<TPosition> TPosition::m_register{ "Position" };

//TVariate* TPosition::Clone() const
//{
//	return new TPosition(*this);
//}
