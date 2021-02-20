#include "stdafx.h"
#include "TRefSys.h"
#include <assert.h>
#include "StringValue.h"
#include "DoubleValue.h"


void TRefSys::MakeCommonValue(const ValueType& value)
{
	m_commonValues.clear();
	for (auto v : value)
	{
		m_commonValues.push_back(std::make_shared<DoubleValue>(v));
	}
}

TRefSys::ValueType TRefSys::GetSpecialValue() const
{
	ValueType result{};
	for (size_t i = 0; i < m_commonValues.size(); ++i)
	{
		result[i] = *std::dynamic_pointer_cast<DoubleValue>(m_commonValues[i]);
	}

	return result;
}

TVariateRegister<TRefSys> TRefSys::m_register(TypeName());

QString TRefSys::TypeName()
{
	return "RefSys";
}


TRefSys::TRefSys(const TSymbol& symbol, ValueType value )
	:TComplex(TSymbol{symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX,TypeName()})
{
	MakeCommonValue(value);
	m_valueNames = QStringList{ "a", "b", "c", "x", "y", "z" };
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
	return GetSpecialValue();
}

void TRefSys::SetValue(ValueType value)
{
	MakeCommonValue(value);
}


//QStringList TRefSys::GetValueNames() const
//{
//	return{ "a", "b", "c", "x", "y", "z" };
//}

