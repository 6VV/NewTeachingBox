#include "stdafx.h"
#include "TAstNodeElseSentence.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "TAstNodeEndIfSentence.h"
#include "Context.h"
#include "TToken.h"



TAstNodeElseSentence::TAstNodeElseSentence(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

TAstNodeElseSentence::~TAstNodeElseSentence()
{

}

const std::shared_ptr<TAstNode> TAstNodeElseSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();

	if (token->Type()!=TOKEN_TYPE::STURCTURE_ELSE)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
	}
	
	CheckLeftBrace(lexer);
	CheckLineBreak(lexer);

	std::shared_ptr<TAstNode> result(new TAstNodeElseSentence(token));

	AddSentenceNodes(lexer, result);

	CheckRightBrace(lexer);
	CheckEofEol(lexer);

	result->AddChild(TAstNodeEndIfSentence::GetAstNode(result->GetEndChild()->GetToken()->LineNumber()));

	//result->AddChild(std::shared_ptr<TAstNode>(new TAstNodeEndIfSentence(
	//	std::shared_ptr<TToken>(new TToken(TOKEN_TYPE::STURCTURE_END_IF, result->GetEndChild()->GetToken()->LineNumber())))));

	return result;
}

TAstNode::ValueReturned TAstNodeElseSentence::Execute() const
{
	Context::interpreterContext.SetNextNode(m_firstChild.get());

	return ValueReturned();
}

void TAstNodeElseSentence::ParseSemantic() const
{
	auto child = m_firstChild;

	while (child)
	{
		child->ParseSemantic();
		child = child->GetSibling();
	}
}
