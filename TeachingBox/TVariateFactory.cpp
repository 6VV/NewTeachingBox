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



TVariate* TVariateFactory::CreateVariate(QByteArray& dataBytes)
{
	QDataStream dataStream(&dataBytes, QIODevice::ReadOnly);
	TSymbol symbol(dataStream);
	dataStream.device()->seek(0);
	switch (symbol.GetType())
	{
	case TSymbol::TYPE_INTERGER:
	{
		return new TInteger(dataStream);
	}break;
	case TSymbol::TYPE_DOUBLE:
	{
		return new TDouble(dataStream);
	}break;
	case TSymbol::TYPE_BOOL:
	{
		return new TBool(dataStream);
	}break;
	case TSymbol::TYPE_STRING:
	{
		return new TString(dataStream);
	}break;
	case TSymbol::TYPE_POSITION:
	{
		return new TPosition(dataStream);
	}break;
	case TSymbol::TYPE_DYNAMIC:
	{
		return new TDynamic(dataStream);
	}break;
	case TSymbol::TYPE_OVERLAP:
	{
		return new TOverlap(dataStream);
	}break;
	case TSymbol::TYPE_REF_SYS:
	{
		return new TRefSys(dataStream);
	}
	case TSymbol::TYPE_TOOL_SYS:
	{
		return new TToolSys(dataStream);
	}
	default:
	{
		assert(!"Create variate failed\nNot find variate class");
		return nullptr;
	}break;
	}
}

std::shared_ptr<TVariate> TVariateFactory::GetVariate(QByteArray& dataBytes)
{
	QDataStream dataStream(&dataBytes, QIODevice::ReadOnly);
	TSymbol symbol(dataStream);
	dataStream.device()->seek(0);
	switch (symbol.GetType())
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
	}
}
