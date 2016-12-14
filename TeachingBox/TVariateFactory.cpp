#include "stdafx.h"
#include "TVariateFactory.h"
#include "TInteger.h"
#include "TDouble.h"
#include "TBool.h"
#include "TString.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"
#include <assert.h>
#include "TRefSys.h"
#include "TToolSys.h"



std::shared_ptr<TVariate> TVariateFactory::GetVariate(QByteArray& dataBytes)
{
	QDataStream dataStream(&dataBytes, QIODevice::ReadOnly);
	TSymbol symbol(dataStream);
	dataStream.device()->seek(0);

	auto iter = FunMapGetVariate().find(symbol.GetTypeName());

	assert(iter!=FunMapGetVariate().end() && "Create variate failed\nNot find variate class");

	return (*iter->second)(dataStream);
	/*switch (symbol.GetType())
	{
	case TSymbol::TYPE_INTERGER:
	{
		return std::shared_ptr<TVariate>(new TInteger(dataStream));
	}break;
	case TSymbol::TYPE_DOUBLE:
	{
		return std::shared_ptr<TVariate>(new TDouble(dataStream));
	}break;
	case TSymbol::TYPE_BOOL:
	{
		return std::shared_ptr<TVariate>(new TBool(dataStream));
	}break;
	case TSymbol::TYPE_STRING:
	{
		return std::shared_ptr<TVariate>(new TString(dataStream));
	}break;
	case TSymbol::TYPE_POSITION:
	{
		return std::shared_ptr<TVariate>(new TPosition(dataStream));
	}break;
	case TSymbol::TYPE_DYNAMIC:
	{
		return std::shared_ptr<TVariate>(new TDynamic(dataStream));
	}break;
	case TSymbol::TYPE_OVERLAP:
	{
		return std::shared_ptr<TVariate>(new TOverlap(dataStream));
	}break;
	case TSymbol::TYPE_REF_SYS:
	{
		return std::shared_ptr<TVariate>(new TRefSys(dataStream));
	}
	case TSymbol::TYPE_TOOL_SYS:
	{
		return std::shared_ptr<TVariate>(new TToolSys(dataStream));
	}
	default:
	{
		assert(!"Create variate failed\nNot find variate class");
		return nullptr;
	}break;
	}*/
}

std::shared_ptr<TVariate> TVariateFactory::CreateVariate(const TSymbol& symbol)
{
	auto type = symbol.GetTypeName();

	auto iter = FunMapCreateVariate().find(symbol.GetTypeName());

	assert(iter != FunMapCreateVariate().end() && "Create variate failed\nNot find variate class");

	return (*iter->second)(symbol);
	/*if (type == TInteger::TypeName())
	{
		return std::shared_ptr<TVariate>(new TInteger(symbol));
	}
	else if (type == TDouble::TypeName())
	{
		return std::shared_ptr<TVariate>(new TDouble(symbol));
	}
	else if (type == TBool::TypeName())
	{
		return std::shared_ptr<TVariate>(new TBool(symbol));
	}
	else if (type == TString::TypeName())
	{
		return std::shared_ptr<TVariate>(new TString(symbol));
	}
	else if (type == TPosition::TypeName())
	{
		return std::shared_ptr<TVariate>(new TPosition(symbol));
	}
	else if (type == TDynamic::TypeName())
	{
		return std::shared_ptr<TVariate>(new TDynamic(symbol));
	}
	else if (type == TOverlap::TypeName())
	{
		return std::shared_ptr<TVariate>(new TOverlap(symbol));
	}
	else if (type == TRefSys::TypeName())
	{
		return std::shared_ptr<TVariate>(new TRefSys(symbol));
	}
	else if (type == TToolSys::TypeName())
	{
		return std::shared_ptr<TVariate>(new TToolSys(symbol));
	}
	else
	{
		assert(!"Create variate failed\nNot find variate class");
		return nullptr;
	}*/
}

std::map<QString, TVariateFactory::FunGetVariate>& TVariateFactory::FunMapGetVariate()
{
	static std::map<QString, TVariateFactory::FunGetVariate> map;

	return map;
}

std::map<QString, TVariateFactory::FunCreateVariate>& TVariateFactory::FunMapCreateVariate()
{
	static std::map<QString, TVariateFactory::FunCreateVariate> map;

	return map;
}
