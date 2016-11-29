#include "stdafx.h"
#include "TPosition.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"
#include "TPositionWidget.h"


inline
QString TPosition::TypeName()
{
	return "Position";
}

TPosition::TPosition(QDataStream& dataStream) : TVariate(dataStream)
{
	double value;

	for (int i = 0; i < AXIS_SIZE;++i)
	{
		dataStream >> value;
		m_value.m_AxisPosition[i] = value;
		//m_value.push_back(value);
	}

	Init();
}

//TPosition::TPosition(const QString& scope, const QString& name, const tAxesAllPositions& value)
//	:TVariate(scope, name, TSymbol::TYPE_POSITION)
//{
//	m_value = value;
//
//	Init();
//}

TPosition::TPosition(const TPosition& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

TPosition::TPosition(const TSymbol& symbol, ValueType value)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_POSITION ,TypeName()})
	, m_value(value)
{
	Init();
}

const tAxesAllPositions TPosition::GetValue() const
{
	return m_value;
}

void TPosition::SetValue(const tAxesAllPositions& value)
{
	m_value = value;
}

void TPosition::WriteValueToStream(QDataStream& dataStream)const
{
	for (int i = 0; i < AXIS_SIZE;++i)
	{
		dataStream << m_value.m_AxisPosition[i];
	}
}

void TPosition::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TPosition&>(variate).m_value;
}

void TPosition::Init()
{
	m_variateWidget = new TPositionWidget(this);
}


TVariate* TPosition::Clone() const
{
	return new TPosition(*this);
}
