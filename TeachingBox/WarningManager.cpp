#include "stdafx.h"
#include "WarningManager.h"
#include "QMessageBox"


WarningManager::WarningManager()
{

}

WarningManager::~WarningManager()
{

}

WarningManager* WarningManager::GetInstance()
{
	return SingleTon<WarningManager>::GetInstance();
}

void WarningManager::Warning(QWidget* widget, QString strText)
{
	QMessageBox::warning(widget, "Warning", strText);
}

void WarningManager::Warning(QWidget* widget, WarningCode warningCode)
{
	switch (warningCode)
	{
	case NameIsEmpty:
	{
		Warning(widget, "Name Is Empty");
	}break;
	case PleaseSelectScope:
	{
		Warning(widget, "Please Select Scope");
	}break;
	case PleaseSelectVariable:
	{
		Warning(widget, "Please Select Variable");
	}break;
	case AlreadyExitVariable:
	{
		Warning(widget, "Already Exit This Variable");
	}break;
	case AlreadyLoadOtherProject:
	{
		Warning(widget, "Already Load Other Project");
	}break;
	case ForbidDelete:
	{
		Warning(widget, "Forbid Delete");
	}break;
	case NotFindVariable:
	{
		Warning(widget, "Not Find Variable");
	}break;
	case WrongName:
	{
		Warning(widget, "Wrong Name");
	}break;
	case NameIsTooLong:
	{
		Warning(widget, "Name Is Too Long");
	}break;
	default:
		break;
	}
}
