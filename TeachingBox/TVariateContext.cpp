#include "stdafx.h"
#include "TVariateContext.h"
#include "TVariateScopeNode.h"
#include "ProjectContext.h"
#include "TVariateFactory.h"
#include "TVariate.h"
#include <assert.h>



TVariateContext::TVariateContext()
	:m_rootNode(new TVariateScopeNode(ProjectContext::ScopeSystem()))
{
	auto cooperateNode = std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(ProjectContext::ScopeCooperate()));
	cooperateNode->AddChild(std::shared_ptr<TVariateScopeNode>(new TVariateScopeNode(ProjectContext::ScopeGlobal())));

	m_rootNode->AddChild(cooperateNode);
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
		scopeNode->AddVariate(variate);
	}
	else
	{
		/*若为项目作用域*/
		if (variateScope.split(".").size()<=1)
		{
			AddProjectScopeNode(variateScope);
		}
		/*若为程序作用域*/
		else
		{
			AddProgramScopeNode(variateScope);
		}
		
		m_rootNode->FindScope(variateScope)->AddVariate(variate);
	}
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

