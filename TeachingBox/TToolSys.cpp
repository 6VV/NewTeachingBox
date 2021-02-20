#include "stdafx.h"
#include "TToolSys.h"
#include <assert.h>
#include "DoubleValue.h"

TVariateRegister<TToolSys> TToolSys::m_register(TypeName());

QString TToolSys::TypeName()
{
	return "ToolSys";
}

//TToolSys::TToolSys(const TSymbol& symbol, TComplex::ValueType value)
//	:TComplex(symbol, value)
//{
//
//}

TToolSys::TToolSys(const TSymbol& symbol, ValueType value /*= ValueType{}*/)
	:TComplex(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX, TypeName() })
{
	MakeCommonValue(value);
	m_valueNames = QStringList{ "a", "b", "c", "x", "y", "z" };
}

inline
void TToolSys::MakeCommonValue(const ValueType& value)
{
	m_commonValues.clear();
	for (auto v : value)
	{
		m_commonValues.push_back(std::make_shared<DoubleValue>(v));
	}
}

inline
TToolSys::ValueType TToolSys::GetSpecialValue() const
{
	ValueType result{};
	for (size_t i = 0; i < m_commonValues.size();++i)
	{
		result[i] = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[i]);
	}

	return result;
}

TToolSys::~TToolSys()
{

}

TVariate* TToolSys::Clone() const
{
	return new TToolSys(*this);
}

TToolSys::ValueType TToolSys::GetValue() const
{
	return GetSpecialValue();
}

void TToolSys::SetValue(ValueType value)
{
	MakeCommonValue(value);
}


