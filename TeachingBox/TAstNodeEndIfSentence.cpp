﻿#include "stdafx.h"
#include "TAstNodeEndIfSentence.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "Context.h"
#include "TAstNode.h"
#include "TToken.h"



TAstNodeEndIfSentence::TAstNodeEndIfSentence(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

TAstNodeEndIfSentence::~TAstNodeEndIfSentence()
{

}

const std::shared_ptr<TAstNode> TAstNodeEndIfSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->Type()!=TOKEN_TYPE::STURCTURE_END_IF)
	{
		throw TInterpreterException(TInterpreterException::IF_SENTENCE_SHOULD_END_WITH_ENDIF, token->LineNumber());
	}

	CheckEofEol(lexer);

	return std::shared_ptr<TAstNode>(new TAstNodeEndIfSentence(token));
}

const std::shared_ptr<TAstNode> TAstNodeEndIfSentence::GetAstNode(int lineNumber)
{
	return std::make_shared<TAstNodeEndIfSentence>(std::make_shared<TToken>(TOKEN_TYPE::STURCTURE_END_IF, lineNumber));

}

TAstNode::ValueReturned TAstNodeEndIfSentence::Execute() const
{
	Context::interpreterContext.SetNextNode(FindNextValidNode());

	return ValueReturned();
}

void TAstNodeEndIfSentence::ParseSemantic() const
{
}

TAstNode* TAstNodeEndIfSentence::FindNextValidNode() const
{
	auto desNode = m_parentNode;
	while (desNode->GetToken()->Type() != TOKEN_TYPE::STRUCTURE_IF)
	{
		desNode = desNode->GetParentNode();
	}

	return desNode->FindNextValidNode();
}
