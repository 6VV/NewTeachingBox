#include "stdafx.h"
#include "TVariateFactory.h"
#include "TInteger.h"
#include "TDouble.h"
#include "TBool.h"
#include "TString.h"
#include "TPosition.h"
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

TVariateFactory::FunCreateVariate TVariateFactory::GetFun(const QString& type)
{
	auto iter = FunMapCreateVariate().find(type);
	if (iter==FunMapCreateVariate().end())
	{
		return nullptr;
	}

	return iter->second;
}

std::shared_ptr<TVariate> TVariateFactory::CreateVariate(const TSymbol& symbol)
{
	auto type = symbol.GetTypeName();

	auto iter = FunMapCreateVariate().find(symbol.GetTypeName());

	assert(iter != FunMapCreateVariate().end() && "Create variate failed\nNot find variate class");

	return (*iter->second)(symbol);
}

void TVariateFactory::Register(const QString& type, FunCreateVariate fun)
{
	FunMapCreateVariate()[type] = fun;
}

std::map<QString, TVariateFactory::FunCreateVariate>& TVariateFactory::FunMapCreateVariate()
{
	static std::map<QString, TVariateFactory::FunCreateVariate> map;

	return map;
}
