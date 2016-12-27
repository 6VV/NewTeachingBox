
#ifndef _TRAJECTORYGENERIC_H_
#define _TRAJECTORYGENERIC_H_



#include "Target_GlobalDefine.h"
#include "Target_Math.h"


namespace Coor{
	//Position
	typedef CVector tPositionCartesian;
	typedef tRotary33 tPostureRotary;

	typedef struct
	{
		CVector m_Vector;//绕此轴旋转Theta角
		LONG_REAL m_Theta;

	}tPostureAxisAngle;


	typedef struct
	{
		tPostureRotary m_PostureRotary;
		tPositionCartesian m_PositionCartesian;

	}tPose;

	typedef struct
	{
		LONG_REAL m_T[4][4];

	}tPoseHomogeneous;//homogeneous transformation 齐次变换



	typedef struct
	{
		double m_A;
		double m_B;
		double m_C;

	}tPostureEuler;


	typedef struct
	{
		tPositionCartesian m_PositionCartesian;
		tPostureEuler m_PostureEuler;

	}tPoseEuler;


	//Velocity
	typedef CVector tVelocityCartesian;
	typedef tRotary33 tVelocityRotary;

	typedef struct
	{
		//tVelocityRotary m_VelocityRotary;
		tVelocityCartesian m_VelocityCartesian;

		CVector m_K;	//轴角坐标中的轴
		LONG_REAL m_ThetaV;//Theta的速度V，角速度

	}tPoseVelocity;

	typedef struct
	{
		LONG_REAL m_V[4][4];

	}tVelocityHomogeneous;









	typedef enum
	{
		kCircModeBorder = 0,
		kCircModeCenter = 1,
		kCircModeRadius = 2,

	}tCircMode;

	typedef enum
	{
		kPathChoiceClockwise = 0,
		kPathChoioceCounterClockwise = 1,

	}tPathChoice;

	typedef enum
	{
		kPCS = 0,
		kMCS = 1,
		kACS = 2,

	}tCoordSystem;





}

#endif	//_TRAJECTORYGENERIC_H_



