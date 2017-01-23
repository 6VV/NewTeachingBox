#ifndef _TEACHING_BOX_DYNAMIC_CONTROLLER_H_
#define _TEACHING_BOX_DYNAMIC_CONTROLLER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DynamicController.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/11
//  Description:	用于配置机器人运动的动态倍率参数，可以按照配置的百分比降低降低机器人动态参数。动态倍率参数会对移动速度参数整体造成影响。
//					本类生成并维护动态倍率参数相关的标签及按钮，控制按钮响应事件及标签显示，同时可返回倍率参数以供使用。
//					此命令不仅同重叠命令一样可以变更移动速度，同时该命令中设置的比率还会对 加速度、速度进行限制。 
//					机器人在运行的时候，机器人是按照倍率参数 50%乘以动态倍率参 数 50%的速度来走轨迹的（25%）。
//  Others:			本类并未设计为单例模式，但不应生成多个对象，建议在某一个对象中生成唯一对象。
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/11
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QObject"
#include <vector>
#include "SingleTon.h"

class QLabel;
class QPushButton;

class DynamicController:public QObject
{
	friend SingleTon<DynamicController>;

	Q_OBJECT

public:
	static int InitSpeed();

public:
	static DynamicController* GetInstance();

	void Accelerate();
	void AddWidget(QComboBox* speedComboBox);
	void Decelerate();


	double Speed() const;
	void Stop();

private:
	DynamicController()=default;
	DynamicController(const DynamicController&) = delete;
	DynamicController& operator=(const DynamicController&) = delete;
	~DynamicController() = default;


	void AccelerateThread();
	void DecelerateThread();
	const QString SpeedText(double speed) const;
	void UpdateSpeed();

private:
	double m_speed{ InitSpeed() };
	bool m_isOperateDyn = false;
	QComboBox* m_speedComboBox;
};

#endif // !_TEACHING_BOX_DYNAMIC_CONTROLLER_H_
