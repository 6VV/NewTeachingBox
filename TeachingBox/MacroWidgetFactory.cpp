#include "stdafx.h"
#include "MacroWidgetFactory.h"
#include "Macro.h"
#include "QWidget"
#include "QString"
#include "MacroWidgetGosub.h"
#include "MacroManager.h"
#include "MacroWidgetCommon.h"

QWidget* MacroWidgetFactory::CreateMacroWidget(const QString& macro, QWidget* parent /*= nullptr*/)
{
	auto stringList = macro.split(" ");

	if (stringList.size()==0)
	{
		return nullptr;
	}

	auto macroName = stringList.at(0);

	if (macroName==Macro::MACRO_GOSUB)
	{
		return new MacroWidgetGosub(macro, parent);
	}
	else
	{
		auto iter = MacroManager::GetInstance()->GetMacroMap()->find(macroName);
		if (iter == MacroManager::GetInstance()->GetMacroMap()->end())
		{
			return nullptr;
		}
		/*若无参数*/
		if (iter->second->GetParameterTypes().size()==0)
		{
			return nullptr;
		}
		return new MacroWidgetCommon(*iter->second, macro, parent);
	}

	return nullptr;
}
