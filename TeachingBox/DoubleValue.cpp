#include "stdafx.h"
#include "DoubleValue.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <assert.h>



QString DoubleValue::TypeText()
{
	return "Double";
}

DoubleValue::DoubleValue(double value)
	:m_value(value)
{
}

DoubleValue::operator double() const
{
	return m_value;
}

void DoubleValue::WriteToDataStream(QDataStream& dataStream) const
{
	dataStream << m_value;
}

void DoubleValue::ReadFromDataStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}

std::shared_ptr<VariateValue> DoubleValue::Clone() const
{
	return std::make_shared<DoubleValue>(m_value);
}

QStringList DoubleValue::ToStrings()
{
	return{ QString::number(m_value) };
}

VariateValueRegister<DoubleValue> DoubleValue::m_register(TypeText());

