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
	if (token->Type() != TOKEN_TYPE::STURCTURE_GOSUB)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
	}
	std::shared_ptr<TAstNode> result(new TAstNodeGosubSentence(token));

	auto childToken = lexer->GetToken();
	if (childToken->Type()!=TOKEN_TYPE::ID)
	{
		throw TInterpreterException(TInterpreterException::WRONG_GRAMMAR, token->LineNumber());
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
		if (programNode->GetToken()->Name()== desProgramName)
		{
			break;
		}
		programNode = programNode->GetSibling();
	}

	if (programNode==nullptr)
	{
		throw TInterpreterException(TInterpreterException::NOT_PROGRAM_NAME, m_token->LineNumber(),desProgramName);
	}

	Context::interpreterContext.PushFunctionInfo({GetProgramNode()->GetToken()->Name(),GetToken()->LineNumber()+1});

	Context::interpreterContext.SetNextNode(programNode.get());

	return TAstNode::Execute();
}

void TAstNodeGosubSentence::ParseSemantic() const
{
	auto programName = GetDestinationProgramNode();


	auto programs = Context::projectContext.Programs();

	if (!programs.contains(programName))
	{
		throw TInterpreterException(TInterpreterException::NOT_PROGRAM_NAME, m_token->LineNumber());
	}
}

inline
QString TAstNodeGosubSentence::GetDestinationProgramNode() const
{
	return Context::projectContext.ProjectLoaded() + "." + m_firstChild->GetToken()->Name();
		//dynamic_cast<TTokenWithValue<QString>*>(m_firstChild->GetToken().get())->GetValue();
}
