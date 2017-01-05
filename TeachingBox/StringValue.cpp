#include "stdafx.h"
#include "StringValue.h"



StringValue::StringValue(ValueType value)
	:m_value(value)
{
}

StringValue::operator ValueType() const
{
	return m_value;
}

void StringValue::WriteToDataStream(QDataStream& dataStream) const
{
	dataStream << m_value;
}

void StringValue::ReadFromDataStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}

std::shared_ptr<VariateValue> StringValue::Clone() const
{
	return std::make_shared<StringValue>(m_value);
}
