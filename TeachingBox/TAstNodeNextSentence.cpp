#include "stdafx.h"
#include "TAstNodeNextSentence.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "Context.h"
#include "TTokenWithValue.h"
#include "TVariateManager.h"
#include "TAstNodeForSentence.h"
#include "TVariate.h"


TAstNodeNextSentence::TAstNodeNextSentence(const std::shared_ptr<TToken> token /*= nullptr*/) :TAstNode(token)
{

}

TAstNodeNextSentence::~TAstNodeNextSentence()
{

}

TAstNode::ValueReturned TAstNodeNextSentence::Execute() const
{
	auto thirdChild = m_parentNode->GetFirstChild()->GetSibling()->GetSibling();

	auto scope = GetScope();
	auto name = m_parentNode->GetFirstChild()->GetFirstChild()->GetToken()->Name();
	auto type = TVariateManager::GetInstance()->GetVariateSrollUp(scope, name)->GetType();

	auto newValue = TAstNodeForSentence::GetValue(type, scope, name) + thirdChild->Execute().value;

	TAstNodeForSentence::UpdateValue(type, scope, name, newValue);

	auto sencondValue = m_parentNode->GetFirstChild()->GetSibling()->Execute();
	if (newValue<sencondValue.value)
	{
		Context::interpreterContext.SetNextNode(thirdChild->GetSibling().get());
	}
	else
	{
		Context::interpreterContext.SetNextNode(FindNextValidNode());
	}

	return ValueReturned{};
}

const std::shared_ptr<TAstNode> TAstNodeNextSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->Type()!=TOKEN_TYPE::STRUCTURE_NEXT)
	{
		throw TInterpreterException(TInterpreterException::FOR_SENTENCE_SHOULD_END_WITH_NEXT, token->LineNumber());
	}

	std::shared_ptr<TAstNode> result(new TAstNodeNextSentence(token));

	CheckEofEol(lexer);

	return result;
}

void TAstNodeNextSentence::ParseSemantic() const
{
}
