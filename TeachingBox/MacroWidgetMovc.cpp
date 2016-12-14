#include "stdafx.h"
#include "MacroWidgetMovc.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"



MacroWidgetMovc::MacroWidgetMovc(const QString& macroText, QWidget* parent /*= nullptr*/)
	:MacroWidgetParent(macroText,parent)
{
	AddParameter<TPosition>(TPosition::TypeName(), 0);
	AddParameter<TPosition>(TPosition::TypeName(), 1);
	AddParameter<TPosition>(TDynamic::TypeName(), 2);
	AddParameter<TPosition>(TOverlap::TypeName(), 3);
}

MacroWidgetMovc::~MacroWidgetMovc()
{

}


QString MacroWidgetMovc::MacroName()
{
	return "MOVC";
}
