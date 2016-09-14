#ifndef _TEACHING_BOX_SCREEN_PROJECT_H_
#define _TEACHING_BOX_SCREEN_PROJECT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenProject.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	项目界面，显示当前所有项目，包括功能：
//					1、新建项目：在总项目文件夹下新建一以项目名命名的文件夹
//					2、新建程序：在选择的项目下，新建一txt文档，所有文件均以EOF结尾
//					3、删除文件：根据选择的内容，删除txt文档或项目文件夹
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ScreenMainParent.h"
#include <memory>

class QTreeWidget;
class Button;
class ButtonGroup;
class ProjectManager;
class QTreeWidgetItem;

class ScreenProject:public ScreenMainParent
{
	Q_OBJECT

private:
	enum LoadState
	{
		LOADED,
		UNLOADED,
	};

public:
	ScreenProject(QWidget* parent);
	~ScreenProject() override;

private slots:
	void SlotOnButtonCloseClicked();
	void SlotOnButtonDeleteClicked();
	void SlotOnButtonFileClicked();
	void SlotOnButtonLoadClicked();

	void SlotOnButtonNewProjectClicked();
	void SlotOnButtonNewProgramClicked();
	void SlotOnButtonOpenClicked();
	void SlotOnButtonRefreshClicked();

private:
	virtual QList<QPushButton*> GetButtonList() override;
	virtual QLayout* GetMainLayout() override;
	virtual void UpdateText() override;


	void Init();
	void InitButtonGroup();
	void InitSignalSlot();
	bool IsCurrentItemValidity();
	bool IsCurrentItemProject();
	bool IsCurrentItemProgram();

	void InitFileTree();

	void SetLoadState(QTreeWidgetItem* projectItem,LoadState state);

	void UpdateLoadProjectState(QTreeWidgetItem* projectItem);

private:
	std::unique_ptr<ProjectManager> m_projectManager;
	QTreeWidget* m_treeWidget;

	Button* m_btnLoad;
	Button* m_btnOpen;
	Button* m_btnClose;
	Button* m_btnInfo;
	Button* m_btnRefresh;
	Button* m_btnFile;

	/*文件相关按钮*/
	ButtonGroup* m_btnGroupFile;
	Button* m_btnNewProject;
	Button* m_btnNewProgram;
	Button* m_btnDelete;
};

#endif