#include "stdafx.h"
#include "TComplex.h"
#include "VariateValue.h"
#include <assert.h>


const QString TComplex::TypeName()
{
	return "Complex";
}


TComplex::TComplex(const TSymbol& symbol, ValueType value)
	:TVariate(symbol)
{
	SetValues(value);
}

TComplex::TComplex(const TComplex& variate)
	: TVariate(variate.m_symbol)
{
	SetValues(variate.m_commonValues);
	m_valueNames = variate.m_valueNames;
}

TComplex::ValueType TComplex::GetValues() const
{
	ValueType result{};
	for (auto value:m_commonValues)
	{
		result.push_back(value->Clone());
	}

	return std::move(result);
}

void TComplex::SetValues(const ValueType& values)
{
	m_commonValues.clear();
	for (auto value : values)
	{
		m_commonValues.push_back(value->Clone());
	}
}

void TComplex::WriteValueToStream(QDataStream& dataStream) const
{
	for (auto value:m_commonValues)
	{
		value->WriteToDataStream(dataStream);
	}
}

void TComplex::ReadValueFromStream(QDataStream& dataStream)
{
	for (auto& value : m_commonValues)
	{
		value->ReadFromDataStream(dataStream);
	}
}



TVariate* TComplex::Clone() const
{
	return new TComplex(*this);
}

QStringList TComplex::GetValueNames() const
{
	return m_valueNames;
}

