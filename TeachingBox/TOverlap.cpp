#include "stdafx.h"
#include "TOverlap.h"
#include "DoubleValue.h"
#include "EnumValue.h"


inline
QString TOverlap::TypeName()
{
	return "Overlap";
}

TOverlap::TOverlap(const TSymbol& symbol, ValueType value)
	:TComplex(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX,TypeName() })
{
	MakeCommonValue(value);
	m_valueNames = { "Mode", "Parameter"};
}

const tOverlapConstraint& TOverlap::GetValue() const
{
	return GetSpecialValue();
}

void TOverlap::SetValue(const tOverlapConstraint& value)
{
	MakeCommonValue(value);
}

void TOverlap::MakeCommonValue(const ValueType& value)
{
	m_commonValues.clear();
	m_commonValues.push_back(std::make_shared<EnumValue>(EnumValue::EnumMapType{ { 0, "Absolute" }, { 1, "Relative" } }, value.m_TransitionMode));
	m_commonValues.push_back(std::make_shared<DoubleValue>(value.m_TransitionParameter));
}

TOverlap::ValueType TOverlap::GetSpecialValue() const
{
	ValueType result{};
	result.m_TransitionMode = *std::dynamic_pointer_cast<EnumValue>(m_commonValues[0]);
	result.m_TransitionParameter = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[1]);

	return result;
}

TVariateRegister<TOverlap> TOverlap::m_register{ TypeName() };

TVariate* TOverlap::Clone() const
{
	return new TOverlap(*this);
}
