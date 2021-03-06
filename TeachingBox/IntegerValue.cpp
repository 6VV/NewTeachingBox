﻿#include "stdafx.h"
#include "IntegerValue.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <assert.h>


QString IntegerValue::TypeText()
{
	return "Integer";
}

IntegerValue::IntegerValue(int value)
	:m_value(value)
{

}

IntegerValue::operator int() const
{
	return m_value;
}

void IntegerValue::WriteToDataStream(QDataStream& dataStream) const
{
	dataStream << m_value;
}

void IntegerValue::ReadFromDataStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}

std::shared_ptr<VariateValue> IntegerValue::Clone() const
{
	return std::make_shared<IntegerValue>(m_value);
}

QStringList IntegerValue::ToStrings()
{
	return{ QString::number(m_value) };
}

VariateValueRegister<IntegerValue> IntegerValue::m_register(TypeText());

