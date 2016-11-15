#include "stdafx.h"
#include "TRefSys.h"
#include <assert.h>
#include "TRefSysWidget.h"



TRefSys::TRefSys(const QString& scope, const QString& name, const ValueType& value)
	:TVariate(scope, name, TSymbol::TYPE_REF_SYS)
	, m_value(value)
{
	Init();
}

TRefSys::TRefSys(const TRefSys& refSys)
	:TVariate(refSys)
	, m_value(refSys.m_value)
{
	Init();
}

TRefSys::TRefSys(QDataStream& dataStream)
	:TVariate(dataStream)
{
	QString baseSysName;
	dataStream >> m_value.baseSys;

	for (auto& value:m_value.offset)
	{
		dataStream >> value;
	}

	Init();
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

void TRefSys::WriteValueToStream(QDataStream& dataStream) const
{
	dataStream << m_value.baseSys;

	for (const auto& value: m_value.offset)
	{
		dataStream << value;
	}
}

void TRefSys::UpdateFromValue(const TVariate& variate)
{
	assert ( typeid(variate) == typeid(*this));

	m_value = static_cast<const TRefSys&>(variate).m_value;
}

void TRefSys::Init()
{
	m_variateWidget = new TRefSysWidget(this);
}
