

#ifndef _TARGET_CONFIG_H_
#define _TARGET_CONFIG_H_

namespace Coor{
#define DEBUG	//���log�ļ�

#define _WIN32_				1
#define TARGET_SYSTEM		_WIN32_


#define SYSTEM_CYCLE	0.01	//s


#define MAX_AXESGROUP_NUM	1
#define MC_BACKWARD_ENABLE  FALSE



#define ROBOT_MECHINE_TYPE_ER20C10	//����������

	//#define RATIO_LENGTH_THETA_THRESHOLD	100	// ����*RATIO_LENGTH_THETA_THRESHOLD > Length�� �򰴻��ȼ���
#define MAX_THETA_VELOCITY	5	//��̬����ٶ� ��/��
#define MAX_THETA_ACCELERATION	100	//��̬����ٶ� ��/��2
#define MAX_THETA_JERK	200	//��̬����ٶ� ��/��3


#define FOLLOW_POSITION_ENABLE	FALSE//TRUE //ֱ�ߡ�Բ���Լ�����ʱ��ֻ������λ�������㣬��������̬������
#define MAX_THETA_VELOCITY_SCALE 8	//�� FOLLOW_POSITION_ENABLE Ϊ TRUE ʱ����̬���ٶȿ��ܻᳬ��MAX_THETA_VELOCITY��ֻ������MAX_THETA_VELOCITY_SCALE��


#define ERROR_LOG_MAXNUM 10


}


#endif  // #ifndef _TARGET_CONFIG_H_


