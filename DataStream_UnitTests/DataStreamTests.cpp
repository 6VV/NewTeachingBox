#include "DataStreamTests.h"
#include "..\DataStream\DataStream.h"
#include "..\TeachingBox\DataStruct.h"
#include "QByteArray"
#include "QDataStream"



TEST_F(DataStreamTests, Test_Int)
{
	DataStream stream;
	stream << 1;
	int i = 0;
	stream.Seek(0);
	stream >> i;

	ASSERT_EQ(1, i);
}

TEST_F(DataStreamTests, Test_Double)
{
	DataStream stream;
	stream << 1.1;
	double i = 0;
	stream.Seek(0);
	stream >> i;

	ASSERT_EQ(1.1, i);
}

TEST_F(DataStreamTests, Test_tTeachCmdAttribute)
{
	DataStream stream;
	tTeachCmdAttribute source;
	source.m_ID = 1;
	source.m_length = 2;
	source.m_LineNumber = 3;
	source.m_programId = 4;
	source.m_type = 5;
	stream << source;

	tTeachCmdAttribute i{};
	stream.Seek(0);
	stream >> i;

	ASSERT_EQ(1, i.m_ID);
	ASSERT_EQ(2, i.m_length);
	ASSERT_EQ(3, i.m_LineNumber);
	ASSERT_EQ(4, i.m_programId);
	ASSERT_EQ(5, i.m_type);

}

TEST_F(DataStreamTests, Test_tAxesAllPositions)
{
	DataStream stream;
	tAxesAllPositions source;
	int i = 0;
	for (auto& v:source.m_AxisPosition)
	{
		v = i++;
	}
	stream << source;

	tAxesAllPositions result{};
	stream.Seek(0);
	stream >> result;

	for (int j = 0; j < 6;++j)
	{
		ASSERT_EQ(source.m_AxisPosition[j], result.m_AxisPosition[j]);
	}

}

TEST_F(DataStreamTests, Test_tDynamicConstraint)
{
	DataStream stream;
	tDynamicConstraint source;
	source.m_Velocity = 1;
	source.m_Acceleration = 2;
	source.m_Deceleration = 3;
	source.m_PostureVelocity = 4;
	source.m_PostureAcceleration = 5;
	source.m_PostureDeceleration = 6;
	stream << source;

	tDynamicConstraint result{};
	stream.Seek(0);
	stream >> result;

	ASSERT_EQ(source.m_Velocity, result.m_Velocity);
	ASSERT_EQ(source.m_Acceleration, result.m_Acceleration);
	ASSERT_EQ(source.m_Deceleration, result.m_Deceleration);
	ASSERT_EQ(source.m_PostureVelocity, result.m_PostureVelocity);
	ASSERT_EQ(source.m_PostureAcceleration, result.m_PostureAcceleration);
	ASSERT_EQ(source.m_PostureDeceleration, result.m_PostureDeceleration);
}

TEST_F(DataStreamTests, Test_tOverlapConstraint)
{
	DataStream stream;
	tOverlapConstraint source;
	source.m_TransitionMode = 1;
	source.m_TransitionParameter = 2;
	stream << source;

	tOverlapConstraint result{};
	stream.Seek(0);
	stream >> result;

	ASSERT_EQ(source.m_TransitionMode, result.m_TransitionMode);
	ASSERT_EQ(source.m_TransitionParameter, result.m_TransitionParameter);
}

TEST_F(DataStreamTests, Test_tMovLParam)
{
	DataStream stream;
	tMovLParam source;
	source.m_Destination = tAxesAllPositions{ { 1, 2, 3, 4, 5, 6 } };
	source.m_Dynamic = tDynamicConstraint{1,2,3,4,5,6};
	source.m_Overlap = tOverlapConstraint{ 1, 2};
	stream << source;

	tMovLParam result{};
	stream.Seek(0);
	stream >> result;

	for (int i = 0; i < 6;++i)
	{
		ASSERT_EQ(source.m_Destination.m_AxisPosition[i], result.m_Destination.m_AxisPosition[i]);
	}
	ASSERT_EQ(source.m_Dynamic.m_Acceleration, result.m_Dynamic.m_Acceleration);
	ASSERT_EQ(source.m_Dynamic.m_Deceleration, result.m_Dynamic.m_Deceleration);
	ASSERT_EQ(source.m_Dynamic.m_Velocity, result.m_Dynamic.m_Velocity);
	ASSERT_EQ(source.m_Dynamic.m_PostureVelocity, result.m_Dynamic.m_PostureVelocity);
	ASSERT_EQ(source.m_Dynamic.m_PostureAcceleration, result.m_Dynamic.m_PostureAcceleration);
	ASSERT_EQ(source.m_Dynamic.m_PostureDeceleration, result.m_Dynamic.m_PostureDeceleration);

	ASSERT_EQ(source.m_Overlap.m_TransitionMode, result.m_Overlap.m_TransitionMode);
	ASSERT_EQ(source.m_Overlap.m_TransitionParameter, result.m_Overlap.m_TransitionParameter);

}

TEST_F(DataStreamTests, Test_Seek)
{
	DataStream stream;
	stream << 1 << 2;
	stream.Seek(0);
	stream << 3;
	stream << 4;

	stream.Seek(0);
	int i1;
	int i2;
	stream >> i1;
	stream >> i2;
	ASSERT_EQ(3, i1);
	ASSERT_EQ(4, i2);

}

TEST_F(DataStreamTests, Test_ReadRawBytes)
{
	DataStream stream;
	stream << 1 << 2;
	stream.Seek(0);
	char* c = new char[100];
	int length = stream.Length();
	int dataReadNum=stream.ReadRawBytes(c, length);
	ASSERT_TRUE(dataReadNum != -1);

	QByteArray array;
	QDataStream dataStream(&array,QIODevice::ReadWrite);
	int dataWriteNum=dataStream.writeRawData(c, length);
	ASSERT_TRUE(dataWriteNum != -1);
	delete[] c;

	int i1;
	int i2;
	dataStream.device()->seek(0);
	dataStream >> i1 >> i2;
	ASSERT_EQ(1, i1);
	ASSERT_EQ(2, i2);

}

TEST_F(DataStreamTests, Test_WriteRawBytes)
{
	QByteArray array;
	QDataStream dataStream(&array, QIODevice::ReadWrite);
	dataStream << 1 << 2;
	dataStream.device()->seek(0);
	char* c = new char[100];
	int length = dataStream.device()->size();
	int dataReadNum = dataStream.readRawData(c, length);
	ASSERT_TRUE(dataReadNum != -1);

	DataStream stream;
	int dataWriteNum = stream.WriteRawBytes(c, length);
	ASSERT_TRUE(dataWriteNum != -1);
	delete[] c;

	int i1;
	int i2;
	stream.Seek(0);
	stream >> i1 >> i2;
	ASSERT_EQ(1, i1);
	ASSERT_EQ(2, i2);

}

TEST_F(DataStreamTests, Test_MovL)
{
	tTeachCmdAttribute attribute;
	attribute.m_type = CmdAttributeType::CMD_ATTRIBUTE_NORMAL_COMMAND;
	attribute.m_ID = CommandId::MOVL;
	attribute.m_LineNumber = 1;
	attribute.m_programId = 2;

	tMovLParam source;
	source.m_Destination = tAxesAllPositions{ { 1, 2, 3, 4, 5, 6 } };
	source.m_Dynamic = tDynamicConstraint{ 1, 2, 3, 4, 5, 6 };
	source.m_Overlap = tOverlapConstraint{ 1, 2 };

	DataStream dataStream;
	dataStream << attribute;
	dataStream << source;
	attribute.m_length = dataStream.Length();
	dataStream.Seek(0);
	dataStream << attribute;
	dataStream.Seek(0);

	static const int LENGTH = 1024;
	char result[LENGTH];

	result[0] = '\0';
	int readLength=dataStream.ReadRawBytes(result + 1, dataStream.Length());
	ASSERT_TRUE(readLength!=-1);

	DataStream resultStream;
	int writeLength=resultStream.WriteRawBytes(result, COMMAND_HEAD_LENGTH);
	ASSERT_TRUE(writeLength != -1);

	resultStream.Seek(1);
	tTeachCmdAttribute resultAttribute;
	dataStream >> resultAttribute;

	ASSERT_EQ(attribute.m_ID, resultAttribute.m_ID);

}
