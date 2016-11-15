#include "stdafx.h"
#include "TDouble.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "TDoubleWidget.h"

TDouble::TDouble(const QString& scope, const QString& name, const double value)
	:TVariate(scope, name, TSymbol::TYPE_DOUBLE)
{
	m_value = value;

	Init();
}

TDouble::TDouble(QDataStream& dataStream) : TVariate(dataStream)
{
	dataStream >> m_value;

	Init();
}

TDouble::TDouble(const TDouble& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

double TDouble::GetValue()
{
	return m_value;
}

void TDouble::SetValue(const double value)
{
	m_value = value;
}

void TDouble::WriteValueToStream(QDataStream& dataStream)const
{
	dataStream << m_value;
}

void TDouble::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TDouble&>(variate).m_value;
}

void TDouble::Init()
{
	m_variateWidget = new TDoubleWidget(this);
}

TVariate* TDouble::Clone() const
{
	return new TDouble(*this);
}

