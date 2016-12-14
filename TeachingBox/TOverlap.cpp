#include "stdafx.h"
#include "TOverlap.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "ComboBoxInTree.h"
#include "LineEditInTree.h"
#include "DataStruct.h"
#include "TOverlapWidget.h"


inline
QString TOverlap::TypeName()
{
	return "Overlap";
}

//TOverlap::TOverlap(const QString& scope, const QString& name, const tOverlapConstraint& value)
//	:TVariate(scope, name, TSymbol::TYPE_OVERLAP)
//	, m_value(value)
//{
//	Init();
//}

TOverlap::TOverlap(QDataStream& dataStream) : TVariate(dataStream)
{
	WriteValueSteam(dataStream);

}

TOverlap::TOverlap(const TOverlap& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

}

TOverlap::TOverlap(const TSymbol& symbol, ValueType value)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX,TypeName() })
	, m_value(value)
{
}

const tOverlapConstraint& TOverlap::GetValue() const
{
	return m_value;
}

void TOverlap::SetValue(const tOverlapConstraint& value)
{
	m_value = value;
}

void TOverlap::WriteValueToStream(QDataStream& dataStream)const
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


TVariateRegister<TOverlap> TOverlap::m_register{ TypeName() };

TVariate* TOverlap::Clone() const
{
	return new TOverlap(*this);
}
