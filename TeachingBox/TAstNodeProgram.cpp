#include "stdafx.h"
#include "TAstNodeProgram.h"
#include "TAstNodeFactory.h"
#include "TLexer.h"
#include "Context.h"
#include "TInterpreterException.h"
#include "TToken.h"



TAstNodeProgram::TAstNodeProgram(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

TAstNodeProgram::~TAstNodeProgram()
{

}

const std::shared_ptr<TAstNode> TAstNodeProgram::GetAstNode(TLexer* const lexer, const std::shared_ptr<TToken> token)
{
	std::shared_ptr<TAstNode> result(new TAstNodeProgram(token));
	std::shared_ptr<TAstNode> node{};
	while (node = TAstNodeFactory::GetNode(lexer))
	{
		result->AddChild(node);
		SkipEol(lexer);
	}

	if (lexer->PeekToken()->Type() != TOKEN_TYPE::SEPARATOR_EOF)
	{
		throw TInterpreterException(TInterpreterException::UNKNOWN_SENTENCE, lexer->PeekToken()->LineNumber());
	}

	return result;
}

TAstNode::ValueReturned TAstNodeProgram::Execute() const
{
	Context::interpreterContext.SetNextNode(m_firstChild.get());

	return TAstNode::Execute();
}

void TAstNodeProgram::ParseSemantic() const
{
	Context::projectContext.ProgramLoading(m_token->Name());
	auto child = m_firstChild;

	while (child)
	{
		child->ParseSemantic();
		child = child->GetSibling();
	}
}
