#ifndef _TEACHING_BOX_MACRO_WIDGTE_GOSUB_H_
#define _TEACHING_BOX_MACRO_WIDGTE_GOSUB_H_

#include "MacroWidgetParent.h"

class QComboBox;

class MacroWidgetGosub:public MacroWidgetParent
{
public:
	MacroWidgetGosub(const QString& macroText, QWidget* parent = nullptr);

	QComboBox* GetProgramComboBox();

	virtual ~MacroWidgetGosub();

private:
	virtual QString MacroName() override;
	virtual void SlotOnButtonConfirmClicked() override;

private:
	QComboBox* m_programComboBox;;
};

#endif