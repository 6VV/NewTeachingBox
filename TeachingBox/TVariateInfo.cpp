#include "stdafx.h"
#include "TVariateInfo.h"
#include "TInteger.h"
#include "TDouble.h"
#include "TBool.h"
#include "TString.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"
#include "TRefSys.h"
#include "TToolSys.h"



void TVariateInfo::RegisterCategory(const QString& category, const QString& newType)
{
	auto iter = CategoryMap().find(category);
	if (iter == CategoryMap().end())
	{
		CategoryMap()[category] = std::make_shared<std::set<QString>>();
	}

	CategoryMap()[category]->insert(newType);
}

void TVariateInfo::RegisterAbbreviation(const QString& wholeName, const QString& abbreviation)
{
	AbbreviationMap()[wholeName] = abbreviation;
}

TVariateInfo::CategoryMapType& TVariateInfo::CategoryMap()
{
	static CategoryMapType map{
		/*添加基本类型*/
		{ "Base", std::shared_ptr<std::set<QString>>(new std::set<QString>{
			TInteger::TypeName(),
			TDouble::TypeName(),
			TBool::TypeName(),
			TString::TypeName()
		}) },

		/*添加坐标系类型*/
		{ "RefSys", std::shared_ptr<std::set<QString>>(new std::set<QString>{
			TRefSys::TypeName(),
			TToolSys::TypeName()
		}) },
	};

	return map;
}

QString TVariateInfo::GetAbbreviation(const QString& wholeName)
{
	auto iter = AbbreviationMap().find(wholeName);
	if (iter==AbbreviationMap().end())
	{
		return wholeName;
	}

	return iter->second;
}

TVariateInfo::AbbreviationMapType& TVariateInfo::AbbreviationMap()
{
	static AbbreviationMapType map{};

	return map;
}
