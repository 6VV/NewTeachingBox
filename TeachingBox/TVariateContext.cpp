#include "stdafx.h"
#include "TVariateContext.h"
#include "TVariateScopeNode.h"
#include "ProjectContext.h"
#include "TVariateFactory.h"
#include "TVariate.h"
#include <assert.h>



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
	auto scopeNode = m_rootNode->FindScope(variateScope);

	if (scopeNode!=nullptr)
	{
		scopeNode->AddOrUpdateVariate(variate);
	}
	else
	{
		AddScopeWithoutCheck(variateScope);
		
		m_rootNode->FindScope(variateScope)->AddOrUpdateVariate(variate);
	}
}

void TVariateContext::AddScope(const QString& scope)
{
	if (m_rootNode->FindScope(scope)==nullptr)
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
	m_rootNode->FindScope(scope)->DeleteVariate(name);
}

std::shared_ptr<TVariate> TVariateContext::GetVariate(const QString& scope, const QString& name) const
{
	return m_rootNode->FindScope(scope)->FindVariate(name);
}

std::shared_ptr<TVariate> TVariateContext::GetVariateScollUp(const QString& scope, const QString& name) const
{
	auto currentScope=m_rootNode->FindScope(scope).get();
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
	auto node = m_rootNode->FindScope(scope);
	if (node==nullptr)
	{
		return {};
	}

	return node->GetVariates();
}

QMap<QString, QVector<std::shared_ptr<TVariate>>> TVariateContext::GetVariatesMapScollUp(const QString& scope) const
{
	QMap<QString, QVector<std::shared_ptr<TVariate>>> result;

	auto scopeNode = m_rootNode->FindScope(scope).get();
	while (scopeNode != nullptr)
	{
		result[scopeNode->GetName()] = std::move(GetVariates(scopeNode->GetName()));
		scopeNode = scopeNode->GetParentNode();
	}

	return result;
}

void TVariateContext::UpdateVariate(std::shared_ptr<TVariate> newVariate)
{
	m_rootNode->FindScope(newVariate->GetScope())->AddOrUpdateVariate(newVariate);
}

inline
void TVariateContext::AddProjectScopeNode(const QString& nodeName)
{
	m_rootNode->FindScope(ProjectContext::ScopeGlobal())->AddChild(std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(nodeName)));
}

inline
void TVariateContext::AddProgramScopeNode(const QString& nodeName)
{
	auto nameList = nodeName.split(".");
	assert(nameList.size() == 2);

	auto projectNode = m_rootNode->FindScope(nameList.at(0));

	/*若未添加项目作用域*/
	if (projectNode==nullptr)
	{
		AddProjectScopeNode(nameList.at(0));
		projectNode = m_rootNode->FindScope(nameList.at(0));
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

