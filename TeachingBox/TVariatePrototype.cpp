#include "stdafx.h"
#include "TVariatePrototype.h"
#include "qdom.h"
#include "TSymbol.h"
#include "TComplex.h"
#include "TVariateFactory.h"
#include "EnumValue.h"
#include "VariateValueFactory.h"
#include "TVariate.h"
#include <assert.h>
#include "TVariateInfo.h"



TVariatePrototype::PrototypeMap TVariatePrototype::m_prototypeMap{};

std::shared_ptr<TVariate> TVariatePrototype::CreateVariate(const TSymbol& symbol)
{
	auto iter = m_prototypeMap.find(symbol.GetTypeName());
	assert(iter != m_prototypeMap.end());
	if (iter == m_prototypeMap.end())
	{
		return nullptr;
	}

	auto result = std::shared_ptr<TVariate>(iter->second->Clone());
	result->SetSymbol(symbol);
	return result;
}

void TVariatePrototype::InitPrototype()
{
	QFile file("./Resources/xml/Variates.xml");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
		
		//assert(1==2);
		return;
	}

	QDomDocument document;
	if (!document.setContent(&file, false))
	{
		file.close();
		return;
	}

	if (document.isNull())
	{
		return;
	}

	/*遍历分类*/
	auto variates = document.documentElement().childNodes();
	for (int i = 0; i < variates.size(); ++i)
	{
		InitCategoryProperty(variates.at(i));
	}

	file.close();
}

void TVariatePrototype::InitCategoryProperty(const QDomNode& categoryNode)
{
	auto categoryName = categoryNode.toElement().attribute("name");

	/*遍历变量*/
	auto variates = categoryNode.childNodes();

	for (int k = 0; k < variates.size();++k)
	{
		QString typeName = variates.at(k).toElement().attribute("typeName");
		TVariateInfo::RegisterCategory(categoryName, typeName);	/*注册变量分类*/

		InitVariateProperty(variates.at(k));
	}
}

TVariatePrototype::Initialization TVariatePrototype::m_initialization{};

void TVariatePrototype::InitVariateProperty(const QDomNode& variateNode)
{
	auto typeName = variateNode.toElement().attribute("typeName");
	auto abbreviation = variateNode.toElement().attribute("abbreviation");

	/*注册变量类型缩写名*/
	if (abbreviation.size()==0)
	{
		abbreviation = typeName;
	}
	TVariateInfo::RegisterAbbreviation(typeName, abbreviation);	

	auto variate = std::make_shared<TComplex>(TSymbol("", "", TSymbol::TYPE_COMPLEX, typeName));

	/*遍历值*/
	auto values = variateNode.childNodes();
	for (int i = 0; i < values.length(); ++i)
	{
		auto valueType = values.at(i).toElement().attribute("type");
		auto valueName = values.at(i).toElement().attribute("name");

		variate->m_valueNames.append(valueName);

		if (valueType == EnumValue::TypeText())
		{
			variate->m_commonValues.push_back(GetEnumValue(values.at(i)));
		}
		else
		{
			variate->m_commonValues.push_back(VariateValueFactory::CreateVariateValue(valueType));
		}
	}

	m_prototypeMap[typeName] = variate;
	TVariateFactory::Register(typeName, CreateVariate);	/*注册变量生成函数*/
}

std::shared_ptr<EnumValue> TVariatePrototype::GetEnumValue(const QDomNode& node)
{
	auto definition = node.toElement().attribute("definition");	/*定义名*/
	auto values=node.namedItem(definition).childNodes();

	EnumValue::EnumMapType map{};
	for (int i = 0; i < values.size();++i)
	{
		map[values.at(i).toElement().attribute("id").toInt()] = values.at(i).toElement().attribute("text");
	}

	return std::make_shared<EnumValue>(map,map.begin()->first);
}

TVariatePrototype::Initialization::Initialization()
{
	TVariatePrototype::InitPrototype();
}
