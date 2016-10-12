#ifndef _TEACHING_BOX_MACRO_PARENT_H_
#define _TEACHING_BOX_MACRO_PARENT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroParent.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2016/10/11
//  Description:	命令控件的父控件
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2016/10/11
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "DialogParent.h"
#include "TSymbol.h"

class Button;
class QHBoxLayout;
class QTreeWidget;

class TVariate;

class MacroWidgetParent :public DialogParent
{
	Q_OBJECT

	typedef TSymbol::SymbolType SymbolType;

public:
	MacroWidgetParent(const QString& macroText,QWidget* parent = nullptr);


	virtual ~MacroWidgetParent();

protected:
	virtual void OnConfirm() = 0;

	void AddPosition(const QString& name);

private slots:
	void SlotOnButtonConfirmClicked();
	void SlotOnButtonCancleClicked();

private:
	virtual void UpdateText() override;

	const QStringList GetVariates(SymbolType type) const;

	void InitMacroText(const QString& macroText);
	void InitLayout();
	void InitSignalSlot();


protected:
	QString m_macroName{};
	QString m_macroParameterText{};
	QVector<TVariate*> m_variates;

	QTreeWidget* m_treeWidget;

	Button* m_btnConfirm;
	Button* m_btnCancle;
};

#endif