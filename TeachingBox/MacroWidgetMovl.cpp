#include "stdafx.h"
#include "MacroWidgetMovl.h"
#include "QBoxLayout"
#include "QLabel"


MacroWidgetMovl::MacroWidgetMovl(const QString& macroText, QWidget* parent/*=nullptr*/)
	:MacroWidgetParent(macroText,parent)
{
	Init();

	UpdateText();
}

MacroWidgetMovl::~MacroWidgetMovl()
{
}

void MacroWidgetMovl::Init()
{
	AddPosition("*");
	AddPosition("*");
}

void MacroWidgetMovl::OnConfirm()
{

}

void MacroWidgetMovl::UpdateText()
{
	
}
