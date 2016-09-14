#include "stdafx.h"
#include "TInterpreterThread.h"
#include "Context.h"
#include "TAstNode.h"


void TInterpreterThread::SlotStartExecute()
{
	auto nextNode = Context::interpreterContext.GetNextNode();

	while (nextNode != nullptr)
	{
		nextNode->Execute();
		nextNode = Context::interpreterContext.GetNextNode();
	}
}

void TInterpreterThread::SlotStepExecute()
{

}
