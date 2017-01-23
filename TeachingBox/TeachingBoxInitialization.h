#ifndef _TEACHING_BOX_INTIALIZATION_H_
#define _TEACHING_BOX_INTIALIZATION_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TeachingBoxInitialization.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/20
//  Description:    示教盒初始化器，用于在示教盒启动时检查初始状态，若缺少数据，则采用添加默认的初始化数据
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/20
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class TRefSys;
class TToolSys;
class User;

class TeachingBoxInitialization
{
public:
	static std::shared_ptr<User> Adminastrator();
	static std::shared_ptr<TToolSys> DefaultToolSys();
	static std::shared_ptr<TRefSys> WorldRefSys();

public:
	TeachingBoxInitialization();
	
};

#endif