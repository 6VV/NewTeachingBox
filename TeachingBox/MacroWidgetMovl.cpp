#include "stdafx.h"
#include "MacroWidgetMovl.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"


MacroWidgetMovl::MacroWidgetMovl(const QString& macroText, QWidget* parent/*=nullptr*/)
	:MacroWidgetParent(macroText,parent)
{
	Init();

}

MacroWidgetMovl::~MacroWidgetMovl()
{
}

void MacroWidgetMovl::Init()
{
	AddParameter<TPosition>(SymbolType::TYPE_POSITION, 0);
	AddParameter<TDynamic>(SymbolType::TYPE_DYNAMIC,1);
	AddParameter<TOverlap>(SymbolType::TYPE_OVERLAP, 2);

}

QString MacroWidgetMovl::MacroName()
{
	return "MOVL";
}
