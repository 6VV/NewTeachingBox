#ifndef _TEACHING_BOX_DIALOG_NEW_VARIATE_H_
#define _TEACHING_BOX_DIALOG_NEW_VARIATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DialogNewVariate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/01
//  Description:	新建变量，用户输入变量信息并确认后，将添加变量到数据库中，并更新变量编辑界面
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/01
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>
#include "DialogParent.h"

class Button;
class QLayout;
class QWidget;
class QTreeWidget;
class QTableWidget;
class QLineEdit;
class QTreeWidgetItem;
class QComboBox;
class IEditVariate;

namespace VariateWidget{

	class DialogNewVariate :public DialogParent
	{
		Q_OBJECT

	public:
		DialogNewVariate(const QString& scope, IEditVariate* iEditVariate, QWidget* parent);
		~DialogNewVariate();

		private slots:
		void SlotOnConfrimButtonClicked();
		void SlotOnCancleButtonClicked();
		void SlotOnTypeChanged(QTreeWidgetItem* item);

		//void UpdateVariateWidget(const QString& currentType);

	private:
		//void showEvent(QShowEvent *) override;
		void UpdateText() override;

		bool CheckNameValid(const QString& name);

		void Destroy();

		QLayout* GetButtonLayout();
		QWidget* GetTitleWidget();
		QLayout* GetVariateLayout();
		QWidget* GetVariateTypeWidget();
		QWidget* GetVariateSettingWidget();

		void Init();
		void InitLayout();

		void InitSignalSlot();

	private:
		QString m_scope;
		IEditVariate* m_iEditVariate;

		QTreeWidget* m_treeWidget;
		QTreeWidget* m_variateTree;

		Button* m_btnConfrim;
		Button* m_btnCancle;

	};
}
#endif
