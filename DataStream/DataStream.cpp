#include "DataStream.h"
#include "DataStruct.h"
#include "QByteArray"
#include "QDataStream"
#include "..\TeachingBox\DataStruct.h"



DataStream::DataStream()
	:m_byteArray(new QByteArray())
	, m_dataStream(new QDataStream(m_byteArray, QIODevice::ReadWrite))
{

}


DataStream::~DataStream()
{
	delete m_byteArray;
	delete m_dataStream;
}

QDataStream* DataStream::GetOriginalDataStream() const
{
	return m_dataStream;
}

int DataStream::Length() const
{
	return m_dataStream->device()->size();
}

int DataStream::ReadRawBytes(char *c, unsigned int length) const
{
	return m_dataStream->readRawData(c, length);
}

int DataStream::WriteRawBytes(const char* c, unsigned int length)
{
	return m_dataStream->writeRawData(c, length);
}

void DataStream::Seek(int pos)
{
	m_dataStream->device()->seek(pos);
}

DataStream& DataStream::operator>>(int& value)
{
	*m_dataStream >> value;

	return *this;
}

DataStream& DataStream::operator>>(double& value)
{
	*m_dataStream >> value;

	return *this;
}

DataStream& DataStream::operator>>(tAxesAllPositions& value)
{
	for (auto& v:value.m_AxisPosition)
	{
		*m_dataStream >> v;
	}

	return *this;
}


DataStream& DataStream::operator>>(tTeachCmdAttribute& value)
{
	*m_dataStream >> value.m_length;
	*m_dataStream >> value.m_ID;
	*m_dataStream >> value.m_type;
	*m_dataStream >> value.m_LineNumber;
	*m_dataStream >> value.m_programId;

	return *this;
}

DataStream& DataStream::operator>>(tDynamicConstraint& value)
{
	*m_dataStream >> value.m_Velocity;
	*m_dataStream >> value.m_Acceleration;
	*m_dataStream >> value.m_Deceleration;
	*m_dataStream >> value.m_PostureVelocity;
	*m_dataStream >> value.m_PostureAcceleration;
	*m_dataStream >> value.m_PostureDeceleration;

	return *this;
}

DataStream& DataStream::operator>>(tOverlapConstraint& value)
{
	*m_dataStream >> value.m_TransitionMode;
	*m_dataStream >> value.m_TransitionParameter;

	return *this;
}

DataStream& DataStream::operator>>(tMovLParam& value)
{
	*this >> value.m_Destination;
	*this >> value.m_Dynamic;
	*this >> value.m_Overlap;

	return *this;
}


DataStream& DataStream::operator>>(tPoseEuler& value)
{
	*this >> value.m_PositionCartesian;
	*this >> value.m_PostureEuler;

	return *this;
}

DataStream& DataStream::operator>>(tPositionCartesian& value)
{
	*m_dataStream >> value.m_X;
	*m_dataStream >> value.m_Y;
	*m_dataStream >> value.m_Z;

	return *this;
}

DataStream& DataStream::operator>>(tPostureEuler& value)
{
	*m_dataStream >> value.m_A;
	*m_dataStream >> value.m_B;
	*m_dataStream >> value.m_C;

	return *this;
}

DataStream& DataStream::operator>>(tMovCParam& value)
{
	*this >> value.m_AuxPoint;
	*this >> value.m_EndPoint;
	*this >> value.m_Dynamic;
	*this >> value.m_Overlap;
	return *this;
}

DataStream& DataStream::operator<<(int value)
{
	*m_dataStream << value;

	return *this;
}

DataStream& DataStream::operator<<(double value) 
{
	*m_dataStream << value;

	return *this;
}

DataStream& DataStream::operator<<(const tAxesAllPositions& value)
{
	for (auto& v : value.m_AxisPosition)
	{
		*m_dataStream << v;
	}

	return *this;
}

DataStream& DataStream::operator<<(const tTeachCmdAttribute& value)
{
	*m_dataStream << value.m_length;
	*m_dataStream << value.m_ID;
	*m_dataStream << value.m_type;
	*m_dataStream << value.m_LineNumber;
	*m_dataStream << value.m_programId;

	return *this;
}

DataStream& DataStream::operator<<(const tDynamicConstraint& value)
{
	*m_dataStream << value.m_Velocity;
	*m_dataStream << value.m_Acceleration;
	*m_dataStream << value.m_Deceleration;
	*m_dataStream << value.m_PostureVelocity;
	*m_dataStream << value.m_PostureAcceleration;
	*m_dataStream << value.m_PostureDeceleration;

	return *this;
}

DataStream& DataStream::operator<<(const tOverlapConstraint& value)
{
	*m_dataStream << value.m_TransitionMode;
	*m_dataStream << value.m_TransitionParameter;

	return *this;
}

DataStream& DataStream::operator<<(const tMovLParam& value)
{
	*this << value.m_Destination;
	*this << value.m_Dynamic;
	*this << value.m_Overlap;

	return *this;
}


DataStream& DataStream::operator<<(const tPoseEuler& value)
{
	*this << value.m_PositionCartesian;
	*this << value.m_PostureEuler;

	return *this;
}

DataStream& DataStream::operator<<(const tPositionCartesian& value)
{
	*m_dataStream << value.m_X;
	*m_dataStream << value.m_Y;
	*m_dataStream << value.m_Z;

	return *this;
}

DataStream& DataStream::operator<<(const tPostureEuler& value)
{
	*m_dataStream << value.m_A;
	*m_dataStream << value.m_B;
	*m_dataStream << value.m_C;

	return *this;
}

DataStream& DataStream::operator<<(const tMovCParam& value)
{
	*this << value.m_AuxPoint;
	*this << value.m_EndPoint;
	*this << value.m_Dynamic;
	*this << value.m_Overlap;
	return *this;
}

