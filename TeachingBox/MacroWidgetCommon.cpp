#include "stdafx.h"
#include "MacroWidgetCommon.h"
#include "MacroInfo.h"
#include "TPosition.h"
#include "TInteger.h"
#include "TDouble.h"
#include "TBool.h"
#include "TString.h"


MacroWidgetCommon::MacroWidgetCommon(const MacroInfo& macroInfo, const QString& macroText, QWidget* parent/*=0*/)
	:MacroWidgetParent(macroText, parent)
	, m_macroInfo(macroInfo)
{
	auto parameterTypes = macroInfo.GetParameterTypes();

	int i = 0;
	for (auto type:parameterTypes)
	{
		AddParameter(type, i++);
	}
}

QString MacroWidgetCommon::MacroName()
{
	return m_macroInfo.GetName();
}
