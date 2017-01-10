#include "stdafx.h"
#include "VariateValueFactory.h"
#include <assert.h>


void VariateValueFactory::Register(const QString& valueType, FunCreateValue fun)
{
	FunMap()[valueType] = fun;
	//m_funMap.insert(std::make_pair(valueType, fun));
}

std::shared_ptr<VariateValue> VariateValueFactory::CreateVariateValue(const QString& valueType)
{
	auto iter = FunMap().find(valueType);
	assert(iter != FunMap().end());

	return (*iter->second)();
}

VariateValueFactory::FunMapType& VariateValueFactory::FunMap()
{
	static FunMapType map{};
	return map;
}
