#include "stdafx.h"
#include "VariateReader.h"
#include "qdom.h"



void VariateReader::InitVariatePrototype()
{
	QFile file("./Resources/xml/Variates.xml");
	if (!file.open(QIODevice::ReadOnly | QFile::Text))
	{
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
	auto categorys = document.documentElement().childNodes();
	for (int j = 0; j < categorys.size(); ++j)
	{
		auto categoryName = categorys.at(j).toElement().attribute("name");

		/*遍历变量*/
		auto variates = categorys.at(j).childNodes();
		for (int i = 0; i < variates.size(); ++i)
		{
			QString typeName = variates.at(i).toElement().attribute("typeName");

			/*遍历值*/
			auto values = variates.at(i).childNodes();
			for (int i = 0; i < values.length(); ++i)
			{
				auto valueType = values.at(i).toElement().attribute("type");
				auto valueName = values.at(i).toElement().attribute("name");

				qDebug() << categoryName+": "+ typeName + ": " << valueType + " " << valueName;
			}
		}
	}

	file.close();
}

//void VariateReader::InitVariate(const QDomNode& domNode)
//{
//	QString typeName = domNode.toElement().attribute("typeName");
//
//	/*遍历值*/
//	auto values = domNode.childNodes();
//	for (int i = 0; i < values.length(); ++i)
//	{
//		auto valueType = values.at(i).toElement().attribute("type");
//		auto valueName = values.at(i).toElement().attribute("name");
//		
//		qDebug() << typeName + ": " << valueType + " " << valueName;
//	}
//}

//VariateReader::Initialization VariateReader::m_initlization{};

VariateReader::Initialization::Initialization()
{
	VariateReader::InitVariatePrototype();
}
