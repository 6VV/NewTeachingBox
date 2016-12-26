#include "stdafx.h"
#include "TRefSys.h"
#include <assert.h>
#include "TRefSysWidget.h"
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
	m_value.baseSys = value.baseSys;
	m_value.offset = value.offset;
}


QStringList TRefSys::GetValueNames() const
{
	return{ "BaseSys", "a", "b", "c", "x", "y", "z" };
}

std::vector<std::shared_ptr<VariateValue>> TRefSys::GetValues() const 
{
	std::vector<std::shared_ptr<VariateValue>> result;
	result.push_back(std::make_shared<StringValue>(m_value.baseSys));
	for (auto value:m_value.offset)
	{
		result.push_back(std::make_shared<DoubleValue>(value));
	}

	return std::move(result);
}

void TRefSys::SetValues(const std::vector<std::shared_ptr<VariateValue>>& values)
{
	m_value.baseSys =*std::dynamic_pointer_cast<StringValue>(values[0]);

	for (size_t i = 0; i < m_value.offset.size(); ++i)
	{
		m_value.offset[i] = *std::dynamic_pointer_cast<DoubleValue>(values[i+1]);
	}
}

//void TRefSys::WriteValueToStream(QDataStream& dataStream) const
//{
//	dataStream << m_value.baseSys;
//
//	for (const auto& value: m_value.offset)
//	{
//		dataStream << value;
//	}
//}

void TRefSys::ReadValueFromStream(QDataStream& dataStream)
{
	dataStream >> m_value.baseSys;

	for (auto& value : m_value.offset)
	{
		dataStream >> value;
	}

}
