#include "stdafx.h"
#include "TBool.h"
#include "TreeWidgetItemWithVariate.h"
#include "TBoolWidget.h"


TBool::TBool(const QString& scope, const QString& name, const bool value)
	:TVariate(scope, name, TSymbol::TYPE_BOOL), m_value(value)
{
	Init();
}

TBool::TBool(QDataStream& dataStream) : TVariate(dataStream)
{
	dataStream >> m_value;

	Init();
}

TBool::TBool(const TBool& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

const bool TBool::GetValue() const
{
	return m_value;
}

void TBool::SetValue(const bool value)
{
	m_value = value;
}

void TBool::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TBool::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TBool&>(variate).m_value;
}


void TBool::Init()
{
	m_variateWidget = new TBoolWidget(this);
}

TVariate* TBool::Clone() const
{
	return new TBool(*this);
}

