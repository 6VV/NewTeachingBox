#include "stdafx.h"
#include "TAstNodeAssignSentence.h"
#include "TToken.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "TAstNodeOperator.h"
#include "TVariateManager.h"
#include "TTokenWithValue.h"
#include "TInteger.h"
#include "TDouble.h"
#include "TBool.h"
#include "TString.h"
#include "Context.h"



TAstNodeAssignSentence::TAstNodeAssignSentence(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{
}

TAstNodeAssignSentence::~TAstNodeAssignSentence()
{
}

TAstNode::ValueReturned TAstNodeAssignSentence::Execute() const
{

	auto var = TVariateManager::GetInstance()->GetVariateSrollUp(GetScope(), m_firstChild->GetToken()->Name()
		/*static_cast<TTokenWithValue<QString>*>(m_firstChild->GetToken().get())->GetValue()*/);

	auto value = m_firstChild->GetSibling()->Execute();

	ValueReturned result(value);

	switch (var->GetType())
	{
	case TSymbol::TYPE_INTERGER:
	{
		TVariateManager::GetInstance()->UpdateInMapScollUp(var->GetScope(), var->GetName(), TInteger(var->GetScope(), var->GetName(), static_cast<int>(value.value)));
		result.type = TSymbol::TYPE_INTERGER;
	}break;
	case TSymbol::TYPE_DOUBLE:
	{
		TVariateManager::GetInstance()->UpdateInMapScollUp(var->GetScope(), var->GetName(), TDouble(var->GetScope(), var->GetName(), value.value));
		result.type = TSymbol::TYPE_DOUBLE;
	}break;
	case TSymbol::TYPE_BOOL:
	{
		TVariateManager::GetInstance()->UpdateInMapScollUp(var->GetScope(), var->GetName(), TBool(var->GetScope(), var->GetName(), value.value != 0));
		result.type = TSymbol::TYPE_BOOL;
	}break;
	default:
		break;
	}

	Context::interpreterContext.SetNextNode(FindNextValidNode());

	qDebug() << result.value;

	return result;
}

const std::shared_ptr<TAstNode> TAstNodeAssignSentence::GetAstNode(TLexer* const lexer)
{
	auto assignNode = GetAssignException(lexer);

	CheckEofEol(lexer);

	return assignNode;
}


const std::shared_ptr<TAstNode> TAstNodeAssignSentence::GetAssignException(TLexer* const lexer)
{
	auto firstToken = lexer->GetToken();

	if (firstToken->Type() != TOKEN_TYPE::ID)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, firstToken->LineNumber());
	}

	std::shared_ptr<TAstNode> firstChild(new TAstNodeOperator(firstToken));

	auto assignToken = lexer->GetToken();
	if (assignToken->Type() != TOKEN_TYPE::OPERATOR_ASSIGN)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, assignToken->LineNumber());
	}

	std::shared_ptr<TAstNode> assignNode(new TAstNodeAssignSentence(assignToken));

	assignNode->AddChild(firstChild);
	assignNode->AddChild(TAstNodeOperator::GetAstNode(lexer));

	return assignNode;
}

void TAstNodeAssignSentence::ParseSemantic() const
{
	auto var = TVariateManager::GetInstance()->GetVariateSrollUp(GetScope(), m_firstChild->GetToken()->Name()
		/*static_cast<TTokenWithValue<QString>*>(m_firstChild->GetToken().get())->GetValue()*/);

	if (!var)
	{
		throw TInterpreterException(TInterpreterException::NOT_FIND_VARIATE, m_token->LineNumber(), m_firstChild->GetToken()->Name()
			/*static_cast<TTokenWithValue<QString>*>(m_firstChild->GetToken().get())->GetValue()*/);
	}

	auto type1 = var->GetType();
	auto type2 = TAstNodeOperator::GetSymbolType(m_firstChild->GetSibling());

	if (type1!=type2)
	{
		if ((type1!=TSymbol::TYPE_INTERGER && type1!=TSymbol::TYPE_DOUBLE)
			|| (type2 != TSymbol::TYPE_INTERGER && type2 != TSymbol::TYPE_DOUBLE))
		{
			throw TInterpreterException(TInterpreterException::TYPE_NOT_MATCH, m_token->LineNumber());
		}
	}
}
