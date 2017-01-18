#include "stdafx.h"
#include "CoordinateSystemTeachInfo.h"




void CoordinateSystemTeachInfo::UpdatePoseEuler(const tPoseEuler& poseEuler)
{
	values.at(index).poseEuler = std::make_shared<tPoseEuler>(poseEuler);

}

void CoordinateSystemTeachInfo::UpdateOrientation(Orientation orientation)
{
	values.at(index).orientation = orientation;
}

void CoordinateSystemTeachInfo::AddCoorSysInfo(const CoorSysInfo& coorInfo)
{
	values.push_back(coorInfo);
}

void CoordinateSystemTeachInfo::AddPoseEuler(const tPoseEuler& poseEuler)
{
	values.push_back({ X,std::make_shared<tPoseEuler>(poseEuler) });
}
