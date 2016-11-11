#include "stdafx.h"
#include "MacroWidgetMovc.h"
#include "TPosition.h"



MacroWidgetMovc::MacroWidgetMovc(const QString& macroText, QWidget* parent /*= nullptr*/)
	:MacroWidgetParent(macroText,parent)
{
	AddParameter<TPosition>(SymbolType::TYPE_POSITION, 0);
	AddParameter<TPosition>(SymbolType::TYPE_POSITION, 1);
	AddParameter<TPosition>(SymbolType::TYPE_DYNAMIC, 2);
	AddParameter<TPosition>(SymbolType::TYPE_OVERLAP, 3);
}

MacroWidgetMovc::~MacroWidgetMovc()
{

}


QString MacroWidgetMovc::MacroName()
{
	return "MOVC";
}
