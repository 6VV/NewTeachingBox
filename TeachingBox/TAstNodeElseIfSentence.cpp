#include "stdafx.h"
#include "TAstNodeElseIfSentence.h"
#include "TLexer.h"
#include "TToken.h"
#include "TInterpreterException.h"
#include "TAstNodeOperator.h"
#include "TAstNodeEndIfSentence.h"
#include "Context.h"
#include "TSymbol.h"



TAstNodeElseIfSentence::TAstNodeElseIfSentence(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

TAstNodeElseIfSentence::~TAstNodeElseIfSentence()
{

}

const std::shared_ptr<TAstNode> TAstNodeElseIfSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();

	if (token->Type()!=TOKEN_TYPE::STRUCTURE_ELSE_IF)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
	}

	std::shared_ptr<TAstNode> result(new TAstNodeElseIfSentence(token));
	result->AddChild(TAstNodeOperator::GetAstNode(lexer));
	CheckLineBreak(lexer);

	AddSentenceNodes(lexer, result);

	result->AddChild(std::shared_ptr<TAstNode>(new TAstNodeEndIfSentence(
		std::shared_ptr<TToken>(new TToken(TOKEN_TYPE::STURCTURE_END_IF, result->GetEndChild()->GetToken()->LineNumber())))));

	return result;
}

TAstNode::ValueReturned TAstNodeElseIfSentence::Execute() const
{
	if (m_firstChild->Execute().value)
	{
		Context::interpreterContext.SetNextNode(m_firstChild->GetSibling().get());
	}
	else
	{
		Context::interpreterContext.SetNextNode(m_siblingNode.get());
	}

	return ValueReturned();
}

void TAstNodeElseIfSentence::ParseSemantic() const
{
	if (TAstNodeOperator::GetSymbolType(m_firstChild) != TSymbol::TYPE_BOOL)
	{
		throw TInterpreterException(TInterpreterException::IF_SENTENCE_SHOULD_WITH_BOOL, m_token->LineNumber());
	}

	auto child = m_firstChild->GetSibling();

	while (child)
	{
		child->ParseSemantic();
		child = child->GetSibling();
	}
}
