#include "stdafx.h"
#include "TAstNodeGosubSentence.h"
#include "TLexer.h"
#include "TToken.h"
#include "TInterpreterException.h"
#include "TTokenWithValue.h"
#include "Context.h"



TAstNodeGosubSentence::TAstNodeGosubSentence(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

const std::shared_ptr<TAstNode> TAstNodeGosubSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->GetType() != TOKEN_TYPE::STURCTURE_GOSUB)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->GetLineNumber());
	}
	std::shared_ptr<TAstNode> result(new TAstNodeGosubSentence(token));

	auto childToken = lexer->GetToken();
	if (childToken->GetType()!=TOKEN_TYPE::ID)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->GetLineNumber());
	}

	result->AddChild(std::shared_ptr<TAstNode>(new TAstNode(childToken)));
	CheckLineBreak(lexer);

	return result;
}

TAstNode::ValueReturned TAstNodeGosubSentence::Execute() const
{
	auto desProgramName = GetDestinationProgramNode();
	auto programNode = Context::interpreterContext.GetRootNode()->GetFirstChild();
	while (programNode!=nullptr)
	{
		if (dynamic_cast<TTokenWithValue<QString>*>(programNode->GetToken().get())->GetValue() == desProgramName)
		{
			break;
		}
		programNode = programNode->GetSibling();
	}

	if (programNode==nullptr)
	{
		throw TInterpreterException(TInterpreterException::NOT_PROGRAM_NAME, m_token->GetLineNumber(),desProgramName);
	}

	Context::interpreterContext.SetNextNode(programNode.get());

	return TAstNode::Execute();
}

void TAstNodeGosubSentence::ParseSemantic() const
{
	auto programName = GetDestinationProgramNode();


	auto programs = Context::projectContext.GetPrograms();

	if (!programs.contains(programName))
	{
		throw TInterpreterException(TInterpreterException::NOT_PROGRAM_NAME, m_token->GetLineNumber());
	}
}

inline
QString TAstNodeGosubSentence::GetDestinationProgramNode() const
{
	return Context::projectContext.GetProjectLoaded() + "." + dynamic_cast<TTokenWithValue<QString>*>(m_firstChild->GetToken().get())->GetValue();
}
