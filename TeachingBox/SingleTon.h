#ifndef _TEACHING_BOX_SINGEL_TON_H_
#define _TEACHING_BOX_SINGEL_TON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    SingleTon.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/29
//  Description:	模板类，实现单例模式，当需要一个全局唯一类时，可将该类设为此模板类的友元，
//					将该类设为此模板的类型，返回的实例即为唯一类
//  Others:			本类采用了静态指针，而非静态变量，是为了保证每个单例可在需要时被创建，不需要时可随时销毁
//  History:
//    <author>      刘巍 
//    <time>        2016/07/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <mutex>

template<typename TYPE>
class CSingleTon
{
public:
	/*获取唯一实例*/
	static TYPE* GetInstance()
	{
		static std::mutex mutex;

		if (!m_instance)
		{
			std::lock_guard<std::mutex> lg(mutex);

			if (!m_instance)
			{
				m_instance = new TYPE;
			}

		}
		return m_instance;
	}

	/*销毁实例,可手动调用，或在其它类的析构函数中调用*/
	static void Destroy()
	{
		if (m_instance)
		{
			delete m_instance;
			m_instance = nullptr;
		}
	}

	/*垃圾回收类，用于在程序退出时释放那些之前未被释放掉的内存*/
private:
	class CGarbo
	{
	public:
		CGarbo();
		~CGarbo()
		{
			CSingleTon::Destroy();
		}
	};
	static CGarbo m_garbo;

private:
	static TYPE* m_instance; /*唯一实例*/

	/*禁止构造函数*/
	CSingleTon();
	CSingleTon(const CSingleTon&);
	CSingleTon& operator=(const CSingleTon&);

	/*禁止析构函数*/
	~CSingleTon();
};

template<typename TYPE>
TYPE* CSingleTon<TYPE>::m_instance = nullptr;

#endif
