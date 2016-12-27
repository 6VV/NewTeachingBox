
#ifndef _COORDINATE_H_
#define _COORDINATE_H_

#include "Target_GlobalDefine.h"
#include "TrajectoryCommon.h"

namespace Coor{

	//坐标表示之间的转换
	tPoseHomogeneous TransEuler2Homogeneous(tPoseEuler & PoseEuler_p);
	tPoseEuler TransHomogeneous2Euler(tPoseHomogeneous & PoseHomogeneous_p);
	tPose TransEuler2Pose(tPoseEuler & PoseEuler_p);
	tPoseEuler TransPose2Euler(tPose & Pose_p);
	tPoseHomogeneous TransPose2Homogeneous(tPose & Pose_p);
	tPose TransHomogeneous2Pose(tPoseHomogeneous & PoseHomogeneous_p);


	//实现坐标变换，参考坐标系为BaseRefSys_p，偏移量为Transition_p
	tPoseEuler CartRefSys(tPoseEuler& BaseRefSys_p, tPoseEuler& Transition_p);

	//坐标系示教方法：三点（含原点）
	//CartTeach From Three Points With Base
	tPoseEuler CartTeachThreeBase(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p);

	//坐标系示教方法：三点（无原点）
	//CartTeach From Three Points Without Base
	tPoseEuler CartTeachThreeNoBase(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p);

	//坐标系示教方法：一点（保持姿态）
	tPoseEuler CartTeachOne(tPositionCartesian& Point1_p);


	//以下是工具坐标系示教
	//四点法
	tPositionCartesian ToolFrameSetWithFourPoints(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p, tPoseEuler& Point4_p);


	//1POINT 6D 方法
	tPostureEuler ToolFrameSetWithOnePoint(tPoseEuler& PoseRobot_p, tPoseEuler& Point1_p, int mode_p, TYPE_BOOL direction_p);




	class CCoordinate
	{
	public:
		tPose m_Pose;
		tPoseEuler m_PoseEuler;//一个坐标系的两种不同表示方法


	public:
		CCoordinate();
		CCoordinate(tPose Pose_p);
		CCoordinate(tPoseEuler PoseEuler_p);
		CCoordinate(tPoseHomogeneous PoseHomogeneous_p);
		~CCoordinate();

		tPoseHomogeneous Homogeneous();//转换成Homogeneous表示法
		//tPose Pose();

		CCoordinate Transit(tPoseEuler PoseEuler_p);//将当前坐标系乘以PoseEuler_p变换，返回新的坐标系
		CCoordinate Transit(tPose Pose_p);//将当前坐标系乘以Pose_p变换，返回新的坐标系

	};

}














#endif//_COORDINATE_H_
