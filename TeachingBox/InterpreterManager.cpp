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



InterpreterManager* InterpreterManager::GetInstance()
{
	return SingleTon<InterpreterManager>::GetInstance();
}

void InterpreterManager::LoadProject(const QString& project)
{
	Context::interpreterContext.SetRootNode(TAstNodeFactory::CreateAstFromProject(project));
}

void InterpreterManager::AutoExecute()
{
	SaveFile();
	LoadProject(Context::projectContext.ProjectLoaded());
	UpdateStartNode();

	Context::interpreterContext.IsAllowExecute(true);
	Context::interpreterContext.IsAllowSendCommandData(true);
	emit SignalAutoExecute();
}

void InterpreterManager::StepExecute()
{
	SaveFile();
	LoadProject(Context::projectContext.ProjectLoaded());
	UpdateStartNode();

	Context::interpreterContext.IsAllowExecute(true);
	Context::interpreterContext.IsAllowSendCommandData(true);
	emit SignalStepExecute();
}

void InterpreterManager::UpdateStartNode()
{
	auto program = Context::projectContext.ProgramOpened();
	Context::interpreterContext.SetNextNode(GetNodeOnLineFromProgram(GetProgramNode(program), Context::interpreterContext.GetLineNumber()));
}

void InterpreterManager::ManualExecute()
{
	AutoExecute();
}

void InterpreterManager::StopExecute()
{
	Context::interpreterContext.IsAllowExecute(false);

	emit SignalStopExecute();
}

void InterpreterManager::ExecuteNextCommand()
{
	emit SignalExecuteNextCommand();
}

void InterpreterManager::SaveFile()
{
	ProjectManager projectManager;

	projectManager.SaveFile(Context::projectContext.ProgramOpened(), CodeEditor::GetInstance()->toPlainText());
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
			//dynamic_cast<TTokenWithValue<QString>*>(childNode->GetToken().get())->GetValue();

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

	connect(this, SIGNAL(SignalAutoExecute()), m_interpreterThread, SLOT(SlotAutoExecute()));
	connect(this, SIGNAL(SignalStopExecute()), m_interpreterThread, SLOT(SlotStopExecute()));
	connect(this, SIGNAL(SignalStepExecute()), m_interpreterThread, SLOT(SlotStepExecute()));
	connect(this, SIGNAL(SignalExecuteNextCommand()), m_interpreterThread, SLOT(SlotExecuteNextCommand()));

	m_thread->start();
}

InterpreterManager::~InterpreterManager()
{
	delete m_interpreterThread;
	delete m_thread;
}
