#ifndef _TEACHING_BOX_DIALOG_TOOL_SYSTEM_H_
#define _TEACHING_BOX_DIALOG_TOOL_SYSTEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenTeachToolSystem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/16
//  Description:	用于工具坐标系示教，给出示教步骤界面，使用户可按界面提示完成工具坐标系示教
	提供三种示教方法：
	1点法（保持方向）
	4点法（保持方向）
	6点法
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"

class TToolSys;

class DialogTeachToolSystem:public DialogParent
{
	Q_OBJECT

	using FunctionCreateStepWidget = QWidget*(DialogTeachToolSystem::*)();

public:
	DialogTeachToolSystem(TToolSys* variate, QWidget* parent = nullptr);

private:
	virtual void UpdateText() override;

	void AssertNotImplement();

	QWidget* GetIllustrationWidget();

	QWidget* OriginWidget();

	QWidget* OnePoint6D();

	QWidget* FourPointKeepOrientationWidgetStep1();
	QWidget* FourPointKeepOrientationWidgetStep2();
	QWidget* FourPointKeepOrientationWidgetStep3();
	QWidget* FourPointKeepOrientationWidgetStep4();

	QWidget* KeepOrientationWidgetResult();

	QWidget* OnePointChangeOrientationWidgetStep1();

	QWidget* GetToolWidget();
	QWidget* GetButtonWidget();

	void Init();

private:
	class Controller
	{
	public:
		/*示教方法*/
		enum TeachMethod
		{
			//ONE_POINT_KEEP_ORIENTATION,	/*一点（保持姿态）*/
			FOUR_POINT_KEEP_ORIENTATION,	/*四点（保持姿态）*/
			ONE_POINT_CHANGE_ORIENTATION,	/*一点（改变姿态）*/
		};

	public:
		Controller(DialogTeachToolSystem* screenMain, TToolSys* variate);

		void NextStep();
		void PreStep();

		bool HaveNextStep();
		bool HavePreStep();

	public:
		DialogTeachToolSystem* m_screenMain;	/*示教窗口父控件*/
		int m_step = -1;	/*当前步骤，-1表示示教方法选择过程*/
		TToolSys* m_oldVariate;	/*原变量*/
		TeachMethod m_teachMethod{ FOUR_POINT_KEEP_ORIENTATION };	/*当前示教方法*/
		QMap<TeachMethod, QVector<DialogTeachToolSystem::FunctionCreateStepWidget>> m_stepMap;	/*记录各示教方法中的示教步骤控件的生成函数*/
	};

	Controller m_controller;
	QWidget* m_currentWidget;
	QGridLayout* m_mainLayout;
};

#endif