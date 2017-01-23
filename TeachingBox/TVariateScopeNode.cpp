#include "stdafx.h"
#include "TVariateScopeNode.h"
#include "TVariate.h"



TVariateScopeNode::TVariateScopeNode(const QString& socpeName)
	:m_name(socpeName)
{

}

void TVariateScopeNode::AddChild(std::shared_ptr<TVariateScopeNode> node)
{
	m_childScopes[node->GetName()]=node;
	node->SetParentNode(this);
}

void TVariateScopeNode::AddOrUpdateVariate(std::shared_ptr<TVariate> variate)
{
	m_variates[variate->GetName()] = variate;
}

void TVariateScopeNode::DeleteVariate(const QString& name)
{
	m_variates.erase(m_variates.find(name));
}

QVector<std::shared_ptr<TVariateScopeNode>> TVariateScopeNode::GetChildScopes() const
{
	QVector<std::shared_ptr<TVariateScopeNode>> result{};
	for (auto scopeNode:m_childScopes)
	{
		result.append(scopeNode);
	}

	return std::move(result);
}

QVector<std::shared_ptr<TVariate>> TVariateScopeNode::GetVariates() const
{
	QVector<std::shared_ptr<TVariate>> vec{};
	for (auto variate:m_variates)
	{
		vec.push_back(variate);
	}

	return std::move(vec);
}

QString TVariateScopeNode::GetName() const
{
	return m_name;
}

TVariateScopeNode* TVariateScopeNode::GetParentNode() const
{
	return m_parentNode;
}

std::shared_ptr<TVariateScopeNode> TVariateScopeNode::FindChildScope(const QString& scopeName) const
{
	if (m_childScopes.size()==0)
	{
		return nullptr;
	}

	auto iter = m_childScopes.find(scopeName);
	if (iter!=m_childScopes.end())
	{
		return iter.value();
	}

	for (auto scope:m_childScopes)
	{
		auto result = scope->FindChildScope(scopeName);
		if (result != nullptr)
		{
			return result;
		}
	}

	return nullptr;
}

std::shared_ptr<TVariate> TVariateScopeNode::FindVariate(const QString& name) const
{
	auto iter = m_variates.find(name);
	if (iter==m_variates.end())
	{
		return nullptr;
	}

	return iter.value();
}

inline
void TVariateScopeNode::SetParentNode(TVariateScopeNode* parentNode)
{
	m_parentNode = parentNode;
}
