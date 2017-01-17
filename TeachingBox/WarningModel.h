#ifndef _TEACHING_BOX_WARNING_MODEL_H_
#define _TEACHING_BOX_WARNING_MODEL_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WarningModel.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/16
//  Description:    警告信息模型，存储各类警告信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QAbstractItemModel"
#include <deque>
#include <memory>
#include "WarningInfo.h"

class WarningModel :public QAbstractTableModel
{
	Q_OBJECT

private:
	typedef std::shared_ptr<std::deque<std::shared_ptr<WarningInfo>>> ModelMapType;

public:
	static const QString CATEFORY_INFO_ICON_PATH;
	static const QString CATEFORY_WARNING_ICON_PATH;
	static const QString CATEFORY_ERROR_ICON_PATH;

	static const QString STATE_SOLVED_ICON_PATH;
	static const QString STATE_TO_BE_SOLVED_ICON_PATH;
	static const QString STATE_WITHOUT_SOLVE_ICON_PATH;

public:
	static WarningModel* GetInstance();

private:
	WarningModel(QWidget* parent = nullptr);
	WarningModel& operator=(const WarningModel&) = default;
	~WarningModel() = default;

public:
	Q_INVOKABLE virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

	Q_INVOKABLE virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

	Q_INVOKABLE virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

	virtual QVariant headerData(int section, Qt::Orientation orientation, int role /* = Qt::DisplayRole */) const override;

	virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

	virtual Qt::ItemFlags flags(const QModelIndex &index) const override;

	void ChangeMode(WarningInfo::Category category);	/*切换显示的数据类型*/

	WarningInfo GetWarningInfo(int index) const;	/*获取第index个数据*/

	bool RemoveAll();	/*删除所有可被删除的数据*/
	bool RemoveRow(int row);	/*删除特定行数据*/
	bool RemoveBack();	/*删除最后一个可被删除的数据*/

	int NextToBeSolved() const;	/*下一个可被处理的数据*/
	int NextToBeSolvedAtCurrentCategory() const;	/*当前类型下一个可被处理的数据*/

	void SolveAllAtCurrentCategory();	/*处理当前类型下所有数据*/
	void SolveRow(int row); /*处理特定行数据*/
	void SolveRowAtCurrentCategory(int row);	/*处理当前类型下特定行数据*/

private:
	bool IsCouldRemove(const WarningInfo& info) const;	/*是否可被删除*/
	bool IsCouldBeSolved(const WarningInfo& info) const;	/*是否可被处理*/

	int NextToBeSolved(ModelMapType map) const;	/*集合map中下一个可被处理的数据*/

	void PushFront(std::shared_ptr<WarningInfo> warningInfo);	/*在头部添加数据*/

private:
	ModelMapType m_allInfos;	/*所有数据*/
	ModelMapType m_currentInfos;	/*当前显示的数据*/

	WarningInfo::Category m_category = WarningInfo::CATEGORY_ALL;	/*当前数据类型*/
};

#endif