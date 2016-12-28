#include "stdafx.h"
#include "MacroManager.h"
#include "MacroInfo.h"
#include "qdom.h"



MacroManager* MacroManager::GetInstance()
{
	static MacroManager manager;
	return &manager;
}

std::shared_ptr<MacroManager::MacroMap> MacroManager::GetMacroMap()
{
	return m_macroMap;
}

std::shared_ptr<MacroManager::TypeMap> MacroManager::GetCategoryTypeMap()
{
	return m_categoryTypeMap;
}

std::shared_ptr<MacroManager::TypeMap> MacroManager::GetTypeMacroMap()
{
	return m_typeMacroMap;
}

MacroManager::MacroManager()
	:m_macroMap(std::make_shared<MacroMap>())
	, m_categoryTypeMap(std::make_shared<TypeMap>())
	, m_typeMacroMap(std::make_shared<TypeMap>())
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
					else
					{
						text = parameters.at(k).toElement().text();
					}
				}

				(*m_macroMap)[macroName] = std::make_shared<MacroInfo>(macroName, id, parameterTypes, categoryName, typeName,text);
			}
		}
	}

	file.close();
}


