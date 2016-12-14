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
	AddParameter<TPosition>(TPosition::TypeName(), 0);
	AddParameter<TDynamic>(TDynamic::TypeName(),1);
	AddParameter<TOverlap>(TOverlap::TypeName(), 2);

}

QString MacroWidgetMovl::MacroName()
{
	return "MOVL";
}
