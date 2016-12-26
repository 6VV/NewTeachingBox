#ifndef _TEACHING_BOX_DATA_STRUCT_H_
#define _TEACHING_BOX_DATA_STRUCT_H_

enum CmdAttributeType
{
	CMD_ATTRIBUTE_NORMAL_COMMAND,
	CMD_ATTRIBUTE_NORMAL_COMMAND_FEEDBACK,
	CMD_ATTRIBUTE_SPECIAL_COMMAND,
	CMD_ATTRIBUTE_SPECIAL_COMMAND_FEEDBACK,
	CMD_ATTRIBUTE_ROBOT_STATE,
};

//单条指令的属性
struct tTeachCmdAttribute
{
	int m_length;
	int m_ID;//命令ID
	int m_type;	/*类型*/
	int m_LineNumber;//行号
	int m_programId;	/*地址*/
	//	tTeachCmdState m_State;//命令状态
};

const int LOCK_LENGTH = 1;
const int COMMAND_HEAD_LENGTH = LOCK_LENGTH + sizeof(tTeachCmdAttribute);
const int COMMAND_MAX_LENGTH = 1024;
const int AXIS_SIZE = 6;

/*命令Id*/
enum CommandId
{
	MOVL = 2000,
	MOVX = 2001,
	MOVY = 2002,
	MOVZ = 2003,
	MOVC = 2004,
	END = 4000,

	MOVE_AXIS_PLUS_1 = 5007,
	MOVE_AXIS_PLUS_2 = 5008,
	MOVE_AXIS_PLUS_3 = 5009,
	MOVE_AXIS_PLUS_4 = 5010,
	MOVE_AXIS_PLUS_5 = 5011,
	MOVE_AXIS_PLUS_6 = 5012,
	MOVE_AXIS_PLUS_7 = 5013,
	MOVE_AXIS_PLUS_8 = 5014,
	MOVE_AXIS_PLUS_9 = 5015,
	MOVE_AXIS_PLUS_10 = 5016,

	MOVE_AXIS_MINUS_1 = 5017,
	MOVE_AXIS_MINUS_2 = 5018,
	MOVE_AXIS_MINUS_3 = 5019,
	MOVE_AXIS_MINUS_4 = 5020,
	MOVE_AXIS_MINUS_5 = 5021,
	MOVE_AXIS_MINUS_6 = 5022,
	MOVE_AXIS_MINUS_7 = 5023,
	MOVE_AXIS_MINUS_8 = 5024,
	MOVE_AXIS_MINUS_9 = 5025,
	MOVE_AXIS_MINUS_10 = 5026,

	STOP_MOVE = 5027,

	STOP_EXECUTE=5031,

	ROBOT_POSITION=6001,

	NORMAL_COMMAND_FEEDBACK = 6009,

	NORMAL_COMMAND = 9001,
};

/*位置变量*/
struct tAxesAllPositions
{
	double m_AxisPosition[AXIS_SIZE];

};

/*速度约束*/
struct tDynamicConstraint{
	//位置约束
	double m_Velocity;
	double m_Acceleration;
	double m_Deceleration;

	//姿态约束
	double m_PostureVelocity;
	double m_PostureAcceleration;
	double m_PostureDeceleration;
};

/*相邻运动指令间的过度模式*/
enum tTransitionMode
{
	kTransitionModeAbsolute = 0,
	kTransitionModeRelative = 1,

};

/*过渡区域约束*/
struct tOverlapConstraint
{
	//过渡模式和参数
	int m_TransitionMode;	/*此处采用int而非枚举，是为了在数据库存储时方便*/
	double m_TransitionParameter;
};

/*三维坐标点位置*/
struct tPositionCartesian
{
	double m_X;
	double m_Y;
	double m_Z;
};

/*姿态旋转矩阵*/
struct tPostureRotary
{
	double m_R[3][3];

};

/*点的位置和姿态*/
struct tPose
{
	tPostureRotary m_PostureRotary;
	tPositionCartesian m_PositionCartesian;

};

struct tPostureEuler
{
	double m_A;
	double m_B;
	double m_C;

};


struct tPoseEuler
{
	tPositionCartesian m_PositionCartesian;
	tPostureEuler m_PostureEuler;

};

/*位置齐次变换*/
struct tPoseHomogeneous
{
	double m_T[4][4];
};

/////////////////////////////////////////////////////
//velocity

/*6个轴的速度*/
struct tAxesAllVelocities
{
	double m_AxisVelocity[6];

};

/*三维坐标点速度*/
struct tVelocityCartesian
{
	double m_Vx;
	double m_Vy;
	double m_Vz;

};

/*速度旋转矩阵*/
struct tVelocityRotary
{
	double m_R[3][3];

};

/*点的速度和姿态速度*/
struct tPoseVelocity
{
	tVelocityRotary m_PostureRotary;
	tVelocityCartesian m_PositionCartesian;

};

/*速度齐次变换*/
struct tVelocityHomogeneous
{
	double m_T[4][4];

};


/////////////////////////////////////////////////////
//Acceleration

/*6个轴的加速度*/
struct tAxesAllAccelerations
{
	double m_AxisAcceleration[6];

};

/*三维坐标点加速度*/
struct tAccelerationCartesian
{
	double m_Vx;
	double m_Vy;
	double m_Vz;

};

/*加速度旋转矩阵*/
struct tAccelerationRotary
{
	double m_R[3][3];

};

/*点的加速度和姿态加速度*/
struct tPoseAcceleration
{
	tAccelerationRotary m_PostureRotary;
	tAccelerationCartesian m_PositionCartesian;

};

/*加速度齐次变换*/
struct tAccelerationHomogeneous
{
	double m_T[4][4];

};


/////////////////////////////////////////////////////////////////
//用户指令参数

/*直线运动规划数据结构*/
struct tMovLParam
{
	tAxesAllPositions m_Destination;//目标位置

	tDynamicConstraint m_Dynamic;

	tOverlapConstraint m_Overlap;
};


struct tMovXParam
{
	tAxesAllPositions m_Destination;//目标位置
	tDynamicConstraint m_Dynamic;
	tOverlapConstraint m_Overlap;

};

struct tMovYParam
{
	tAxesAllPositions m_Destination;//目标位置
	tDynamicConstraint m_Dynamic;
	tOverlapConstraint m_Overlap;
};

struct tMovZParam
{
	tAxesAllPositions m_Destination;//目标位置
	tDynamicConstraint m_Dynamic;
	tOverlapConstraint m_Overlap;
};



enum tCircMode
{
	kCircModeBorder = 0,//设定圆弧边上三点
	kCircModeCenter = 1,//设定圆心和末端点
	kCircModeRadius = 2,//设定圆弧平面、半径和末端点

};

enum tPathChoice
{
	kPathChoiceClockwise = 0,//顺时针
	kPathChoioceCounterClockwise = 1,//逆时针

};

struct tMovCParam
{
	tAxesAllPositions m_AuxPoint;//参数位置
	tAxesAllPositions m_EndPoint;//目标位置
	tPathChoice m_PathChoice;//顺时针，逆时针

	tDynamicConstraint m_Dynamic;
	tOverlapConstraint m_Overlap;
};


//////////////////////////////////////////////////////////
//用于通信

//typedef enum
//{
//	kTeachCmdStateWaiting = 0,
//	kTeachCmdStateRunning = 1,
//	kTeachCmdStateFinished = 2,
//	kTeachCmdStateError = 10,
//
//}tTeachCmdState;//单条指令的状态，已废弃
//
//typedef enum
//{
//	kTeachBufferStateIdle = 0,
//	kTeachBufferStateFilled = 1,//已填充
//	kTeachBufferStateRunning = 2,//正在运行
//	kTeachBufferStateHolding = 3,//暂停
//	kTeachBufferStateError = 10,
//
//}tTeachBufferState;//整个buffer的状态,已废弃


////整个buffer的属性
//typedef struct
//{
//	tTeachBufferState m_State;
//	int m_LengthAll;	//buffer的总长
//	int m_LengthEmpty;	//空的长度
//	int m_CurrentCmd;	//当前在执行的指令
//
//
//}tTeachBufferAttribute;

//示教器要设置的数据
enum tTeachSetParam
{
	JLimitPos = 0,//关节角正限位
	JLimitNeg = 1,//关节角负限位
	velLimit = 2,//关节速度
	accLimit = 3,//加速度
	jerkLimit = 4,//加加速度


};



enum tControllerError
{
	//TODO:待定义

};

enum tTeachBoxError
{
	//TODO:待定义

};



//读取数字IO
typedef struct
{
	char m_DigitalIOData;

}tReadDigitalInputParam;



//读取模拟IO
typedef struct
{
	double m_AnalogIOData;

}tReadAnalogInputParam;


typedef enum
{
	kRobotStateDisabled = 0,
	kRobotStateStandby = 1,
	kRobotStateMoving = 2,
	kRobotStateStopping = 4,
	kRobotStateErrorStop = 5,
	kRobotStateHoming = 6,

}tRobotState;


//机器人当前状态信息
typedef struct
{
	tRobotState m_RobotState;

}tRobotStateInfo;


#endif