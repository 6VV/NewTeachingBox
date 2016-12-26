﻿#include "stdafx.h"
#include "TAstNodeFactory.h"
#include "TLexer.h"
#include "TInterpreterException.h"
#include "TAstNode.h"
#include "TAstNodeOperator.h"
#include "TAstNodeAssignSentence.h"
#include "TAstNodeForSentence.h"
#include "TAstNodeRoot.h"
#include "TAstNodeIfSentence.h"
#include "TAstNodeMovlSentence.h"
#include "TAstNodeProgram.h"
#include "ProjectManager.h"
#include "Context.h"
#include "TAstNodeGosubSentence.h"
#include "TToken.h"
#include "TVariateContext.h"

const std::shared_ptr<TAstNode> TAstNodeFactory::CreateAstFromProject(const QString& project)
{
	std::shared_ptr<TAstNode> result(new TAstNodeRoot);
	ProjectManager projectManager;
	QList<QString> fileNames = projectManager.GetProjectFiles(project);

	int programId = 0;
	for (const QString& var : fileNames)
	{
		Context::projectContext.ProgramLoading(var);

		QString fileText = projectManager.GetFileText(project, var.split(".").at(1));

		TLexer lexer(fileText);
		lexer.Parse();
		std::shared_ptr<TToken> token(new TToken(TYPE::ID, 0, var));

		auto program = TAstNodeProgram::GetAstNode(&lexer, token);
		std::dynamic_pointer_cast<TAstNodeProgram>(program)->SetId(programId++);
		result->AddChild(program);
	}

	result->ParseSemantic();

	return result;
}

const std::shared_ptr<TAstNode> TAstNodeFactory::GetNode(TLexer* const lexer)
{
	auto token = lexer->PeekToken();

	switch (token->Type())
	{
	case TYPE::ID:
	{
		return TAstNodeAssignSentence::GetAstNode(lexer);
	}break;
	case TYPE::STRUCTURE_FOR:
	{
		return TAstNodeForSentence::GetAstNode(lexer);
	}break;
	case TYPE::STRUCTURE_IF:
	{
		return TAstNodeIfSentence::GetAstNode(lexer);
	}break;
	case TYPE::MACRO_MOVL:
	{
		return TAstNodeMovlSentence::GetAstNode(lexer);
	}break;
	case TYPE::STURCTURE_GOSUB:{
		return TAstNodeGosubSentence::GetAstNode(lexer);
	}break;
	default:
	{
		return nullptr;
	}break;
	}
}

