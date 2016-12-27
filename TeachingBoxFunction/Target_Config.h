

#ifndef _TARGET_CONFIG_H_
#define _TARGET_CONFIG_H_

namespace Coor{
#define DEBUG	//输出log文件

#define _WIN32_				1
#define TARGET_SYSTEM		_WIN32_


#define SYSTEM_CYCLE	0.01	//s


#define MAX_AXESGROUP_NUM	1
#define MC_BACKWARD_ENABLE  FALSE



#define ROBOT_MECHINE_TYPE_ER20C10	//机器人类型

	//#define RATIO_LENGTH_THETA_THRESHOLD	100	// 弧度*RATIO_LENGTH_THETA_THRESHOLD > Length， 则按弧度计算
#define MAX_THETA_VELOCITY	5	//姿态最大速度 度/秒
#define MAX_THETA_ACCELERATION	100	//姿态最大速度 度/秒2
#define MAX_THETA_JERK	200	//姿态最大速度 度/秒3


#define FOLLOW_POSITION_ENABLE	FALSE//TRUE //直线、圆弧以及过渡时，只允许按照位置来计算，不按照姿态来计算
#define MAX_THETA_VELOCITY_SCALE 8	//当 FOLLOW_POSITION_ENABLE 为 TRUE 时，姿态的速度可能会超过MAX_THETA_VELOCITY，只允许超过MAX_THETA_VELOCITY_SCALE倍


#define ERROR_LOG_MAXNUM 10


}


#endif  // #ifndef _TARGET_CONFIG_H_


