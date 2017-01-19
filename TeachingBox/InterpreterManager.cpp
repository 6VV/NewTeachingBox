#include "stdafx.h"
#include "InterpreterManager.h"
#include "TAstNodeFactory.h"
#include "Context.h"
#include "TAstNode.h"
#include "TAstNodeProgram.h"
#include "TTokenWithValue.h"
#include "TInterpreterThread.h"
#include "QThread"
#include "CodeEditor.h"
#include "ProjectManager.h"
#include "CodeEditorManager.h"



InterpreterManager* InterpreterManager::GetInstance()
{
	return SingleTon<InterpreterManager>::GetInstance();
}

bool InterpreterManager::LoadProject(const QString& project)
{
	auto rootNode = TAstNodeFactory::CreateAstFromProject(project);
	if (rootNode->GetFirstChild()==nullptr)
	{
		return false;
	}
	Context::interpreterContext.SetRootNode(rootNode);
	return true;
}

bool InterpreterManager::AutoExecute()
{
	/*已经执行*/
	if (Context::interpreterContext.GetExecuteState()==InterpreterContext::EXECUTING)
	{
		return false;
	}

	if (!(SaveFile() && LoadProject(Context::projectContext.ProjectLoaded())))
	{
		return true;
	}
	UpdateStartNode();

	Context::interpreterContext.SetExecuteState(InterpreterContext::EXECUTING);
	Context::interpreterContext.IsAllowSendCommandData(true);
	emit SignalAutoExecute();

	return true;
}

bool InterpreterManager::StepExecute()
{
	/*已经执行*/
	if (Context::interpreterContext.GetExecuteState()==InterpreterContext::EXECUTING)
	{
		return false;
	}
	if (!(SaveFile() && LoadProject(Context::projectContext.ProjectLoaded())))
	{
		return true;
	}
	UpdateStartNode();

	Context::interpreterContext.SetExecuteState(InterpreterContext::EXECUTING);
	Context::interpreterContext.IsAllowSendCommandData(true);
	emit SignalStepExecute();

	return true;
}

void InterpreterManager::UpdateStartNode()
{
	auto program = Context::interpreterContext.GetProgramExecuting();
	Context::interpreterContext.SetNextNode(GetNodeOnLineFromProgram(GetProgramNode(program), Context::interpreterContext.GetPCLine()));
}

bool InterpreterManager::ManualExecute()
{
	return AutoExecute();
}

void InterpreterManager::StopExecute()
{
	Context::interpreterContext.SetExecuteState(InterpreterContext::STOP);

	emit SignalStopExecute();
}

void InterpreterManager::ExecuteNextCommand()
{
	emit SignalExecuteNextCommand();
}

bool InterpreterManager::SaveFile()
{
	if (Context::projectContext.ProgramOpened().size()==0)
	{
		return false;
	}
	ProjectManager projectManager;

	projectManager.SaveFile(Context::projectContext.ProgramOpened(), CodeEditorManager::GetInstance()->Text());

	return true;
}


TAstNode* InterpreterManager::GetProgramNode(const QString& program)
{
	auto rootNode = Context::interpreterContext.GetRootNode();
	if (rootNode == nullptr)
	{
		return nullptr;
	}

	auto childNode = rootNode->GetFirstChild();
	while (childNode!=nullptr)
	{
		auto nodeText = childNode->GetToken()->Name();

		if (nodeText==program)
		{
			return childNode.get();
		}

		childNode = childNode->GetSibling();
	}

	return nullptr;
}

TAstNode* InterpreterManager::GetNodeOnLineFromProgram(TAstNode* programNode, int lineNumber)
{
	std::shared_ptr<TAstNode> currentNode = programNode->GetFirstChild();
	if (currentNode == nullptr)
	{
		return nullptr;
	}
	else if (currentNode->GetToken()->LineNumber() == lineNumber)
	{
		return currentNode.get();
	}

	/*查询最后一个不大于起始行的子节点*/
	while (currentNode->GetSibling() != nullptr)
	{
		if (currentNode->GetSibling()->GetToken()->LineNumber() < lineNumber)
		{
			currentNode = currentNode->GetSibling();
		}
		else if (currentNode->GetSibling()->GetToken()->LineNumber() == lineNumber)
		{
			return currentNode->GetSibling().get();
		}
		else
		{
			break;
		}
	}

	return GetNodeOnLineFromProgram(currentNode.get(), lineNumber);
}

InterpreterManager::InterpreterManager()
	:m_interpreterThread(new TInterpreterThread())
	, m_thread(new QThread())
{
	m_interpreterThread->moveToThread(m_thread);

	connect(this, &InterpreterManager::SignalAutoExecute, m_interpreterThread, &TInterpreterThread::SlotAutoExecute);
	connect(this, &InterpreterManager::SignalStopExecute, m_interpreterThread, &TInterpreterThread::SlotStopExecute);
	connect(this, &InterpreterManager::SignalStepExecute, m_interpreterThread, &TInterpreterThread::SlotStepExecute);
	connect(this, &InterpreterManager::SignalExecuteNextCommand, m_interpreterThread, &TInterpreterThread::SlotExecuteNextCommand);

	m_thread->start();
}

InterpreterManager::~InterpreterManager()
{
	delete m_interpreterThread;
	delete m_thread;
}
