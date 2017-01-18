#ifndef _TEACHING_BOX_SYSTEM_DIALOG_WIDGET_PARENT_H_
#define _TEACHING_BOX_SYSTEM_DIALOG_WIDGET_PARENT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    SystemDialogWidgetParent.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    坐标系对话框控件的父控件，用于职责链模式
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QWidget"
#include "QStackedWidget"
#include "IRemoteFeedbackListener.h"

class QLineEdit;
class CoordinateSystemTeachInfo;
class Button;

class SystemDialogWidgetParent :public QWidget, public IRemoteFeedbackListener
{
	Q_OBJECT

signals:
	void SignalOnCancelClicked();

public:
	SystemDialogWidgetParent(QStackedWidget* parent);
	virtual ~SystemDialogWidgetParent();

	void SetCoorInfo(std::shared_ptr<CoordinateSystemTeachInfo> coorInfo);
	void SetNextWidget(SystemDialogWidgetParent* widget);

protected:
	virtual void showEvent(QShowEvent *event) override;
	virtual void hideEvent(QHideEvent *event) override;
	virtual void paintEvent(QPaintEvent *event) override;

	virtual void OnReseivePose(const tPoseEuler& pose= {}) override;

	virtual bool HavePre();
	virtual bool HaveNext();

	virtual QWidget* MainWidget() = 0;
	virtual QString IllustrationPixmapPath()=0;

	virtual void OnNextButtonClicked();

	void GetRemotePose();
	bool IsTeached();
	QWidget* PointWidgetXYZ();
	void UpdateButtonState();

private:
	QWidget* IllustrationWidget();

	QLayout* ButtonLayout();
	void Init();
	void SetPreWidget(SystemDialogWidgetParent* widget);

protected:
	QLineEdit* m_ltX=nullptr;
	QLineEdit* m_ltY=nullptr;
	QLineEdit* m_ltZ=nullptr;
	QLineEdit* m_ltA=nullptr;
	QLineEdit* m_ltB=nullptr;
	QLineEdit* m_ltC=nullptr;

	Button* m_btnPre;
	Button* m_btnNext;
	Button* m_btnCancel;

	std::shared_ptr<CoordinateSystemTeachInfo> m_coorInfo = nullptr;

private:
	QStackedWidget* m_parentWidget=nullptr;
	QHBoxLayout* m_layoutMain=nullptr;
	QLabel* m_lbPixmap=nullptr;

	SystemDialogWidgetParent* m_preWidget = nullptr;
	SystemDialogWidgetParent* m_nextWidget = nullptr;

	bool m_isFirstShow = true;

};


#endif