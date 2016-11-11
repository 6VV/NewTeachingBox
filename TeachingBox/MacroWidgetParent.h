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
#include "ComboBoxWithParentTreeItem.h"
#include "TVariateManager.h"
#include "Context.h"
#include "TreeWidgetItemWithVariate.h"


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
	virtual void OnConfirm();
	virtual QString MacroName()=0;

	template<typename T>
	void AddParameter(SymbolType type, const QString& name);

	template<typename T>
	void AddParameter(SymbolType type, int index);

private slots:
	void SlotOnButtonConfirmClicked();
	void SlotOnButtonCancleClicked();

	void SlotOnParameterChanged();

private:
	virtual void UpdateText() override;

	QMap<QString, QStringList> GetVariateMap(SymbolType type) const;
	ComboBoxWithParentItem* GetComboBox(SymbolType type) const;

	void InitMacroText(const QString& macroText);
	void InitLayout();
	void InitSignalSlot();

	QString GetSuggestName(SymbolType type) const;

protected:
	QString m_macroName{};
	QStringList m_macroParameterList{};
	//QString m_macroParameterText{};

	QVector<ComboBoxWithParentItem*> m_parameterComboBoxes;		/*保存所有参数选择控件*/

	QTreeWidget* m_treeWidget;

private:
	QMap<QString, QVector<TVariate*>> m_variatesMap;		/*保存本作用域中所有有效变量*/
	QVector<std::shared_ptr<TVariate>> m_newVariates{};	/*保存所有新建变量*/


	Button* m_btnConfirm;
	Button* m_btnCancle;
};

template<typename T>
void MacroWidgetParent::AddParameter(SymbolType type, const QString& name)
{
		auto variateComboBox = GetComboBox(type);
		m_parameterComboBoxes.append(variateComboBox);

		variateComboBox->setCurrentText(name);
	
		auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(Context::projectContext.ProgramOpened(), variateComboBox->currentText());
	
		if (variate==nullptr)
		{
			auto name = GetSuggestName(type);
			variateComboBox->addItem(QPixmap(IMAGE_LOGO_LOCAL), name);
			std::shared_ptr<TVariate> newVariate(new T(Context::projectContext.ProgramOpened(), name));
			m_newVariates.append(newVariate);
			newVariate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
		}
		else
		{
			variate->ReadTreeWidgetItem(m_treeWidget->invisibleRootItem(), m_treeWidget);
		}
	
		auto item = m_treeWidget->topLevelItem(m_treeWidget->topLevelItemCount() - 1);
	
		m_treeWidget->setItemWidget(item, 1, variateComboBox);
		variateComboBox->ParentItem(dynamic_cast<TreeWidgetItemWithVariate*>(item));

		connect(variateComboBox, SIGNAL(currentTextChanged(const QString&)), this, SLOT(SlotOnParameterChanged()));
}

template<typename T>
inline
void MacroWidgetParent::AddParameter(SymbolType type, int index)
{
	if (m_macroParameterList.size()>index)
	{
		AddParameter<T>(type, m_macroParameterList.at(index));
	}
	else
	{
		AddParameter<T>(type, "");
	}
}

#endif