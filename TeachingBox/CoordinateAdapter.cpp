#include "stdafx.h"
#include "CoordinateAdapter.h"
#include "..\TeachingBoxFunction\TrajectoryCommon.h"
#include "..\TeachingBoxFunction\Coordinate.h"


Coor::tPoseEuler LocalToCoor(const tPoseEuler& poseEuler)
{
	Coor::tPoseEuler desPose;
	desPose.m_PositionCartesian.m_X = poseEuler.m_PositionCartesian.m_X;
	desPose.m_PositionCartesian.m_Y = poseEuler.m_PositionCartesian.m_Y;
	desPose.m_PositionCartesian.m_Z = poseEuler.m_PositionCartesian.m_Z;

	desPose.m_PostureEuler.m_A = poseEuler.m_PostureEuler.m_A;
	desPose.m_PostureEuler.m_B = poseEuler.m_PostureEuler.m_B;
	desPose.m_PostureEuler.m_C = poseEuler.m_PostureEuler.m_C;

	return desPose;
}

Coor::tPositionCartesian LocalToCoor(const tPositionCartesian& point)
{
	Coor::tPositionCartesian result;
	result.m_X = point.m_X; 
	result.m_Y = point.m_Y;
	result.m_Z = point.m_Z;

	return result;
}

tPoseEuler CoorToLocal(const Coor::tPoseEuler& poseEuler)
{
	tPoseEuler desPose;
	desPose.m_PositionCartesian.m_X = poseEuler.m_PositionCartesian.m_X;
	desPose.m_PositionCartesian.m_Y = poseEuler.m_PositionCartesian.m_Y;
	desPose.m_PositionCartesian.m_Z = poseEuler.m_PositionCartesian.m_Z;

	desPose.m_PostureEuler.m_A = poseEuler.m_PostureEuler.m_A;
	desPose.m_PostureEuler.m_B = poseEuler.m_PostureEuler.m_B;
	desPose.m_PostureEuler.m_C = poseEuler.m_PostureEuler.m_C;

	return desPose;
}

tPositionCartesian CoorToLocal(const Coor::tPositionCartesian& point)
{
	tPositionCartesian result;
	result.m_X = point.m_X;
	result.m_Y = point.m_Y;
	result.m_Z = point.m_Z;

	return result;
}

tPostureEuler CoorToLocal(const Coor::tPostureEuler& point)
{
	tPostureEuler result;
	result.m_A = point.m_A;
	result.m_B = point.m_B;
	result.m_C = point.m_C;

	return result;
}

tPoseEuler CoordinateAdapter::CartTeachThreeBase(const tPoseEuler& point1, const tPoseEuler& point2, const tPoseEuler& point3, int xyz, int xyzxyz)
{
	auto cp1 = LocalToCoor(point1);
	auto cp2= LocalToCoor(point2);
	auto cp3= LocalToCoor(point3);

	return CoorToLocal(Coor::CartTeachThreeBase(cp1, cp2, cp3,xyz,xyzxyz));
}

tPoseEuler CoordinateAdapter::CartTeachThreeNoBase(const tPoseEuler& point1, const tPoseEuler& point2, const tPoseEuler& point3, int xyz1_p, int xyz2_p)
{
	auto cp1 = LocalToCoor(point1);
	auto cp2 = LocalToCoor(point2);
	auto cp3 = LocalToCoor(point3);

	return CoorToLocal(Coor::CartTeachThreeNoBase(cp1, cp2, cp3, xyz1_p, xyz2_p));
}

tPoseEuler CoordinateAdapter::CartTeachOne(const tPositionCartesian& point1)
{
	auto cp1 = LocalToCoor(point1);

	return CoorToLocal(Coor::CartTeachOne(cp1));
}

tPositionCartesian CoordinateAdapter::ToolFrameSetWithFourPoints(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p, tPoseEuler& Point4_p)
{
	auto cp1 = LocalToCoor(Point1_p);
	auto cp2 = LocalToCoor(Point2_p);
	auto cp3 = LocalToCoor(Point3_p);
	auto cp4 = LocalToCoor(Point4_p);


	return CoorToLocal(Coor::ToolFrameSetWithFourPoints(cp1, cp2, cp3, cp4));
}

tPostureEuler CoordinateAdapter::ToolFrameSetWithOnePoint(tPoseEuler& PoseRobot_p, int mode_p, unsigned char direction_p)
{
	auto cp = LocalToCoor(PoseRobot_p);

	return CoorToLocal(Coor::ToolFrameSetWithOnePoint(cp,mode_p,direction_p));

}
