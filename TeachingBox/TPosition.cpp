#include "stdafx.h"
#include "TPosition.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"
#include "DoubleValue.h"


inline
QString TPosition::TypeName()
{
	return "Position";
}


//TPosition::TPosition(const TPosition& variate)
//	: TVariate(variate)
//{
//	m_value = variate.m_value;
//
//}

TPosition::TPosition(const TSymbol& symbol, ValueType value)
	:TComplex(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX ,TypeName()})
	//, m_value(value)
{
	MakeCommonValue(value);
	m_valueNames = { "Axis1","Axis2","Axis3","Axis4","Axis5","Aixs6" };
}

const tAxesAllPositions TPosition::GetValue() const
{
	return GetSpecialValue();
}

void TPosition::SetValue(const tAxesAllPositions& value)
{
	MakeCommonValue(value);
}

void TPosition::MakeCommonValue(const ValueType& value)
{
	m_commonValues.clear();
	for (auto v : value.m_AxisPosition)
	{
		m_commonValues.push_back(std::make_shared<DoubleValue>(v));
	}
}

TPosition::ValueType TPosition::GetSpecialValue() const
{
	ValueType result{};
	for (size_t i = 0; i < m_commonValues.size(); ++i)
	{
		result.m_AxisPosition[i] = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[i]);
	}

	return result;
}

//
//void TPosition::WriteValueToStream(QDataStream& dataStream)const
//{
//	for (int i = 0; i < AXIS_SIZE;++i)
//	{
//		dataStream << m_value.m_AxisPosition[i];
//	}
//}
//
//void TPosition::ReadValueFromStream(QDataStream& dataStream)
//{
//	double value;
//
//	for (int i = 0; i < AXIS_SIZE; ++i)
//	{
//		dataStream >> value;
//		m_value.m_AxisPosition[i] = value;
//	}
//}


TVariateRegister<TPosition> TPosition::m_register{ "Position" };

TVariate* TPosition::Clone() const
{
	return new TPosition(*this);
}
