#include "stdafx.h"
#include "MacroWidgetCommon.h"
#include "MacroInfo.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"




MacroWidgetCommon::MacroWidgetCommon(const MacroInfo& macroInfo, QWidget* parent/*=0*/)
	:MacroWidgetParent(macroInfo.GetText(), parent)
	, m_macroInfo(macroInfo)
{
	auto parameterTypes = macroInfo.GetParameterTypes();

	int i = 0;
	for (auto type:parameterTypes)
	{
		if (type == TPosition::TypeName())
		{
			AddParameter<TPosition>(type, i);
		}
		else if (type == TDynamic::TypeName())
		{
			AddParameter<TDynamic>(type, i);
		}
		else if (type == TOverlap::TypeName())
		{
			AddParameter<TOverlap>(type, i);
		}

		++i;
	}
}

QString MacroWidgetCommon::MacroName()
{
	return m_macroInfo.GetName();
}
