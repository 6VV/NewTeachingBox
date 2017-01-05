#include "stdafx.h"
#include "ComplexValue.h"


	void ComplexValue::WriteToDataStream(QDataStream& dataStream) const
	{
		for (auto value:m_value)
		{
			value->WriteToDataStream(dataStream);
		}
	}

	void ComplexValue::ReadFromDataStream(QDataStream& dataStream)
	{
		for (auto value : m_value)
		{
			value->ReadFromDataStream(dataStream);
		}
	}

	std::shared_ptr<VariateValue> ComplexValue::Clone() const
	{
		ValueType result{};
		for (auto variate:m_value)
		{
			result.push_back(variate->Clone());
		}

		return std::make_shared<ComplexValue>(result);
	}


	ComplexValue::ComplexValue(ValueType value)
	{
		m_value.clear();
		for (auto variate : m_value)
		{
			m_value.push_back(variate->Clone());
		}
	}

	ComplexValue::operator ValueType() const
	{
		return m_value;
	}

