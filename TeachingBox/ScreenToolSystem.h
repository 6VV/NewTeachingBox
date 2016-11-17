#ifndef _TEACHING_BOX_SCREEN_TOOL_SYSTEM_H_
#define _TEACHING_BOX_SCREEN_TOOL_SYSTEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenToolSystem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/16
//  Description:	生成工具坐标系示教操作界面，提供工具坐标系的相关信息，
		提供以下功能：
		显示查询当前可用工具坐标系：若未加载有项目，显示通用工具坐标系；若加载有项目，则额外显示项目坐标系
		工具坐标系示教
		添加、修改、删除、保存工具坐标系
		显示工具坐标系示意图
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/


#include "InternationalWidget.h"
#include "QVector"

class QGroupBox;
class QPushButton; 
class QLabel;
class QComboBox;
class QLineEdit;

class TToolSys;

class ScreenToolSystem :public InternationalWidget
{
	Q_OBJECT

public:
	ScreenToolSystem(QWidget* parent = nullptr);
	~ScreenToolSystem();
	
private:
	virtual void UpdateText() override;
	
	//显示界面时，更新控件信息，包括：
	//当前可用的工具坐标系，当前选择的工具坐标系值
	virtual void showEvent(QShowEvent *) override;

	//TVariate* GetCurrentVariate();
	QWidget* GetDataWidget();
	QWidget* GetIllustrationWidget();
	QWidget* GetToolWidget();
	QWidget* GetButtonWidget();

	TToolSys* GetVariate();
	QString GetVariateName();
	QString GetVariateScope();

	void Init();

	void OnDataChanged();

private:
	QGroupBox* m_toolBox;
	QGroupBox* m_dataBox;
	QGroupBox* m_illustrationBox;

	QPushButton* m_btnAdd;
	QPushButton* m_btnDelete;
	QPushButton* m_btnEdit;
	QPushButton* m_btnSave;

	QLabel* m_lbTool;
	QComboBox* m_comboBoxTool;

	QVector<QLineEdit*> m_dataLineEditList;
};

#endif