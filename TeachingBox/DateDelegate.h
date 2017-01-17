#ifndef _TEACHING_BOX_DATE_DELEGATE_H_
#define _TEACHING_BOX_DATE_DELEGATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DateDelegate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/16
//  Description:    日期委托，用于控制视图上日期类型的显示、操作方式
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QItemDelegate"

class DateDelegate :public QItemDelegate
{
	Q_OBJECT

public:
	DateDelegate(QObject* parent = nullptr);

	virtual QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

	virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

	virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

	virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

};

#endif