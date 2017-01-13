#include "stdafx.h"
#include "MacroManager.h"
#include "MacroInfo.h"
#include "qdom.h"



MacroManager* MacroManager::GetInstance()
{
	static MacroManager manager;
	return &manager;
}

std::shared_ptr<MacroManager::MacroMap> MacroManager::GetMacroMap() const
{
	return m_macroMap;
}

std::shared_ptr<MacroManager::TypeMap> MacroManager::GetCategoryTypeMap()const
{
	return m_categoryTypeMap;
}

std::shared_ptr<MacroManager::TypeMap> MacroManager::GetTypeMacroMap()const
{
	return m_typeMacroMap;
}

std::shared_ptr<std::set<int>> MacroManager::GetIdSet() const
{
	return m_idSet;
}

std::shared_ptr<QStringList> MacroManager::GetKeywords() const
{
	return m_keywords;
}

MacroManager::MacroManager()
	:m_macroMap(std::make_shared<MacroMap>())
	, m_categoryTypeMap(std::make_shared<TypeMap>())
	, m_typeMacroMap(std::make_shared<TypeMap>())
	, m_idSet(std::make_shared<std::set<int>>())
	, m_keywords(std::make_shared<QStringList>())
{
	InitMapFromXmlFile();
}

void MacroManager::InitMapFromXmlFile()
{
	QFile file("./Resources/xml/Macro.xml");
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
	for (int i = 0; i < categorys.size(); ++i)
	{
		QString categoryName = categorys.at(i).toElement().attribute("name");

		/*遍历分类*/
		auto types = categorys.at(i).childNodes();
		for (int m = 0; m < types.length(); ++m)
		{
			QString typeName = types.at(m).toElement().attribute("name");
			(*m_categoryTypeMap)[categoryName].insert(typeName);

			/*遍历命令*/
			auto macros = types.at(m).childNodes();
			for (int j = 0; j < macros.length(); ++j)
			{
				auto macroNode = macros.at(j);

				QString macroName = macroNode.toElement().attribute("name");
				(*m_typeMacroMap)[typeName].insert(macroName);
				m_keywords->append(macroName);

				bool ok;
				int id = macroNode.toElement().attribute("id").toInt(&ok);
				if (!ok)
				{
					id = -1;
				}

				QStringList parameterTypes{};
				QString text{};
				auto parameters = macroNode.childNodes();
				for (int k = 0; k < parameters.size(); ++k)
				{
					if (parameters.at(k).nodeName() == "Parameter")
					{
						parameterTypes.append(parameters.at(k).toElement().text());
					}
					else if (parameters.at(k).nodeName() == "Text")
					{
						text = parameters.at(k).toElement().text();
					}
					else if (parameters.at(k).nodeName() == "ExtraKeywords")
					{
						auto keywords = parameters.at(k).toElement().text().split(" ");
						m_keywords->append(keywords);
					}
				}

				(*m_macroMap)[macroName] = std::make_shared<MacroInfo>(macroName, id, parameterTypes, categoryName, typeName,text);
				m_idSet->insert(id);
			}
		}
	}

	file.close();
}


