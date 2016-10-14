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

private:
	static const QString IMAGE_LOGO_SYSTEM;
	static const QString IMAGE_LOGO_COORPERATER;
	static const QString IMAGE_LOGO_GLOBAL;
	static const QString IMAGE_LOGO_PROJECT;
	static const QString IMAGE_LOGO_LOCAL;

	static const QMap<SymbolType, QString> TYPE_HEADER_MAP;

public:
	MacroWidgetParent(const QString& macroText,QWidget* parent = nullptr);

	virtual ~MacroWidgetParent();

protected:
	virtual void OnConfirm() = 0;

	void AddPosition(const QString& name);
	void AddParameter(SymbolType type, const QString& name);

private slots:
	void SlotOnButtonConfirmClicked();
	void SlotOnButtonCancleClicked();

private:
	virtual void UpdateText() override;

	QMap<QString, QStringList> GetVariateMap(SymbolType type) const;
	QComboBox* GetComboBox(SymbolType type) const;

	void InitMacroText(const QString& macroText);
	void InitLayout();
	void InitSignalSlot();

	QString GetSuggestName(SymbolType type) const;

protected:
	QString m_macroName{};
	QString m_macroParameterText{};
	QMap<QString,QVector<TVariate*>> m_variatesMap;

	QTreeWidget* m_treeWidget;

	Button* m_btnConfirm;
	Button* m_btnCancle;
};

#endif