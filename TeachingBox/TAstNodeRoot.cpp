#include "stdafx.h"
#include "TAstNodeRoot.h"
#include "TSymbol.h"
#include "Context.h"



TAstNodeRoot::TAstNodeRoot(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

TAstNodeRoot::~TAstNodeRoot()
{

}

TAstNode::ValueReturned TAstNodeRoot::Execute() const
{
	Context::interpreterContext.SetNextNode(m_firstChild.get());

	return ValueReturned{ 0, TSymbol::TYPE_VOID };
}

void TAstNodeRoot::ParseSemantic() const
{
	auto child = m_firstChild;

	while (child)
	{
		child->ParseSemantic();
		child = child->GetSibling();
	}
}
