#include "stdafx.h"
#include "TAstNodeEof.h"
#include "TLexer.h"
#include "TToken.h"
#include "InterpreterManager.h"
#include "Context.h"
#include "RemoteManager.h"
#include "TAstNodeProgram.h"



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
	auto nextNode = FindNextValidNode();
	if (nextNode==nullptr)
	{
		tTeachCmdAttribute attribute;
		attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
		attribute.m_ID = CommandId::END;
		attribute.m_LineNumber = m_token->LineNumber();
		attribute.m_programId = dynamic_cast<const TAstNodeProgram*>(GetProgramNode())->GetId();

		DataStream dataStream;
		dataStream << attribute;
		dataStream.Seek(0);

		RemoteManager::GetInstance()->SendCommand(dataStream);
	}
	Context::interpreterContext.SetNextNode(nextNode);

	return TAstNode::Execute();
}

void TAstNodeEof::ParseSemantic() const
{
	return;
}
