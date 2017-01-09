#ifndef _TEACHING_BOX_VARIATE_VALUE_H_
#define _TEACHING_BOX_VARIATE_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateValue.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2016/12/13
//  Description:    变量值接口，提供变量值的相关操作
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2016/12/13
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "QObject"
#include "QStringList"

class QDataStream;
class QTreeWidget;
class QTreeWidgetItem;

class VariateValue
{
public:
	virtual ~VariateValue();

	virtual std::shared_ptr<VariateValue> Clone() const=0;

	/*************************************************
	//  Method:        void WriteToDataStream(QDataStream& dataStream)
	//  Description:   将变量值写入到字节流
	//  Author:        刘巍
	//  Date:          2016/12/14
	//  Returns:       void
	//  Parameter:     QDataStream& dataStream：被写入的字节流
	//  History:
	*************************************************/
	virtual void WriteToDataStream(QDataStream& dataStream) const = 0;

	/*************************************************
	//  Method:        void ReadFromDataStream(QDataStream& dataStream)
	//  Description:   从字节流读出数据
	//  Author:        刘巍
	//  Date:          2016/12/14
	//  Returns:       void
	//  Parameter:     QDataStream& dataStream：读取的字节流
	//  History:
	*************************************************/
	virtual void ReadFromDataStream(QDataStream& dataStream) = 0;

	virtual QStringList ToStrings() = 0;	/*获取字符串值*/
};

#endif