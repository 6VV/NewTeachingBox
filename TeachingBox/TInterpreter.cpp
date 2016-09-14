#include "stdafx.h"
#include "TInterpreter.h"
//#include "TLexer.h"
//#include "Context.h"
//#include "TAstNodeFactory.h"
//#include "TAstNode.h"
//#include "CodeEditor.h"
//#include <memory>
//
//void TInterpreter::ExecuteAll(int lineNum)
//{
//	Context::interpreterContext.IsExecuting(true);
//	InitContext(lineNum);
//
//	TAstNode* nextNode = nullptr;
//	while ((nextNode = Context::interpreterContext.GetNextNode()) != nullptr && Context::interpreterContext.IsExecuting())
//	{
//		nextNode->Execute();
//	}
//
//	StopExecute();
//}
//
//void TInterpreter::ExecuteOneLine(int lineNum)
//{
//	//InitContext(lineNum);
//	//TAstNode* nextNode = TContext::GetNextNode();
//
//	//if (nextNode!=nullptr)
//	//{
//	//	nextNode->Execute();
//	//}
//	//CCodeEditor::GetInstance()->HighlightPCLine(TContext::GetNextNode()->GetToken()->GetLineNumber());
//}
//
//void TInterpreter::StopExecute()
//{
//	//TContext::SetExecuteState(false);
//	//CTcpManager::GetInstance()->SendData(CTcpSpecialCommand::CommandStopExecute());
//}
//
//void TInterpreter::Parse(const QString& text)
//{
//	//auto rootNode = TAstNodeFactory::CreateAst();
//	//rootNode->ParseSemantic();
//
//	//TContext::SetRootNode(rootNode);
//	//TContext::SetNextNode(rootNode.get());
//}
//
//TAstNode* TInterpreter::FindStartNode(std::shared_ptr<TAstNode> rootNode,int lineNumber)
//{
//	auto currentNode = rootNode->GetFirstChild();
//	if (currentNode == nullptr)
//	{
//		return nullptr;
//	}
//	else if (currentNode->GetToken()->GetLineNumber() == lineNumber)
//	{
//		return currentNode.get();
//	}
//
//	/*查询最后一个不大于起始行的子节点*/
//	while (currentNode->GetSibling() != nullptr)
//	{
//		if (currentNode->GetSibling()->GetToken()->GetLineNumber() < lineNumber)
//		{
//			currentNode = currentNode->GetSibling();
//		}
//		else if (currentNode->GetSibling()->GetToken()->GetLineNumber() == lineNumber)
//		{
//			return currentNode->GetSibling().get();
//		}
//		else
//		{
//			break;
//		}
//	}
//
//	return FindStartNode(currentNode, lineNumber);
//}
//
//void TInterpreter::InitContext(int lineNum)
//{
//	Context::interpreterContext.SetNextNode(FindStartNode(Context::interpreterContext.GetRootNode(), lineNum));
//
//	TAstNode* node = Context::interpreterContext.GetNextNode();
//	while (node->GetParentNode()->GetParentNode())
//	{
//		node = node->GetParentNode();
//	}
//
//	Context::interpreterContext.SetCurrentProgramNode(node);
//}
//

