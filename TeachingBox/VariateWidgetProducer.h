#ifndef _TEACHING_BOX_VARIATE_WIDGET_RPODUCER_H_
#define _TEACHING_BOX_VARIATE_WIDGET_RPODUCER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateWidgetProducer.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/16
//  Description:	提供变量控件的一些操作，包括：
		更新某类型变量的comboBox控件；
		获取对应某变量类型的建议名字；
		获取不同作用域对应的图标路径；
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QString"
#include "TSymbol.h"

class TVariate;

class VariateWidgetProducer
{
	typedef TSymbol::SymbolType SymbolType;


public:
	static const QString IMAGE_LOGO_SYSTEM;
	static const QString IMAGE_LOGO_COORPERATER;
	static const QString IMAGE_LOGO_GLOBAL;
	static const QString IMAGE_LOGO_PROJECT;
	static const QString IMAGE_LOGO_LOCAL;

public:
	VariateWidgetProducer();
	~VariateWidgetProducer();

	/*************************************************
	//  Method:        VariateWidgetProducer::UpdateComboBox(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap, QComboBox* comboBox)
	//  Description:   更新某类型变量的comboBox控件,显示该类型的完整变量名（包括作用域和变量名）
	//  Author:        刘巍
	//  Date:          2016/11/16
	//  Returns:       void
	//  Parameter:     SymbolType：变量类型
			const QMap<QString, QVector<TVariate*>>&：变量集合，key指作用域，QVector<TVariate*>指该作用域内的变量集合
			QComboBox*：需要更新的控件
	//  History:
	*************************************************/
	static void UpdateComboBoxWithWholeName(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap, QComboBox* comboBox);

	/*************************************************
	//  Method:        VariateWidgetProducer::UpdateComboBox(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap, QComboBox* comboBox)
	//  Description:   更新某类型变量的comboBox控件,显示该类型的简单变量名（不包括作用域）
	//  Author:        刘巍
	//  Date:          2016/11/16
	//  Returns:       void
	//  Parameter:     SymbolType：变量类型
			const QMap<QString, QVector<TVariate*>>&：变量集合，key指作用域，QVector<TVariate*>指该作用域内的变量集合
			QComboBox*：需要更新的控件
	//  History:
	*************************************************/
	static void UpdateComboBoxWithSimpleName(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap, QComboBox* comboBox);
	
	/*************************************************
	//  Method:		static QString GetSuggestName(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap)
	//  Description:获取对应某变量类型的建议名字，如Position的建立名为p2（若已存在p1，未存在p2）
	//  Author:		刘巍
	//  Date:		2016/11/16
	//  Returns:	void 
	//  Parameter:	SymbolType:变量类型
			const QMap<QString, QVector<TVariate*>>&：变量集合，key指作用域，QVector<TVariate*>指该作用域内的变量集合
	//  History:
	*************************************************/
	static QString GetSuggestName(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap);


	/*************************************************
	//  Method:		static QString GetIconPath(const QString& scope)
	//  Description:获取不同作用域对应的图标路径
	//  Author:     刘巍
	//  Date:       2016/11/16
	//  Returns:	QString:图标路径
	//  Parameter:	const QString&：作用域名
	//  History:
	*************************************************/
	static QString GetIconPath(const QString& scope);	

private:
	/*************************************************
	//  Method:static QMap<QString, QStringList> GetVariateMap(SymbolType type, const QMap<QString, QVector<TVariate*>>& variateMap)
	//  Description:获取作用域中某类型变量
	//  Author:        刘巍
	//  Date:          2016/11/16
	//  Returns:QMap<QString, QStringList>:不同作用域中的变量集合，QString指作用域，QStringList指变量名列表
	//  Parameter:SymbolType:变量类型
			const QMap<QString, QVector<TVariate*>>&：变量集合，key指作用域，QVector<TVariate*>指该作用域内的变量集合
	//  History:
	*************************************************/
	static QMap<QString, QStringList> GetVariateMap(SymbolType type, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap);
	static QMap<QString, QStringList> GetVariateMap(const QString& typeName, const QMap<QString, QVector<std::shared_ptr<TVariate>>>& variateMap);


};

#endif