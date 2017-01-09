#include "stdafx.h"
#include "ProjectVariatesXmlManager.h"
#include "QFile"
#include "ProjectManager.h"
#include "qxmlstream.h"
#include "TVariateContext.h"
#include "ProjectContext.h"
#include "TVariate.h"
#include "TInteger.h"
#include "TDouble.h"
#include "TString.h"
#include "TBool.h"
#include "TOverlap.h"
#include "TComplex.h"
#include "VariateValue.h"
#include "TVariateFactory.h"
#include "VariateDatabase.h"


void ProjectVariatesXmlManager::WriteToXml(const QString& projectName) const	/*将项目变量导出到xml文件*/
{
	QFile file(ProjectManager::PROJECT_PATH + "/" + projectName+"/"+projectName + ".xml");
	if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
	{
		return;
	}

	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.setCodec("UTF-8");
	writer.writeStartDocument();

	writer.writeStartElement("Variates");

	auto variatesArray = Database::VariateDatabase::SelectAllVariates();
	WriteOriVariates(writer, variatesArray);
	WriteProjectVariates(writer, variatesArray,projectName);

	writer.writeEndElement();

	writer.writeEndDocument();
	file.close();
}


void ProjectVariatesXmlManager::WriteOriVariates(QXmlStreamWriter& writer, QVector<QByteArray>& variatesArray) const
{
	WriteScopeVariates(writer, ProjectContext::ScopeSystem(), variatesArray);
	WriteScopeVariates(writer, ProjectContext::ScopeCooperate(), variatesArray);
	WriteScopeVariates(writer, ProjectContext::ScopeGlobal(), variatesArray);
}

void ProjectVariatesXmlManager::WriteProjectVariates(QXmlStreamWriter& writer, QVector<QByteArray>& variatesArray, const QString& projectName) const
{
	WriteScopeVariates(writer, projectName, variatesArray);

	ProjectManager manager;
	auto programs = manager.GetProjectFiles(projectName);
	for (auto program:programs)
	{
		WriteScopeVariates(writer, program, variatesArray);
	}
}

void ProjectVariatesXmlManager::WriteVariate(QXmlStreamWriter& writer, std::shared_ptr<TVariate> variate) const
{
	writer.writeStartElement("Variate");

	writer.writeTextElement("Name",variate->GetName());
	writer.writeTextElement("Type", variate->GetTypeName());
	
	if (typeid(*variate)==typeid(TInteger))
	{
		writer.writeTextElement("Value", QString::number(std::dynamic_pointer_cast<TInteger>(variate)->GetValue()));
	}
	else if (typeid(*variate) == typeid(TDouble))
	{
		writer.writeTextElement("Value", QString::number(std::dynamic_pointer_cast<TDouble>(variate)->GetValue()));
	}
	else if (typeid(*variate) == typeid(TString))
	{
		writer.writeTextElement("Value", std::dynamic_pointer_cast<TString>(variate)->GetValue());
	}
	else if (typeid(*variate) == typeid(TBool))
	{
		auto value = std::dynamic_pointer_cast<TBool>(variate)->GetValue();
		QString valueName = "TRUE";
		if (!value)
		{
			valueName = "FALSE";
		}
		writer.writeTextElement("Value", valueName);
	}
	else if (typeid(*variate) == typeid(TOverlap))
	{
		auto value = std::dynamic_pointer_cast<TOverlap>(variate)->GetValue();
		writer.writeTextElement("Transition Parameter", QString::number(value.m_TransitionParameter));
		writer.writeTextElement("Transition Mode", QString::number(value.m_TransitionMode));
	}
	else
	{
		auto valueNames = std::dynamic_pointer_cast<TComplex>(variate)->GetValueNames();
		auto values = std::dynamic_pointer_cast<TComplex>(variate)->GetValues();
		for (size_t i = 0; i < values.size();++i)
		{
			writer.writeTextElement(valueNames.at(i), values.at(i)->ToStrings().at(0));
		}
	}

	writer.writeEndElement();
}

void ProjectVariatesXmlManager::WriteScopeVariates(QXmlStreamWriter& writer, const QString& scope, QVector<QByteArray>& variatesArray) const
{
	writer.writeStartElement(scope);

	for (auto& variateBytes : variatesArray)
	{
		auto variate = TVariateFactory::GetVariate(variateBytes);
		if (variate->GetScope() == scope)
		{
			WriteVariate(writer, variate);
		}
	}

	writer.writeEndElement();
}

