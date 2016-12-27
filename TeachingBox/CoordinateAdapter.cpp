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

tPoseEuler CoordinateAdapter::CartTeachThreeBase(const tPoseEuler& point1, const tPoseEuler& point2, const tPoseEuler& point3)
{
	auto cp1 = LocalToCoor(point1);
	auto cp2= LocalToCoor(point2);
	auto cp3= LocalToCoor(point3);

	return CoorToLocal(Coor::CartTeachThreeBase(cp1, cp2, cp3));
}

tPoseEuler CoordinateAdapter::CartTeachThreeNoBase(const tPoseEuler& point1, const tPoseEuler& point2, const tPoseEuler& point3)
{
	auto cp1 = LocalToCoor(point1);
	auto cp2 = LocalToCoor(point2);
	auto cp3 = LocalToCoor(point3);

	return CoorToLocal(Coor::CartTeachThreeNoBase(cp1, cp2, cp3));
}

tPoseEuler CoordinateAdapter::CartTeachOne(const tPositionCartesian& point1)
{
	auto cp1 = LocalToCoor(point1);

	return CoorToLocal(Coor::CartTeachOne(cp1));
}
