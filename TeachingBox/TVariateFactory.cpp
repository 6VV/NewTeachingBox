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
	//dataStream.device()->seek(0);

	//auto iter = FunMapGetVariate().find(symbol.GetTypeName());
	//assert(iter != FunMapGetVariate().end() && "Create variate failed\nNot find variate class");

	auto variate = CreateVariate(symbol);
	variate->ReadValueFromStream(dataStream);

	return variate;
}

std::shared_ptr<TVariate> TVariateFactory::CreateVariate(const TSymbol& symbol)
{
	auto type = symbol.GetTypeName();

	auto iter = FunMapCreateVariate().find(symbol.GetTypeName());

	assert(iter != FunMapCreateVariate().end() && "Create variate failed\nNot find variate class");

	return (*iter->second)(symbol);
}

//std::map<QString, TVariateFactory::FunGetVariate>& TVariateFactory::FunMapGetVariate()
//{
//	static std::map<QString, TVariateFactory::FunGetVariate> map;
//
//	return map;
//}

std::map<QString, TVariateFactory::FunCreateVariate>& TVariateFactory::FunMapCreateVariate()
{
	static std::map<QString, TVariateFactory::FunCreateVariate> map;

	return map;
}
