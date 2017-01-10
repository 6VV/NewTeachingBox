#include "stdafx.h"
#include "TAstNodeMacroCommon.h"
#include "TLexer.h"
#include "MacroManager.h"
#include "TToken.h"
#include "TInterpreterException.h"
#include "MacroInfo.h"
#include "TVariateManager.h"
#include "TVariate.h"
#include "Context.h"
#include "..\DataStream\DataStruct.h"
#include "TAstNodeProgram.h"
#include "..\DataStream\DataStream.h"
#include "RemoteManager.h"



TAstNodeMacroCommon::TAstNodeMacroCommon(const std::shared_ptr<TToken> token /*= nullptr*/)
	:TAstNode(token)
{

}

const std::shared_ptr<TAstNode> TAstNodeMacroCommon::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();

	std::shared_ptr<TAstNode> result(new TAstNodeMacroCommon(token));

	auto macroIter = MacroManager::GetInstance()->GetMacroMap()->find(token->Name());
	if (macroIter == MacroManager::GetInstance()->GetMacroMap()->end())
	{
		throw TInterpreterException(TInterpreterException::UNKNOWN_TOKEN, token->LineNumber());
	}

	int paraSize = macroIter->second->GetParameterTypes().size();

	for (int i = 0; i < paraSize-1;++i)
	{
		result->AddChild(GetParameter(lexer));
		CheckComma(lexer);
	}
	result->AddChild(GetParameter(lexer));
	CheckLineBreak(lexer);

	return result;
}

TAstNode::ValueReturned TAstNodeMacroCommon::Execute() const
{
	SendData();
	Context::interpreterContext.SetNextNode(GetSibling().get());
	return ValueReturned();
}

void TAstNodeMacroCommon::ParseSemantic() const
{
	auto macroIter = MacroManager::GetInstance()->GetMacroMap()->find(m_token->Name());
	auto types= macroIter->second->GetParameterTypes();

	auto currentChild = m_firstChild;
	for (auto type:types)
	{
		CheckParameterType(currentChild, type);
		currentChild = currentChild->GetSibling();
	}
}

const std::shared_ptr<TAstNode> TAstNodeMacroCommon::GetParameter(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->Type() != TOKEN_TYPE::ID)
	{
		throw TInterpreterException(TInterpreterException::WRONG_PARAMETER, token->LineNumber());
	}
	return std::shared_ptr<TAstNode>(new TAstNode(token));
}

void TAstNodeMacroCommon::CheckComma(TLexer* const lexer)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::SEPARATOR_COMMA)
	{
		lexer->UnGetToken();
		throw TInterpreterException(TInterpreterException::LOSE_COMMA, lexer->PeekToken()->LineNumber());
	}
}

void TAstNodeMacroCommon::CheckParameterType(std::shared_ptr<TAstNode> node, const QString& typeName) const
{
	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(GetScope(), node->GetToken()->Name());

	if (variate == nullptr)
	{
		throw TInterpreterException(TInterpreterException::UNKNOWN_VARIATE, node->GetToken()->LineNumber()
			, node->GetToken()->Name());
	}

	if (variate->GetTypeName() != typeName)
	{
		throw TInterpreterException(TInterpreterException::MOVL_SHOULD_WITH_POSITOIN_DYNAMIC_OVERLAP, node->GetToken()->LineNumber());
	}
}

void TAstNodeMacroCommon::SendData() const
{
	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
	attribute.m_ID = m_token->Type();
	attribute.m_LineNumber = m_token->LineNumber();
	attribute.m_programId = dynamic_cast<const TAstNodeProgram*>(GetProgramNode())->GetId();

	DataStream dataStream;
	dataStream << attribute;

	auto currentChild = m_firstChild;
	while (currentChild)
	{
		auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(GetScope(), currentChild->GetToken()->Name());
		if (!variate)
		{
			break;
		}
		variate->WriteValueToStream(*dataStream.GetOriginalDataStream());
		currentChild = currentChild->GetSibling();
	}
	attribute.m_length = dataStream.Length();
	dataStream.Seek(0);
	dataStream << attribute;
	dataStream.Seek(0);

	RemoteManager::GetInstance()->SendCommand(dataStream);
	Context::interpreterContext.IsAllowSendCommandData(false);
}
