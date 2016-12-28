#ifndef _DATA_STREAM_H_
#define _DATA_STREAM_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DataStream.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/19
//  Description:    数据流，用于数据序列化
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/19
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class QByteArray;
class QDataStream;
struct tTeachCmdAttribute;
struct tAxesAllPositions;
struct tDynamicConstraint;
struct tOverlapConstraint;
struct tMovLParam;
struct tMovCParam;
struct tPoseEuler;
struct tPositionCartesian;
struct tPostureEuler;

class DataStream
{
public:
	DataStream();
	~DataStream();

	QDataStream* GetOriginalDataStream() const;
	int Length() const;	//字节流长度
	int ReadRawBytes(char *c, unsigned int length) const;	//将数据写入到字节数组c
	int WriteRawBytes(const char* c, unsigned int length);//从字节数组c中获取数据
	void Seek(int pos);	//设置读写位置

	DataStream& operator>>(int& value) ;
	DataStream& operator>>(double& value);
	DataStream& operator>>(tTeachCmdAttribute& value);
	DataStream& operator>>(tAxesAllPositions& value);
	DataStream& operator>>(tDynamicConstraint& value);
	DataStream& operator>>(tOverlapConstraint& value);
	DataStream& operator>>(tMovLParam& value);
	DataStream& operator>>(tMovCParam& value);
	DataStream& operator>>(tPositionCartesian& value);
	DataStream& operator>>(tPostureEuler& value);
	DataStream& operator>>(tPoseEuler& value);


	DataStream& operator<<(int value) ;
	DataStream& operator<<(double value) ;
	DataStream& operator<<(const tTeachCmdAttribute& value);
	DataStream& operator<<(const tAxesAllPositions& value);
	DataStream& operator<<(const tDynamicConstraint& value);
	DataStream& operator<<(const tOverlapConstraint& value);
	DataStream& operator<<(const tMovLParam& value);
	DataStream& operator<<(const tMovCParam& value);
	DataStream& operator<<(const tPositionCartesian& value);
	DataStream& operator<<(const tPostureEuler& value);
	DataStream& operator<<(const tPoseEuler& value);


private:
	QByteArray* m_byteArray;
	QDataStream* m_dataStream;
};

#endif