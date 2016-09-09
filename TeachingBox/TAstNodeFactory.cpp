#include "stdafx.h"
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
#include "TTokenWithValue.h"
#include "TAstNodeProgram.h"
#include "ProjectManager.h"
#include "Context.h"

const std::shared_ptr<TAstNode> TAstNodeFactory::CreateAst()
{
	std::shared_ptr<TAstNode> result(new TAstNodeRoot);
	ProjectManager projectManager;
	QString project = Context::projectContext.GetProjectLoaded();
	QList<QString> fileNames = projectManager.GetProjectFiles(project);
	for (const QString& var : fileNames)
	{
		QString fileText=projectManager.GetFileText(project,var);

		TLexer lexer(fileText);
		std::shared_ptr<TToken> token(new TTokenWithValue<QString>(TYPE::ID, 0, var));

		result->AddChild(TAstNodeProgram::GetAstNode(&lexer, token));
	}

	return result;
}

const std::shared_ptr<TAstNode> TAstNodeFactory::GetOneNode(TLexer* const lexer)
{
	auto token = lexer->PeekToken();

	switch (token->GetType())
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
	default:
	{
		return nullptr;
	}break;
	}
}

