#include "stdafx.h"
#include "MacroReader.h"
#include "QFile"
#include "QDomDocument"
#include "QUrl"


void MacroReader::InitMacro()
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

			/*遍历命令*/
			auto macros = types.at(m).childNodes();
			for (int j = 0; j < macros.length(); ++j)
			{
				auto macroNode = macros.at(j);

				QString macroName = macroNode.toElement().attribute("name");

				bool ok;
				int id = macroNode.toElement().attribute("id").toInt(&ok);
				if (!ok)
				{
					id=-1;
				}

				QStringList parameterTypes{};
				QString text{};
				auto parameters = macroNode.childNodes();
				for (int k = 0; k < parameters.size(); ++k)
				{
					if (parameters.at(k).nodeName()=="Parameter")
					{
						parameterTypes.append(parameters.at(k).toElement().text());
					}
					else
					{
						text = parameters.at(k).toElement().text();
					}
				}
				qDebug() << categoryName;
				qDebug() << typeName;
				qDebug() << macroName << " " << id;
				qDebug() << text;
				for (auto type : parameterTypes)
				{
					qDebug() << type;
				}
			}
		}
	}

	file.close();
}

MacroReader::Initialization MacroReader::m_initlization{};

MacroReader::Initialization::Initialization()
{
	MacroReader::InitMacro();
}
