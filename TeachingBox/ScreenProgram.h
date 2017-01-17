#ifndef _TEACHING_BOX_SCREEN_PROGRAM_H_
#define _TEACHING_BOX_SCREEN_PROGRAM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenProgram.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/05
//  Description:	程序界面
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/
#include "ScreenMainParent.h"
#include "QBoxLayout"

class CodeEditorManager;
class Button;
class ButtonGroup;
class SimpleKeyboard;

class ScreenProgram:public ScreenMainParent
{
	Q_OBJECT

public:
	ScreenProgram(QWidget* parent);
	~ScreenProgram() override;

private slots:
	void SlotOnButtonAddvanceClicked();
	void SlotOnButtonModifyClicked();
	void SlotOnButtonNewClicked();
	void SlotOnButtonEditClicked();
	void SlotOnButtonSetPCClicked();

private:
	void Init();
	void InitSignalSlot();
	void InitButtonGroup();
	void InitEditGroup();
	void InitAddvanceGroup();

	virtual void showEvent(QShowEvent *e) override;
	virtual QList<QWidget*> GetButtonList() override;
	virtual QLayout* GetMainLayout() override;
	virtual void UpdateText() override;
private:
	CodeEditorManager* m_codeEditor;
	QVBoxLayout* m_editorLayout;
	SimpleKeyboard* m_simpleKeyboard = nullptr;
	bool m_isKeyboardVisiable=false;

	Button* m_btnModify;
	Button* m_btnMacro;
	Button* m_btnNew;
	Button* m_btnSetPC;
	Button* m_btnEdit;
	Button* m_btnAddvance;

	/*编辑按钮窗口*/
	ButtonGroup* m_btnGroupEdit;
	Button* m_btnSelectAll;
	Button* m_btnCut;
	Button* m_btnCopy;
	Button* m_btnPaste;
	Button* m_btnDelete;
	Button* m_btnUndo;
	Button* m_btnRedo;

	/*高级功能*/
	ButtonGroup* m_btnGroupAddvance;
	Button* m_btnKeyboard;
	//Button* m_btnSubProgram;
	Button* m_btnFormat;
	Button* m_btnSearch;
	Button* m_btnNote;
	//Button* m_btnInvalidate;
};

#endif