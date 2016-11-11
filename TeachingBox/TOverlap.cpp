#include "stdafx.h"
#include "TOverlap.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "ComboBoxInTree.h"
#include "LineEditInTree.h"
#include "DataStruct.h"
#include "TOverlapWidget.h"



TOverlap::TOverlap(const QString& scope, const QString& name, const tOverlapConstraint& value)
	:TVariate(scope, name, TSymbol::TYPE_OVERLAP)
	, m_value(value)
{
	Init();
}

TOverlap::TOverlap(QDataStream& dataStream) : TVariate(dataStream)
{
	WriteValueSteam(dataStream);

	Init();
}

TOverlap::TOverlap(const TOverlap& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

const tOverlapConstraint& TOverlap::GetValue() const
{
	return m_value;
}

void TOverlap::SetValue(const tOverlapConstraint& value)
{
	m_value = value;
}

void TOverlap::ReadValueStream(QDataStream& dataStream)const
{
	dataStream << m_value.m_TransitionMode;
	dataStream << m_value.m_TransitionParameter;
}

void TOverlap::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TOverlap&>(variate).m_value;
}

void TOverlap::WriteValueSteam(QDataStream& dataStream)
{
	dataStream >> m_value.m_TransitionMode;
	dataStream >> m_value.m_TransitionParameter;
}

void TOverlap::Init()
{
	m_variateWidget = new TOverlapWidget(this);
}

TVariate* TOverlap::Clone() const
{
	return new TOverlap(*this);
}
