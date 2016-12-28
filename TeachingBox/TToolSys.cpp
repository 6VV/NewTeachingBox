#include "stdafx.h"
#include "TToolSys.h"
#include <assert.h>
#include "DoubleValue.h"

TVariateRegister<TToolSys> TToolSys::m_register(TypeName());

inline
QString TToolSys::TypeName()
{
	return "ToolSys";
}


TToolSys::TToolSys(const TSymbol& symbol, ValueType value /*= ValueType{}*/)
	:TComplex(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX, TypeName() })
	//, m_value(value)
{
	MakeCommonValue(value);

}

void TToolSys::MakeCommonValue(const ValueType& value)
{
	for (auto v : value)
	{
		m_commonValues.push_back(std::make_shared<DoubleValue>(v));
	}
}

inline
TToolSys::ValueType TToolSys::MakeSpecialValue(const std::vector<std::shared_ptr<VariateValue>>& values) const
{
	ValueType result{};
	for (size_t i = 0; i < values.size();++i)
	{
		result[i] = *std::dynamic_pointer_cast<DoubleValue>(values[i]);
	}

	return result;
}

TToolSys::~TToolSys()
{

}

TVariate* TToolSys::Clone() const
{
	return new TToolSys(m_symbol,MakeSpecialValue(m_commonValues));
}

TToolSys::ValueType TToolSys::GetValue() const
{
	return MakeSpecialValue(m_commonValues);
}

void TToolSys::SetValue(ValueType value)
{
	/*m_value = value;*/
	MakeCommonValue(value);
}

void TToolSys::ReadValueFromStream(QDataStream& dataStream)
{
	for (auto& value : m_commonValues)
	{
		value->WriteToDataStream(dataStream);
		//dataStream >> value;
	}
}

void TToolSys::SetValues(const std::vector<std::shared_ptr<VariateValue>>& values)
{
	assert(values.size() == 6);
	//for (int i = 0; i < 6;++i)
	//{
	//	assert(typeid(*(values[i])) == typeid(DoubleValue));
	//	m_value[i] = *(std::dynamic_pointer_cast<DoubleValue>(values[i]));
	//}
	m_commonValues = values;
}

QStringList TToolSys::GetValueNames() const
{
	return{ "a", "b", "c", "x", "y", "z" };
}

std::vector<std::shared_ptr<VariateValue>> TToolSys::GetValues() const
{
	/*std::vector<std::shared_ptr<VariateValue>> result;
	for (auto value:m_value)
	{
	result.push_back(std::make_shared<DoubleValue>(value));
	}

	return std::move(result);*/

	return m_commonValues;
}

