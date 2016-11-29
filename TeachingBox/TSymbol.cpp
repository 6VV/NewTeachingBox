#include "stdafx.h"
#include "TSymbol.h"


//TSymbol::TSymbol(const QString& scope, const QString& name, const SymbolType type, const SymbolCategory category)
//	:m_scope(scope)
//	, m_name(name)
//	, m_type(type)
//	, m_category(category)
//{
//}

TSymbol::TSymbol(QDataStream& dataStream)
{
	dataStream >> m_scope;
	dataStream >> m_name;
	dataStream >> m_type;
	dataStream >> m_typeName;
}

TSymbol::TSymbol(const TSymbol& symbol)
	: m_scope(symbol.m_scope)
	, m_name(symbol.m_name)
	, m_type(symbol.m_type)
	, m_typeName(symbol.m_typeName)
	, m_category(symbol.m_category)
{

}

TSymbol::TSymbol(const QString& scope/*=""*/, const QString& name/*=""*/, const SymbolType type /*= SymbolType::TYPE_VOID*/,
	const QString& typeName/*=""*/, const SymbolCategory category /*= SymbolCategory::CATEGORY_VARIABLE*/)
	:m_scope(scope)
	, m_name(name)
	, m_type(type)
	, m_typeName(typeName)
	, m_category(category)
{

}

TSymbol& TSymbol::operator=(const TSymbol& symbol)
{
	m_scope = symbol.m_scope;
	m_name = symbol.m_name;
	m_type = symbol.m_type;
	m_typeName = symbol.m_typeName;
	m_category = symbol.m_category;

	return *this;
}

TSymbol::SymbolType TSymbol::GetType() const
{
	return static_cast<SymbolType>(m_type);
}

TSymbol::SymbolCategory TSymbol::GetCategory() const
{
	return m_category;
}

QString TSymbol::GetName() const
{
	return m_name;
}

QString TSymbol::GetScope() const
{
	return m_scope;
}

QString TSymbol::GetTypeName() const
{
	return m_typeName;
}

//void TSymbol::SetName(const QString& name)
//{
//	m_name = name;
//}

void TSymbol::WriteToStream(QDataStream& dataStream) const
{
	dataStream << m_scope;
	dataStream << m_name;
	dataStream << m_type;
	dataStream << m_typeName;
}

//QHash<TSymbol::SymbolType, QString> TSymbol::Map_Type = QHash<TSymbol::SymbolType, QString>{
//	{TYPE_VOID, "VOID"},
//	{ TYPE_INTERGER, "INTERGER" },
//	{ TYPE_DOUBLE, "DOUBLE" },
//	{ TYPE_STRING, "STRING" },
//	{ TYPE_BOOL, "BOOL" },
//	{ TYPE_POSITION, "POSITION" },
//	{ TYPE_DYNAMIC, "DYNAMIC" },
//	{ TYPE_OVERLAP, "OVERLAP" },
//	{ TYPE_REF_SYS, "REF_SYS" },
//	{ TYPE_TOOL_SYS, "TOOL_SYS" },
//};

