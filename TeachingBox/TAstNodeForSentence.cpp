﻿#include "stdafx.h"
#include "TAstNodeForSentence.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "TAstNodeFactory.h"
#include "TAstNodeAssignSentence.h"
#include "TAstNodeOperator.h"
#include "TAstNodeNextSentence.h"
#include "TVariateManager.h"
#include "Context.h"
#include "TTokenWithValue.h"
#include "TInteger.h"
#include "TDouble.h"



TAstNodeForSentence::TAstNodeForSentence(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

TAstNodeForSentence::~TAstNodeForSentence()
{

}

TAstNode::ValueReturned TAstNodeForSentence::Execute() const
{
	auto secondChild = m_firstChild->GetSibling();
	auto thirdChild = secondChild->GetSibling();

	auto firstValue = m_firstChild->Execute();
	auto sencondValue = secondChild->Execute();
	//auto thirdValue = thirdChild->Execute();

	auto scope = GetScope();
	auto name = m_firstChild->GetFirstChild()->GetToken()->Name();
	auto type = TVariateManager::GetInstance()->GetVariateSrollUp(scope, name)->GetType();

	UpdateValue(type, scope, name, firstValue.value);
	
	if (GetValue(type, scope, name)<sencondValue.value)
	{
		Context::interpreterContext.SetNextNode(thirdChild->GetSibling().get());
	}
	else
	{
		Context::interpreterContext.SetNextNode(FindNextValidNode());
	}

	return ValueReturned{ 0, SYMBOL_TYPE::TYPE_VOID };
}

void TAstNodeForSentence::UpdateValue(SYMBOL_TYPE type, const QString& scope, const QString& name, double value)
{
	if (type == SYMBOL_TYPE::TYPE_INTERGER)
	{
		TVariateManager::GetInstance()->UpdateInMapScollUp(std::shared_ptr<TInteger>(new TInteger({scope, name}, static_cast<int>(value))));
	}
	else
	{
		TVariateManager::GetInstance()->UpdateInMapScollUp(std::shared_ptr<TDouble>(new TDouble({ scope, name }, value)));
	}
}

double TAstNodeForSentence::GetValue(SYMBOL_TYPE type, const QString& scope, const QString& name)
{
	if (type == SYMBOL_TYPE::TYPE_INTERGER)
	{
		return std::static_pointer_cast<TInteger>(TVariateManager::GetInstance()->GetVariateSrollUp(scope, name))->GetValue();
	}
	else
	{
		return std::static_pointer_cast<TDouble>(TVariateManager::GetInstance()->GetVariateSrollUp(scope, name))->GetValue();
	}
}

const std::shared_ptr<TAstNode> TAstNodeForSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->Type()!=TOKEN_TYPE::STRUCTURE_FOR)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
	}

	std::shared_ptr<TAstNode> result(new TAstNodeForSentence(token));

	result->AddChild(TAstNodeAssignSentence::GetAssignException(lexer));

	AddToNode(lexer, token, result);
	AddStepNode(lexer, token, result);

	CheckLeftBrace(lexer);
	CheckLineBreak(lexer);

	AddSentenceNodes(lexer, result);

	int line = lexer->PeekToken()->LineNumber();
	CheckRightBrace(lexer);
	CheckEofEol(lexer);

	result->AddChild(TAstNodeNextSentence::GetAstNode(std::make_shared<TToken>(TOKEN_TYPE::STRUCTURE_NEXT, line)));

	return result;
}

void TAstNodeForSentence::AddStepNode(TLexer* const lexer, std::shared_ptr<TToken> token, std::shared_ptr<TAstNode> result)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::STRUCTURE_STEP)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
	}

	result->AddChild(TAstNodeOperator::GetAstNode(lexer));
}

void TAstNodeForSentence::AddToNode(TLexer* const lexer, std::shared_ptr<TToken> token, std::shared_ptr<TAstNode> result)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::STRUCTURE_TO)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
	}

	result->AddChild(TAstNodeOperator::GetAstNode(lexer));
}

void TAstNodeForSentence::ParseSemantic() const
{
	auto type1 = TAstNodeOperator::GetSymbolType(m_firstChild->GetFirstChild()->GetSibling());
	auto type2 = TAstNodeOperator::GetSymbolType(m_firstChild->GetSibling());
	auto type3 = TAstNodeOperator::GetSymbolType(m_firstChild->GetSibling()->GetSibling());

	if ((type1 != SYMBOL_TYPE::TYPE_INTERGER && type1 != SYMBOL_TYPE::TYPE_DOUBLE)
		|| (type2 != SYMBOL_TYPE::TYPE_INTERGER && type2 != SYMBOL_TYPE::TYPE_DOUBLE)
		|| (type3 != SYMBOL_TYPE::TYPE_INTERGER && type3 != SYMBOL_TYPE::TYPE_DOUBLE))
	{
		throw TInterpreterException(TInterpreterException::FOR_SENTENCE_SHOULD_USE_INTERGER_OR_DOUBLE, m_firstChild->GetToken()->LineNumber());
	}

	auto child = m_firstChild->GetSibling()->GetSibling()->GetSibling();
	while (child)
	{
		child->ParseSemantic();
		child = child->GetSibling();
	}
}
