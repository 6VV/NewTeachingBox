#include "Coordinate.h"

namespace Coor{
	//从tPoseEuler坐标到tPoseHomogeneous的变换
	//tPoseEuler --> tPoseHomogeneous
	tPoseHomogeneous TransEuler2Homogeneous(tPoseEuler & PoseEuler_p)
	{
		tPoseHomogeneous PoseHomogeneous;

		Roll_Pitch_Yaw(PoseEuler_p.m_PostureEuler.m_A,
			PoseEuler_p.m_PostureEuler.m_B,
			PoseEuler_p.m_PostureEuler.m_C,
			(double*)(PoseHomogeneous.m_T));

		PoseHomogeneous.m_T[0][3] = PoseEuler_p.m_PositionCartesian.m_X;
		PoseHomogeneous.m_T[1][3] = PoseEuler_p.m_PositionCartesian.m_Y;
		PoseHomogeneous.m_T[2][3] = PoseEuler_p.m_PositionCartesian.m_Z;

		return PoseHomogeneous;
	}


	//tPoseHomogeneous --> tPoseEuler
	tPoseEuler TransHomogeneous2Euler(tPoseHomogeneous & PoseHomogeneous_p)
	{
		tPoseEuler PoseEuler;

		PoseEuler.m_PositionCartesian.m_X = PoseHomogeneous_p.m_T[0][3];
		PoseEuler.m_PositionCartesian.m_Y = PoseHomogeneous_p.m_T[1][3];
		PoseEuler.m_PositionCartesian.m_Z = PoseHomogeneous_p.m_T[2][3];

		Matrix_RPY((double*)(PoseHomogeneous_p.m_T),
			&(PoseEuler.m_PostureEuler.m_A),
			&(PoseEuler.m_PostureEuler.m_B),
			&(PoseEuler.m_PostureEuler.m_C));

		return PoseEuler;
	}


	//tPoseEuler --> tPose
	tPose TransEuler2Pose(tPoseEuler & PoseEuler_p)
	{
		tPose Pose;
		tPoseHomogeneous PoseHomogeneous;

		Roll_Pitch_Yaw(PoseEuler_p.m_PostureEuler.m_A,
			PoseEuler_p.m_PostureEuler.m_B,
			PoseEuler_p.m_PostureEuler.m_C,
			(double*)(PoseHomogeneous.m_T));

		HomeMatrix2RP((double*)(PoseHomogeneous.m_T),
			(double*)(&(Pose.m_PostureRotary)),
			(double*)(Pose.m_PositionCartesian));

		return Pose;
	}


	//tPose --> tPoseEuler
	tPoseEuler TransPose2Euler(tPose & Pose_p)
	{
		tPoseEuler PoseEuler;
		tPoseHomogeneous PoseHomogeneous;

		RP2HomeMatrix((double*)(&Pose_p.m_PostureRotary),
			(double*)(Pose_p.m_PositionCartesian),
			(double*)(PoseHomogeneous.m_T));

		Matrix_RPY((double*)(PoseHomogeneous.m_T),
			&(PoseEuler.m_PostureEuler.m_A),
			&(PoseEuler.m_PostureEuler.m_B),
			&(PoseEuler.m_PostureEuler.m_C));

		PoseEuler.m_PositionCartesian = Pose_p.m_PositionCartesian;

		return PoseEuler;
	}


	//tPose --> tPoseHomogeneous
	tPoseHomogeneous TransPose2Homogeneous(tPose & Pose_p)
	{
		tPoseHomogeneous PoseHomogeneous;

		RP2HomeMatrix((double*)(&Pose_p.m_PostureRotary),
			(double*)(Pose_p.m_PositionCartesian),
			(double*)(PoseHomogeneous.m_T));

		return PoseHomogeneous;
	}

	//tPoseHomogeneous --> tPose
	tPose TransHomogeneous2Pose(tPoseHomogeneous & PoseHomogeneous_p)
	{
		tPose Pose;

		HomeMatrix2RP((double*)(PoseHomogeneous_p.m_T),
			(double*)(&(Pose.m_PostureRotary)),
			(double*)(Pose.m_PositionCartesian));

		return Pose;
	}


	//实现坐标变换，参考坐标系为BaseRefSys_p，偏移量为Transition_p
	tPoseEuler CartRefSys(tPoseEuler& BaseRefSys_p, tPoseEuler& Transition_p)
	{
		tPoseHomogeneous Base, T, Result;
		Base = TransEuler2Homogeneous(BaseRefSys_p);
		T = TransEuler2Homogeneous(Transition_p);

		MatrixMul((double*)(Base.m_T), (double*)(T.m_T), 4, 4, 4, (double*)(Result.m_T));

		return TransHomogeneous2Euler(Result);
	}

	//坐标系示教方法：三点（含原点）
	//CartTeach From Three Points With Base
	//返回值为CartRefSys函数中的参数Transition_p。
	tPoseEuler CartTeachThreeBase(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p)
	{
		tPose Pose;//1,2,3点确定的坐标系的变换量Transition_p
		CVector ox, oy, oz, v1, v2, v3, v12, v23;

		v1 = CVector(Point1_p.m_PositionCartesian);
		v2 = CVector(Point2_p.m_PositionCartesian);
		v3 = CVector(Point3_p.m_PositionCartesian);

		v12 = v2 - v1;
		ox = v12.Unit();
		v23 = v3 - v2;
		oy = v23 - (v23*ox)*ox;
		oy = oy.Unit();
		oz = ox.Cross(oy);

		Pose.m_PositionCartesian = Point1_p.m_PositionCartesian;
		Pose.m_PostureRotary.m_R[0][0] = ox.GetX();
		Pose.m_PostureRotary.m_R[0][1] = ox.GetY();
		Pose.m_PostureRotary.m_R[0][2] = ox.GetZ();
		Pose.m_PostureRotary.m_R[1][0] = oy.GetX();
		Pose.m_PostureRotary.m_R[1][1] = oy.GetY();
		Pose.m_PostureRotary.m_R[1][2] = oy.GetZ();
		Pose.m_PostureRotary.m_R[2][0] = oz.GetX();
		Pose.m_PostureRotary.m_R[2][1] = oz.GetY();
		Pose.m_PostureRotary.m_R[2][2] = oz.GetZ();

		return TransPose2Euler(Pose);
	}

	//坐标系示教方法：三点（无原点）
	//CartTeach From Three Points Without Base
	tPoseEuler CartTeachThreeNoBase(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p)
	{
		tPose Pose;//1,2,3点确定的坐标系的变换量Transition_p
		CVector ox, oy, oz, v1, v2, v3, v12, v23;
		LONG_REAL Length03;

		v1 = CVector(Point1_p.m_PositionCartesian);
		v2 = CVector(Point2_p.m_PositionCartesian);
		v3 = CVector(Point3_p.m_PositionCartesian);

		v12 = v2 - v1;
		ox = v12.Unit();
		v23 = v3 - v2;
		oy = v23 - (v23*ox)*ox;
		Length03 = oy.Length();
		oy = oy.Unit();
		oz = ox.Cross(oy);


		Pose.m_PositionCartesian = v3 - Length03*oy;
		Pose.m_PostureRotary.m_R[0][0] = ox.GetX();
		Pose.m_PostureRotary.m_R[0][1] = ox.GetY();
		Pose.m_PostureRotary.m_R[0][2] = ox.GetZ();
		Pose.m_PostureRotary.m_R[1][0] = oy.GetX();
		Pose.m_PostureRotary.m_R[1][1] = oy.GetY();
		Pose.m_PostureRotary.m_R[1][2] = oy.GetZ();
		Pose.m_PostureRotary.m_R[2][0] = oz.GetX();
		Pose.m_PostureRotary.m_R[2][1] = oz.GetY();
		Pose.m_PostureRotary.m_R[2][2] = oz.GetZ();

		return TransPose2Euler(Pose);
	}

	//坐标系示教方法：一点（保持姿态）
	tPoseEuler CartTeachOne(tPositionCartesian& Point1_p)
	{
		tPoseEuler PoseEuler;

		PoseEuler.m_PositionCartesian = Point1_p;
		PoseEuler.m_PostureEuler.m_A = 0;
		PoseEuler.m_PostureEuler.m_B = 0;
		PoseEuler.m_PostureEuler.m_C = 0;

		return PoseEuler;
	}


	//以下是工具坐标系示教
	//四点法,这四个点对应的是机器人第六轴末端对应的位姿。
	tPositionCartesian ToolFrameSetWithFourPoints(tPoseEuler& Point1_p, tPoseEuler& Point2_p, tPoseEuler& Point3_p, tPoseEuler& Point4_p)
	{
		TYPE_BOOL Flag1, Flag2, Flag3;
		tPositionCartesian Sum;
		int n = 0;

		tPoseHomogeneous P1Homo, P2Homo, P3Homo, P4Homo;
		LONG_REAL deltaR[3][3], deltaP[3], deltaRInv[9], PT[3];
		CVector P1, P2, P3, P4;

		int i, j;

		P1 = CVector(Point1_p.m_PositionCartesian);
		P2 = CVector(Point2_p.m_PositionCartesian);
		P3 = CVector(Point3_p.m_PositionCartesian);
		P4 = CVector(Point4_p.m_PositionCartesian);

		P1Homo = TransEuler2Homogeneous(Point1_p);
		P2Homo = TransEuler2Homogeneous(Point2_p);
		P3Homo = TransEuler2Homogeneous(Point3_p);
		P4Homo = TransEuler2Homogeneous(Point4_p);

		//1
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				deltaR[i][j] = P1Homo.m_T[i][j] - P2Homo.m_T[i][j];

		for (i = 0; i < 3; i++)
			deltaP[i] = P2Homo.m_T[i][3] - P1Homo.m_T[i][3];

		Flag1 = MatrixInv(deltaR[0], deltaRInv, 3);
		if (Flag1)
		{
			MatrixMul(deltaRInv, deltaP, 3, 3, 1, PT);
			n++;
			Sum = Sum + CVector(PT[0], PT[1], PT[2]);
		}

		//2
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				deltaR[i][j] = P1Homo.m_T[i][j] - P3Homo.m_T[i][j];

		for (i = 0; i < 3; i++)
			deltaP[i] = P3Homo.m_T[i][3] - P1Homo.m_T[i][3];

		Flag2 = MatrixInv(deltaR[0], deltaRInv, 3);
		if (Flag2)
		{
			MatrixMul(deltaRInv, deltaP, 3, 3, 1, PT);
			n++;
			Sum = Sum + CVector(PT[0], PT[1], PT[2]);
		}

		//3
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
				deltaR[i][j] = P1Homo.m_T[i][j] - P4Homo.m_T[i][j];

		for (i = 0; i < 3; i++)
			deltaP[i] = P4Homo.m_T[i][3] - P1Homo.m_T[i][3];

		Flag3 = MatrixInv(deltaR[0], deltaRInv, 3);
		if (Flag3)
		{
			MatrixMul(deltaRInv, deltaP, 3, 3, 1, PT);
			n++;
			Sum = Sum + CVector(PT[0], PT[1], PT[2]);
		}

		//求平均
		if (n > 0)
			Sum = Sum*(1 / n);
		else
			Sum = { 0, 0, 0 };

		return Sum;
	}


	//1POINT 6D 方法
	//mode_p选择当前位姿对应的是哪个轴，1：x， 2：y， 3：z。
	//direction_p:表示是沿坐标轴的正向还是负向,0:正向，1：负向
	//A:对应机器人姿态矩阵的第三行
	//B:对应工具坐标的姿态变换
	//C:有mode_p确定的姿态方向
	//AB=C，求A的伪逆乘以C得到B
	tPostureEuler ToolFrameSetWithOnePoint(tPoseEuler& PoseRobot_p, tPoseEuler& Point1_p, int mode_p, TYPE_BOOL direction_p)
	{
		tPose PoseRobot;
		LONG_REAL A[3], B[9], C[3], temp1[9], temp2[9], temp3[9];
		tPostureEuler PostureEuler;
		int i;

		PostureEuler.m_A = 0;
		PostureEuler.m_B = 0;
		PostureEuler.m_C = 0;

		if (mode_p == 1)
		{
			C[0] = 1;
			C[1] = 0;
			C[2] = 0;
			if (direction_p)
				C[0] = -1;
		}
		else if (mode_p == 2)
		{
			C[0] = 0;
			C[1] = 1;
			C[2] = 0;
			if (direction_p)
				C[1] = -1;
		}
		else if (mode_p == 3)
		{
			C[0] = 0;
			C[1] = 0;
			C[2] = 1;
			if (direction_p)
				C[2] = -1;
		}
		else//error
		{
			return PostureEuler;
		}

		PoseRobot = TransEuler2Pose(PoseRobot_p);
		for (i = 0; i < 3; i++)
			A[i] = PoseRobot.m_PostureRotary.m_R[mode_p - 1][i];

		MatrixMul(A, A, 3, 1, 3, temp1);
		MatrixInv(temp1, temp2, 3);
		MatrixMul(temp2, A, 3, 3, 1, temp3);
		MatrixMul(temp3, C, 3, 1, 3, B);


		tPoseHomogeneous PoseHomo_temp;
		tPositionCartesian PositionCartesian_temp;
		RP2HomeMatrix(B,
			(double*)(PositionCartesian_temp),
			(double*)(PoseHomo_temp.m_T));
		Matrix_RPY((double*)(PoseHomo_temp.m_T),
			&(PostureEuler.m_A),
			&(PostureEuler.m_B),
			&(PostureEuler.m_C));

		return PostureEuler;
	}



	CCoordinate::CCoordinate()
	{
		int i, j;
		m_Pose.m_PositionCartesian.m_X = 0;
		m_Pose.m_PositionCartesian.m_Y = 0;
		m_Pose.m_PositionCartesian.m_Z = 0;
		for (i = 0; i < 3; i++)
			for (j = 0; j < 3; j++)
			{
				if (i != j)
					m_Pose.m_PostureRotary.m_R[i][j] = 0;
				else
					m_Pose.m_PostureRotary.m_R[i][j] = 1;
			}

		m_PoseEuler.m_PositionCartesian.m_X = 0;
		m_PoseEuler.m_PositionCartesian.m_Y = 0;
		m_PoseEuler.m_PositionCartesian.m_Z = 0;
		m_PoseEuler.m_PostureEuler.m_A = 0;
		m_PoseEuler.m_PostureEuler.m_B = 0;
		m_PoseEuler.m_PostureEuler.m_C = 0;
	}

	CCoordinate::CCoordinate(tPose Pose_p)
	{
		m_Pose = Pose_p;
		m_PoseEuler = TransPose2Euler(Pose_p);
	}

	CCoordinate::CCoordinate(tPoseEuler PoseEuler_p)
	{
		m_Pose = TransEuler2Pose(PoseEuler_p);
		m_PoseEuler = PoseEuler_p;
	}

	CCoordinate::CCoordinate(tPoseHomogeneous PoseHomogeneous_p)
	{
		m_Pose = TransHomogeneous2Pose(PoseHomogeneous_p);
		m_PoseEuler = TransHomogeneous2Euler(PoseHomogeneous_p);
	}

	CCoordinate::~CCoordinate()
	{}


	tPoseHomogeneous CCoordinate::Homogeneous()
	{
		return TransPose2Homogeneous(m_Pose);
	}

	CCoordinate CCoordinate::Transit(tPoseEuler PoseEuler_p)
	{
		tPoseEuler PoseEuler;
		PoseEuler = CartRefSys(this->m_PoseEuler, PoseEuler_p);
		return CCoordinate(PoseEuler);
	}

	CCoordinate CCoordinate::Transit(tPose Pose_p)
	{
		tPoseEuler PoseEuler;
		PoseEuler = CartRefSys(this->m_PoseEuler, TransPose2Euler(Pose_p));
		return CCoordinate(PoseEuler);
	}

}