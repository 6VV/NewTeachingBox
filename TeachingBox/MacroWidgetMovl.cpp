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
	AddParameter(SymbolType::TYPE_POSITION,"p1");
	AddParameter(SymbolType::TYPE_DYNAMIC,"*");
	AddParameter(SymbolType::TYPE_OVERLAP, "*");
}

void MacroWidgetMovl::OnConfirm()
{

}

void MacroWidgetMovl::UpdateText()
{
	
}
