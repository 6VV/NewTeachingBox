﻿#include "stdafx.h"
#include "TVariateContext.h"
#include "TVariateScopeNode.h"
#include "ProjectContext.h"
#include "TVariateFactory.h"
#include "TVariate.h"
#include <assert.h>
#include "VariateDatabase.h"



TVariateContext::TVariateContext()
{
	InitScope();
}

TVariateContext* TVariateContext::GetInstance()
{
	static TVariateContext context;
	return &context;
}

void TVariateContext::AddVariate(std::shared_ptr<TVariate> variate)
{
	auto variateScope = variate->GetScope();
	auto scopeNode = m_rootNode->FindChildScope(variateScope);

	if (scopeNode!=nullptr)
	{
		scopeNode->AddOrUpdateVariate(variate);
	}
	else
	{
		AddScopeWithoutCheck(variateScope);
		
		m_rootNode->FindChildScope(variateScope)->AddOrUpdateVariate(variate);
	}
}

void TVariateContext::AddScope(const QString& scope)
{
	if (m_rootNode->FindChildScope(scope)==nullptr)
	{
		AddScopeWithoutCheck(scope);
	}
}

void TVariateContext::Clear()
{
	m_rootNode = nullptr;
	InitScope();
}

void TVariateContext::DeleteVariate(const QString& scope, const QString& name)
{
	m_rootNode->FindChildScope(scope)->DeleteVariate(name);
}

std::shared_ptr<TVariate> TVariateContext::GetVariate(const QString& scope, const QString& name) const
{
	return m_rootNode->FindChildScope(scope)->FindVariate(name);
}

std::shared_ptr<TVariate> TVariateContext::GetVariateScollUp(const QString& scope, const QString& name) const
{
	auto currentScope=m_rootNode->FindChildScope(scope).get();
	while (currentScope!=nullptr)
	{
		auto variate = currentScope->FindVariate(name);
		if (variate==nullptr)
		{
			currentScope = currentScope->GetParentNode();
			continue;
		}

		return variate;
	}

	return nullptr;
}

QVector<std::shared_ptr<TVariate>> TVariateContext::GetVariates(const QString& scope) const
{
	auto node = m_rootNode->FindChildScope(scope);
	if (node==nullptr)
	{
		return {};
	}

	return node->GetVariates();
}

QVector<std::shared_ptr<TVariate>> TVariateContext::GetVariates(const QString& scope, const QString& typeName)
{
	auto node = m_rootNode->FindChildScope(scope);
	if (node == nullptr)
	{
		return{};
	}

	QVector<std::shared_ptr<TVariate>> result{};
	auto variates = node->GetVariates();
	for (auto variate:variates)
	{
		if (variate->GetTypeName()==typeName)
		{
			result.append(variate);
		}
	}
	return result;
}

QVector<std::shared_ptr<TVariate>> TVariateContext::GetAvailableVariatesScollUp(const QString& scope) const
{
	QVector<std::shared_ptr<TVariate>> result;
	QStringList names{};

	auto scopeNode = m_rootNode->FindChildScope(scope).get();
	while (scopeNode != nullptr)
	{
		auto variates = GetVariates(scopeNode->GetName());

		for (auto variate:variates)
		{
			if (!names.contains(variate->GetName()))
			{
				result.push_back(variate);
				names.push_back(variate->GetName());
			}
		}
		
		scopeNode = scopeNode->GetParentNode();
	}

	return result;
}

QVector<std::shared_ptr<TVariate>> TVariateContext::GetAvailableVariatesScollUp(const QString& scope, const QString& typeName)
{
	QVector<std::shared_ptr<TVariate>> result;
	QStringList names{};

	auto scopeNode = m_rootNode->FindChildScope(scope).get();
	while (scopeNode != nullptr)
	{
		auto variates = GetVariates(scopeNode->GetName(),typeName);

		for (auto variate : variates)
		{
			if (!names.contains(variate->GetName()))
			{
				result.push_back(variate);
				names.push_back(variate->GetName());
			}
		}

		scopeNode = scopeNode->GetParentNode();
	}

	return result;
}

QMap<QString, QVector<std::shared_ptr<TVariate>>> TVariateContext::GetAllVariatesMapScollUp(const QString& scope) const
{
	QMap<QString, QVector<std::shared_ptr<TVariate>>> result;

	auto scopeNode = m_rootNode->FindChildScope(scope).get();
	while (scopeNode != nullptr)
	{
		result[scopeNode->GetName()] = std::move(GetVariates(scopeNode->GetName()));
		scopeNode = scopeNode->GetParentNode();
	}

	return result;
}

QVector<std::shared_ptr<TVariate>> TVariateContext::GetAllVariates(const QString& typeName) const
{
	QVector<std::shared_ptr<TVariate>> result{};
	PushScopeVariates(m_rootNode,result,typeName);

	return result;
}

void TVariateContext::UpdateVariate(std::shared_ptr<TVariate> newVariate)
{
	m_rootNode->FindChildScope(newVariate->GetScope())->AddOrUpdateVariate(newVariate);
}

inline
void TVariateContext::AddProjectScopeNode(const QString& nodeName)
{
	m_rootNode->FindChildScope(ProjectContext::ScopeGlobal())->AddChild(std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(nodeName)));
}

inline
void TVariateContext::AddProgramScopeNode(const QString& nodeName)
{
	auto nameList = nodeName.split(".");
	assert(nameList.size() == 2);

	auto projectNode = m_rootNode->FindChildScope(nameList.at(0));

	/*若未添加项目作用域*/
	if (projectNode==nullptr)
	{
		AddProjectScopeNode(nameList.at(0));
		projectNode = m_rootNode->FindChildScope(nameList.at(0));
		assert(projectNode != nullptr);
	}

	projectNode->AddChild(std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(nodeName)));
}

void TVariateContext::AddScopeWithoutCheck(const QString& scope)
{
	/*若为项目作用域*/
	if (scope.split(".").size() <= 1)
	{
		AddProjectScopeNode(scope);
	}
	/*若为程序作用域*/
	else
	{
		AddProgramScopeNode(scope);
	}
}

void TVariateContext::InitScope()
{
	m_rootNode = std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode());
	auto systemNode= std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(ProjectContext::ScopeSystem()));
	auto cooperateNode = std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(ProjectContext::ScopeCooperate()));

	m_rootNode->AddChild(systemNode);
	systemNode->AddChild(cooperateNode);
	cooperateNode->AddChild(std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(ProjectContext::ScopeGlobal())));
}

void TVariateContext::PushScopeVariates(std::shared_ptr<TVariateScopeNode> scopeNode, QVector<std::shared_ptr<TVariate>>& desVariates, const QString& typeName) const
{
	auto scopeVariates = scopeNode->GetVariates();
	for (auto variate:scopeVariates)
	{
		if (variate->GetTypeName()==typeName)
		{
			desVariates.append(variate);
		}
	}

	auto childScopes = scopeNode->GetChildScopes();
	for (auto childScope:childScopes)
	{
		PushScopeVariates(childScope, desVariates,typeName);
	}
}

