﻿#include "stdafx.h"
#include "TAstNodeMovlSentence.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "TTokenWithValue.h"
#include "TVariateManager.h"
#include "Context.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"
#include "RemoteManager.h"
#include "TAstNodeProgram.h"
#include "..\DataStream\DataStream.h"

TAstNodeMovlSentence::TAstNodeMovlSentence(const std::shared_ptr<TToken> token /*= nullptr*/) :TAstNode(token)
{

}

TAstNodeMovlSentence::~TAstNodeMovlSentence()
{

}

const std::shared_ptr<TAstNode> TAstNodeMovlSentence::GetAstNode(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->Type()!=TOKEN_TYPE::MACRO_MOVL)
	{
		throw TInterpreterException(TInterpreterException::NOT_MOVL_SENTENCE, token->LineNumber());
	}
	std::shared_ptr<TAstNode> result(new TAstNodeMovlSentence(token));

	result->AddChild(GetParameter(lexer));
	CheckComma(lexer);
	result->AddChild(GetParameter(lexer));
	CheckComma(lexer);
	result->AddChild(GetParameter(lexer));
	CheckLineBreak(lexer);

	return result;
}

const std::shared_ptr<TAstNode> TAstNodeMovlSentence::GetParameter(TLexer* const lexer)
{
	auto token = lexer->GetToken();
	if (token->Type() != TOKEN_TYPE::ID)
	{
		throw TInterpreterException(TInterpreterException::MOVL_SHOULD_WITH_POSITOIN_DYNAMIC_OVERLAP, token->LineNumber());
	}
	return std::shared_ptr<TAstNode>(new TAstNode(token));
}

void TAstNodeMovlSentence::CheckComma(TLexer* const lexer)
{
	if (lexer->GetToken()->Type() != TOKEN_TYPE::SEPARATOR_COMMA)
	{
		lexer->UnGetToken();
		throw TInterpreterException(TInterpreterException::LOSE_COMMA, lexer->PeekToken()->LineNumber());
	}
}

TAstNode::ValueReturned TAstNodeMovlSentence::Execute() const
{
	SendMovlData();
	Context::interpreterContext.SetNextNode(GetSibling().get());
	return ValueReturned();
}

void TAstNodeMovlSentence::ParseSemantic() const
{
	CheckParameterType(m_firstChild, TPosition::TypeName());
	CheckParameterType(m_firstChild->GetSibling(), TDynamic::TypeName());
	CheckParameterType(m_firstChild->GetSibling()->GetSibling(), TOverlap::TypeName());
}

void TAstNodeMovlSentence::CheckParameterType(std::shared_ptr<TAstNode> node, const QString& typeName) const
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

void TAstNodeMovlSentence::SendMovlData() const
{
	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
	attribute.m_ID = CommandId::MOVL;
	attribute.m_LineNumber = m_token->LineNumber();
	attribute.m_programId = dynamic_cast<const TAstNodeProgram*>(GetProgramNode())->GetId();

	DataStream dataStream;
	dataStream << attribute;
	dataStream << GetMovlParameter();
	attribute.m_length = dataStream.Length();
	dataStream.Seek(0);
	dataStream << attribute;
	dataStream.Seek(0);

	RemoteManager::GetInstance()->SendCommand(dataStream);

	//char data[sizeof(tMovLParam)];
	//*(tMovLParam*)data = GetMovlParameter();
	//RemoteManager::GetInstance()->SendMovlCommand(data, sizeof(tMovLParam), m_token->LineNumber(),
	//	dynamic_cast<const TAstNodeProgram*>(GetProgramNode())->GetId());
}

tMovLParam TAstNodeMovlSentence::GetMovlParameter() const
{
	tMovLParam movlParam;

	std::shared_ptr<TAstNode> firstChild = this->GetFirstChild();
	tAxesAllPositions position = GetPosition(firstChild->GetToken()->Name());


	std::shared_ptr<TAstNode> secondChild = firstChild->GetSibling();
	tDynamicConstraint dynamic = GetDynamic(secondChild->GetToken()->Name());

	std::shared_ptr<TAstNode> thirdChild = secondChild->GetSibling();
	tOverlapConstraint overlap = GetOverlap(thirdChild->GetToken()->Name());

	movlParam.m_Destination = position;
	movlParam.m_Dynamic = dynamic;
	movlParam.m_Overlap = overlap;

	return movlParam;
}

tAxesAllPositions TAstNodeMovlSentence::GetPosition(const QString& name) const
{
	return std::static_pointer_cast < TPosition>(TVariateManager::GetInstance()
		->GetVariateSrollUp(GetScope(), name))->GetValue();
}

tDynamicConstraint TAstNodeMovlSentence::GetDynamic(const QString& name) const
{
	return std::static_pointer_cast<TDynamic>(TVariateManager::GetInstance()
		->GetVariateSrollUp(GetScope(), name))->GetValue();
}

tOverlapConstraint TAstNodeMovlSentence::GetOverlap(const QString& name) const
{
	return std::static_pointer_cast<TOverlap>(TVariateManager::GetInstance()
		->GetVariateSrollUp(GetScope(), name))->GetValue();
}
