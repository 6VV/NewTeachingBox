#include "stdafx.h"
#include "TAstNodeEof.h"
#include "TLexer.h"
#include "TToken.h"
#include "InterpreterManager.h"
#include "Context.h"



TAstNodeEof::TAstNodeEof(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

const std::shared_ptr<TAstNode> TAstNodeEof::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();

	return std::make_shared<TAstNodeEof>(std::make_shared<TToken>(TTokenType::SEPARATOR_EOF, token->LineNumber()));
}

TAstNode* TAstNodeEof::FindNextValidNode() const
{
	auto funInfo = Context::interpreterContext.PopFunctionInfo();
	if (funInfo.functionName=="")
	{
		Context::interpreterContext.ClearFunctionInfo();
		return nullptr;
	}
	return InterpreterManager::GetInstance()->GetNode(funInfo.functionName, funInfo.lineNumber);
}

TAstNode::ValueReturned TAstNodeEof::Execute() const
{
	Context::interpreterContext.SetNextNode(FindNextValidNode());

	return TAstNode::Execute();
}

void TAstNodeEof::ParseSemantic() const
{
	return;
}
