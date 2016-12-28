#include "stdafx.h"
#include "MacroInfo.h"




MacroInfo::MacroInfo(const QString& name, int id, const QStringList& parameterTypes, const QString& category, const QString& type, const QString& text)
	:m_name(name)
	, m_id(id)
	, m_parameterTypes(parameterTypes)
	, m_category(category)
	, m_type(type)
	, m_text(text)
{

}

int MacroInfo::GetId() const
{
	return m_id;
}

QString MacroInfo::GetText() const
{
	return m_text;
}

QString MacroInfo::GetName() const
{
	return m_name;
}

QStringList MacroInfo::GetParameterTypes() const
{
	return m_parameterTypes;
}
