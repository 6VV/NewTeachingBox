#include "stdafx.h"
#include "TRefSys.h"
#include <assert.h>
#include "StringValue.h"
#include "DoubleValue.h"


TVariateRegister<TRefSys> TRefSys::m_register(TypeName());

inline
QString TRefSys::TypeName()
{
	return "TRefSys";
}


TRefSys::TRefSys(const TSymbol& symbol, ValueType value )
	:TComplex(TSymbol{symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX,TypeName()})
	, m_value(value)
{
}

TRefSys::~TRefSys()
{

}

TVariate* TRefSys::Clone() const
{
	return new TRefSys(*this);
}

TRefSys::ValueType TRefSys::GetValue() const
{
	return m_value;
}

void TRefSys::SetValue(ValueType value)
{
	m_value = value;
}


QStringList TRefSys::GetValueNames() const
{
	return{ "a", "b", "c", "x", "y", "z" };
}

std::vector<std::shared_ptr<VariateValue>> TRefSys::GetValues() const 
{
	std::vector<std::shared_ptr<VariateValue>> result;
	for (auto value:m_value)
	{
		result.push_back(std::make_shared<DoubleValue>(value));
	}

	return std::move(result);
}

void TRefSys::SetValues(const std::vector<std::shared_ptr<VariateValue>>& values)
{
	//m_value.baseSys =*std::dynamic_pointer_cast<StringValue>(values[0]);

	for (size_t i = 0; i < m_value.size(); ++i)
	{
		m_value[i] = *std::dynamic_pointer_cast<DoubleValue>(values[i]);
	}
}

void TRefSys::ReadValueFromStream(QDataStream& dataStream)
{
	for (auto& value : m_value)
	{
		dataStream >> value;
	}

}
