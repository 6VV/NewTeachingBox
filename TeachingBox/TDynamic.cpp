#include "stdafx.h"
#include "TDynamic.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"
#include "TDynamicWidget.h"



TDynamic::TDynamic(const QString& scope, const QString& name, const tDynamicConstraint& value)
	:TVariate(scope,name,TSymbol::TYPE_DYNAMIC)
{
	m_value = value;

	Init();
}

TDynamic::TDynamic(QDataStream& dataStream) : TVariate(dataStream)
{
	WriteValueStream(dataStream);

	Init();
}

TDynamic::TDynamic(const TDynamic& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

const tDynamicConstraint& TDynamic::GetValue() const
{
	return m_value;
}

void TDynamic::SetValue(const tDynamicConstraint& value)
{
	m_value = value;
}

void TDynamic::WriteValueStream(QDataStream& dataStream)
{
	dataStream >> m_value.m_Velocity;
	dataStream >> m_value.m_Acceleration;
	dataStream >> m_value.m_Deceleration;

	dataStream >> m_value.m_PostureVelocity;
	dataStream >> m_value.m_PostureAcceleration;
	dataStream >> m_value.m_PostureDeceleration;
}


void TDynamic::Init()
{
	m_variateWidget = new TDynamicWidget(this);
}

TVariate* TDynamic::Clone() const
{
	return new TDynamic(*this);
}

void TDynamic::ReadValueStream(QDataStream& dataStream)const
{
	dataStream << m_value.m_Velocity;
	dataStream << m_value.m_Acceleration;
	dataStream << m_value.m_Deceleration;

	dataStream << m_value.m_PostureVelocity;
	dataStream << m_value.m_PostureAcceleration;
	dataStream << m_value.m_PostureDeceleration;
}

void TDynamic::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TDynamic&>(variate).m_value;
}
