#include "stdafx.h"
#include "TVariateManager.h"
#include "TVariate.h"
#include "TScope.h"
#include "QByteArray"
#include "VariateDatabase.h"
#include "TVariateFactory.h"
#include "Exception.h"

using namespace Database;

TVariateManager* TVariateManager::GetInstance()
{
	return SingleTon<TVariateManager>::GetInstance();
}

TVariateManager::TVariateManager()
	:m_scopeRoot(new TScope())
{
	LoadInitDataFromDatabase();
}

TVariateManager::~TVariateManager()
{
	ClearMap();
}

void TVariateManager::AddVariate(const TVariate& object)
{
	TVariate* variate = object.Clone();
	AddInMemory(variate);
	AddInDatabase(variate);
}

void TVariateManager::DeleteVariate(const QString& scope, const QString& name)
{
	delete m_objectMap.value(scope).value(name);
	m_objectMap[scope].remove(name);

	m_scopeRoot->DeleteVariate(scope, name);
	VariateDatabase::DeleteVariate(scope, name);
}

QVector<TVariate*> TVariateManager::GetVariatesFromScope(const QString& scope)
{
	QVector<TVariate*> variates;

	auto iterVariate=m_objectMap.find(scope);

	if (iterVariate == m_objectMap.end())
	{
		return variates;
	}
	
	auto values=iterVariate.value();

	for (auto value:values)
	{
		variates.append(value);
	}

	return variates;
}

void TVariateManager::LoadInitDataFromDatabase()
{
	auto variates = VariateDatabase::SelectAllVariates();
	for (auto var : variates)
	{
		AddInMemory(TVariateFactory::CreateVariate(var));
	}
}


void TVariateManager::UpdateVariate(const QString& scope, const QString& name, const TVariate& newVariate)
{
	UpdateInMap(scope, name, newVariate);
	m_scopeRoot->UpdateVariate(scope, name, &newVariate);
	UpdateInDatabase(scope, name, newVariate);
}

void TVariateManager::AddInMemory(TVariate* const object)
{
	m_objectMap[object->GetScope()][object->GetName()] = object;
	m_scopeRoot->AddVariate(object);
}

void TVariateManager::AddInDatabase(TVariate* const object)
{
	QByteArray data;
	QDataStream dataStream(&data, QIODevice::ReadWrite);
	object->ReadDataStream(dataStream);
	dataStream.device()->seek(0);
	VariateDatabase::InsertVariate(dataStream);
}

void TVariateManager::ClearMap()
{
	for (auto iterMap = m_objectMap.begin(); iterMap != m_objectMap.end(); iterMap++)
	{
		for (auto iterVar = iterMap.value().begin(); iterVar != iterMap.value().end(); iterVar++)
		{
			delete iterVar.value();
		}
	}
	m_objectMap.clear();
}

void TVariateManager::UpdateInMap(const QString& scope, const QString& name, const TVariate& newVariate)
{
	auto iterMap = m_objectMap.find(scope);
	auto iterVar = iterMap.value().find(name);

	auto ptrVariate = iterVar.value();
	ptrVariate->UpdateFromVariate(newVariate);

	iterMap.value().erase(iterVar);

	m_objectMap[scope][name] = ptrVariate;
}

void TVariateManager::UpdateInDatabase(const QString& scope, const QString& name, const TVariate& newVariate)
{
	QByteArray data;
	QDataStream dataStream(&data, QIODevice::ReadWrite);
	newVariate.ReadDataStream(dataStream);
	VariateDatabase::UpdateVariate(scope, name, dataStream);
}

