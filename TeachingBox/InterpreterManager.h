#ifndef _TEACHING_BOX_INTERPRETER_MANAGER_H_
#define _TEACHING_BOX_INTERPRETER_MANAGER_H_

#include "QObject"
#include "SingleTon.h"

class TAstNode;
class TInterpreterThread;
class QThread;

class InterpreterManager:public QObject
{
	Q_OBJECT

	friend SingleTon < InterpreterManager>;

public:
	static InterpreterManager* GetInstance();

private:
	InterpreterManager();
	InterpreterManager(const InterpreterManager&);
	InterpreterManager& operator=(const InterpreterManager&);
	~InterpreterManager();

public:
	bool AutoExecute();

	TAstNode* GetNode(const QString& program, int lineNumber);

	bool ManualExecute();

	bool StepExecute();
	void StopExecute();

	void ExecuteNextCommand();

private:
	TAstNode* GetProgramNode(const QString& program);
	TAstNode* GetNodeOnLineFromProgram(TAstNode* programNode, int lineNumber);

	bool LoadProject(const QString& project);

	bool SaveFile();
	void UpdateStartNode();

signals:
	void SignalStopExecute();
	void SignalStepExecute();
	void SignalAutoExecute();

	void SignalExecuteNextCommand();
private:
	TInterpreterThread* m_interpreterThread=nullptr;
	QThread* m_thread=nullptr;
};

#endif