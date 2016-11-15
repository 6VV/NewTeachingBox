#ifndef _TEACHING_BOX_SCREEN_REFERENCE_SYSTEM_H_
#define _TEACHING_BOX_SCREEN_REFERENCE_SYSTEM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenReferenceSystem.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/14
//  Description:	用于查看、添加、删除、修改参考坐标系
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"
#include <array>

class Button;
class QLineEdit;
class VariateWidgetProducer;

class ScreenReferenceSystem :public InternationalWidget
{
	Q_OBJECT

public:
	ScreenReferenceSystem(QWidget* parent=nullptr);

private:
	virtual void UpdateText() override;

	QLayout* GetButtonLayout();
	QWidget* GetDataWidget();
	QWidget* GetSystemWidget();
	QWidget* GetTcpValueWidget();
	QLayout* GetValuesWidget(std::array<QLineEdit*,6> widgets,bool enabled);
	QLabel* GetValuesIllustrateWidget();
	QString GetCurrentScope();	/*获取当前作用域*/

	void Init();

	void OnAddButtonClicked();
	void OnEditButtonClicked();
	void OnDeleteButtonClicked();

	void OnRefSysChanged();
	
private:
	std::unique_ptr<VariateWidgetProducer> m_variateWidgetProducer;

	Button* m_btnEdit;
	Button* m_btnAdd;
	Button* m_btnDelete;

	QGroupBox* m_systemBox;
	QGroupBox* m_offsetBox;
	QGroupBox* m_tcpValueBox;

	QComboBox* m_comboBoxRefSys;
	QComboBox* m_comboBoxBaseSys;

	QLabel* m_lbRefSys;
	QLabel* m_lbBaseSys;

	QLabel* m_lbOffsetValuesIllustrate;
	QLabel* m_lbTcpValuesIllustrate;

	std::array<QLineEdit*,6> m_ltOffsetValues;
	std::array<QLineEdit*, 6> m_ltTcpValues;
};

#endif