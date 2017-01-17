#ifndef _TEACHING_BOX_SCREEN_VARIATE_H_
#define _TEACHING_BOX_SCREEN_VARIATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenVariate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/29
//  Description:	变量编辑界面，包括添加、删除、修改、清除未用变量
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ScreenMainParent.h"
#include "IEditVariate.h"
#include "IRemoteFeedbackListener.h"

class QPushButton;
class QTreeWidget;
class ButtonGroup;
class QTreeWidgetItem;
class VariateManagerWithHorizonHeader;

class ScreenVariate :public ScreenMainParent, IEditVariate, IRemoteFeedbackListener
{
	friend class ScreenManager;

	Q_OBJECT

public:
	const QString TYPE_ALL="";

public:
	virtual void OnNewVariate(TVariate& variate) override;

private:
	ScreenVariate(QWidget* parent = 0);
	ScreenVariate(const ScreenVariate&);
	ScreenVariate& operator=(const ScreenVariate&);
	~ScreenVariate();

private slots:
	void SlotOnDeleteVariateButtonClicked();
	void SlotOnVariateButtonClicked();
	void SlotOnNewVariateButtonClicked();
	void SlotOnTeachButtonClicked();

private:
	virtual QList<QWidget*> GetButtonList() override;
	virtual QLayout* GetMainLayout() override;
	virtual void showEvent(QShowEvent *) override;

	virtual void OnReseivePosition(const tAxesAllPositions& position) override;

	QTreeWidgetItem* FindScopeItem(const QString& scope);

	QString GetScope(QTreeWidgetItem* item) const;
	QTreeWidgetItem* GetScopeItem(QTreeWidgetItem* item) const;

	void Init();
	void InitTreeWidget();
	void InitButtonWidget();
	void InitSignalSlot();
	void InsertVariate(std::shared_ptr<TVariate> variate, QTreeWidgetItem* item);

	bool IsVariateItem(QTreeWidgetItem* item) const;
	bool IsScopeItem(QTreeWidgetItem* item) const;
	bool IsValueItem(QTreeWidgetItem* item) const;

	virtual void UpdateText() override;

private:
	QTreeWidget* m_treeWidget;
	VariateManagerWithHorizonHeader* m_variateWidgetManager;

	QPushButton* m_btnVariate;
	QPushButton* m_btnTeach;
	QPushButton* m_btnClearUnused;
	QPushButton* m_btnCheck;
	QComboBox* m_comboBoxType;

	ButtonGroup* m_btnGroupVariate;
	QPushButton* m_btnCopy;
	QPushButton* m_btnCut;
	QPushButton* m_btnPaste;
	QPushButton* m_btnRename;
	QPushButton* m_btnNew;
	QPushButton* m_btnDelete;
	QPushButton* m_btnSave;

private:
	struct PasteInfo
	{
		enum OperatorType
		{
			COPY,
			CUT,
		};
		OperatorType operatorType = COPY;
		std::shared_ptr<TVariate> variate=nullptr;
	};
	PasteInfo m_pasteInfo{};
};

#endif