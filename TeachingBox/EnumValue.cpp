#include "stdafx.h"
#include "EnumValue.h"



//EnumValue::EnumValue(int id)
//	:m_value(id)
//{
//}

//EnumValue::EnumValue(const EnumMapType& enumMap)
//	: m_enumMap(enumMap)
//{
//}

//EnumValue::EnumValue(const QString& text)
//{
//	for (auto iter:m_enumMap)
//	{
//		if (iter.second==text)
//		{
//			m_value = iter.first;
//			break;
//		}
//	}
//}

EnumValue::EnumValue(const EnumMapType& enumMap, int id)
	:m_value(id)
	, m_enumMap(enumMap)
{

}

EnumValue::operator int() const
{
	return m_value;
}

std::shared_ptr<VariateValue> EnumValue::Clone() const
{
	return std::make_shared<EnumValue>(m_enumMap,m_value);
}

void EnumValue::WriteToDataStream(QDataStream& dataStream) const
{
	dataStream << m_value;
}

void EnumValue::ReadFromDataStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}

QStringList EnumValue::ToStrings()
{
	return{ m_enumMap[m_value] };
}

QStringList EnumValue::Texts() const
{
	QStringList result{};
	for (auto iter:m_enumMap)
	{
		result.append(iter.second);
	}
	return result;
}
