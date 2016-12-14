#include "stdafx.h"
#include "TToolSys.h"
#include <assert.h>
#include "TToolSysWidget.h"


inline
QString TToolSys::TypeName()
{
	return "ToolSys";
}

//TToolSys::TToolSys(const QString& scope, const QString& name, ValueType value/* = {}*/)
//	:TVariate(scope,name,TSymbol::TYPE_TOOL_SYS)
//	, m_value(value)
//{
//	Init();
//}


TToolSys::TToolSys(const TToolSys& variate)
	:TVariate(variate)
{
	UpdateFromValue(variate);

	//Init();
}

TToolSys::TToolSys(QDataStream& dataStream)
	: TVariate(dataStream)
{
	m_value.ReadFromDataStream(dataStream);
	//for (auto& value:m_value)
	//{
	//	dataStream >> value;
	//}

}

TToolSys::TToolSys(const TSymbol& symbol, ValueType value /*= ValueType{}*/)
	:TVariate(TSymbol{ symbol.GetScope(), symbol.GetName(), TSymbol::TYPE_COMPLEX, TypeName() })
	, m_value(value)
{
}

TToolSys::~TToolSys()
{

}

TVariate* TToolSys::Clone() const
{
	return new TToolSys(*this);
}

TToolSys::ValueType::ValueType TToolSys::GetValue() const
{
	return m_value;
}

void TToolSys::SetValue(ValueType value)
{
	m_value = value;
}

void TToolSys::WriteValueToStream(QDataStream& dataStream) const
{
	m_value.WriteToDataStream(dataStream);
}

void TToolSys::UpdateFromValue(const TVariate& variate)
{
	m_value = dynamic_cast<const TToolSys&>(variate).m_value;
}

