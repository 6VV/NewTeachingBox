
#ifndef _COORDINATE_H_
#define _COORDINATE_H_


#include "Target_GlobalDefine.h"
#include "TrajectoryCommon.h"


namespace Coor{

	//�����ʾ֮���ת��
	tPoseHomogeneous TransEuler2Homogeneous(tPoseEuler & PoseEuler_p);
	tPoseEuler TransHomogeneous2Euler(tPoseHomogeneous & PoseHomogeneous_p);
	tPose TransEuler2Pose(tPoseEuler & PoseEuler_p);
	tPoseEuler TransPose2Euler(tPose & Pose_p);
	tPoseHomogeneous TransPose2Homogeneous(tPose & Pose_p);
	tPose TransHomogeneous2Pose(tPoseHomogeneous & PoseHomogeneous_p);


	//ʵ������任���ο�����ϵΪBaseRefSys_p��ƫ����ΪTransition_p
	tPoseEuler CartAdd(tPoseEuler& BaseRefSys_p, tPoseEuler& Transition_p);

	//�������
	//����A - ����B => ���귵��ֵ
	tPoseEuler CartMinus(tPoseEuler& A_p, tPoseEuler& B_p);



	//����ϵʾ�̷��������㣨��ԭ�㣩
	//CartTeach From Three Points With Base
	tPoseEuler CartTeachThreeBase(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p, int xyz, int xyzxyz);

	//����ϵʾ�̷��������㣨��ԭ�㣩
	//CartTeach From Three Points Without Base
	tPoseEuler CartTeachThreeNoBase(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p, int xyz1_p, int xyz2_p);

	//����ϵʾ�̷�����һ�㣨������̬��
	tPoseEuler CartTeachOne(tPositionCartesian& Point1_p);


	//�����ǹ�������ϵʾ��
	//�ĵ㷨
	tPositionCartesian ToolFrameSetWithFourPoints(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p, tPoseEuler& Point4_p);


	//1POINT 6D ����
	tPostureEuler ToolFrameSetWithOnePoint(tPoseEuler& PoseRobot_p, int mode_p, TYPE_BOOL direction_p);




	class CCoordinate
	{
	public:
		tPose m_Pose;
		tPoseEuler m_PoseEuler;//һ������ϵ�����ֲ�ͬ��ʾ����


	public:
		CCoordinate();
		CCoordinate(tPose Pose_p);
		CCoordinate(tPoseEuler PoseEuler_p);
		CCoordinate(tPoseHomogeneous PoseHomogeneous_p);
		~CCoordinate();

		tPoseHomogeneous Homogeneous();//ת����Homogeneous��ʾ��
		//tPose Pose();

		CCoordinate Transit(tPoseEuler PoseEuler_p);//����ǰ����ϵ����PoseEuler_p�任�������µ�����ϵ
		CCoordinate Transit(tPose Pose_p);//����ǰ����ϵ����Pose_p�任�������µ�����ϵ

	};




}











#endif//_COORDINATE_H_
