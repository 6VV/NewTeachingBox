#include "stdafx.h"
#include "TVariateContextNode.h"
#include "TVariate.h"



void TVariateContextNode::AddChild(std::shared_ptr<TVariateContextNode> node)
{
	m_childScopes.push_back(node);
}

void TVariateContextNode::AddVariate(std::shared_ptr<TVariate> variate)
{
	m_variates[variate->GetName()] = variate;
}
