
#include "CVector.h"
#include "Target_Math.h"



CVector::CVector()
{
	m_X = 0;
	m_Y = 0;
	m_Z = 0;
}
CVector::CVector(LONG_REAL x_p, LONG_REAL y_p, LONG_REAL z_p)
{
	m_X = x_p;
	m_Y = y_p;
	m_Z = z_p;
}
//CVector::CVector(LONG_REAL Position[3])
//{
//	m_X = Position[0];
//	m_Y = Position[1];
//	m_Z = Position[2];
//}

CVector::CVector(CVector& Vector_p)
{
	m_X = Vector_p.m_X;
	m_Y = Vector_p.m_Y;
	m_Z = Vector_p.m_Z;
}

CVector::~CVector()
{

}

CVector& CVector::operator= (const CVector& Vector_p)
{
	m_X = Vector_p.m_X;
	m_Y = Vector_p.m_Y;
	m_Z = Vector_p.m_Z;

	return *this;
}

CVector CVector::operator+ (const CVector& B) const
{
	return CVector(m_X + B.m_X, m_Y + B.m_Y, m_Z + B.m_Z);
}
CVector CVector::operator- (const CVector B) const
{
	return CVector(m_X - B.m_X, m_Y - B.m_Y, m_Z - B.m_Z);
}
CVector CVector::operator- () const
{
	return CVector(-m_X, -m_Y, -m_Z);
}
CVector CVector::operator* (LONG_REAL n) const
{
	return CVector(m_X*n, m_Y*n, m_Z*n);
}

CVector operator*(LONG_REAL n, const CVector & A)
{
	return CVector(A.m_X*n, A.m_Y*n, A.m_Z*n);
}

LONG_REAL CVector::operator* (const CVector B) const
{
	return (m_X*B.m_X + m_Y*B.m_Y + m_Z*B.m_Z);	
}

TYPE_BOOL CVector::IsZero() const
{
	if (Equal(m_X, 0) && Equal(m_Y, 0) && Equal(m_Z, 0))
		return TRUE;
	else
		return FALSE;
}
LONG_REAL CVector::Length() const
{
	return sqrt(m_X*m_X+m_Y*m_Y+m_Z*m_Z);
}
CVector CVector::Cross(const CVector & B) const
{
	CVector Result;
	Result.m_X = m_Y*B.m_Z - m_Z*B.m_Y;
	Result.m_Y = m_Z*B.m_X - m_X*B.m_Z;
	Result.m_Z = m_X*B.m_Y - m_Y*B.m_X;

	return Result;
}
CVector CVector::Unit() const
{
	LONG_REAL L;
	CVector Result;
	L = sqrt(m_X*m_X + m_Y*m_Y + m_Z*m_Z);
	if (Equal(L, 0))
	{
		Result.m_X = 0;
		Result.m_Y = 0;
		Result.m_Z = 0;
	}
	else
	{
		Result.m_X = m_X/L;
		Result.m_Y = m_Y/L;
		Result.m_Z = m_Z/L;
	}

	return Result;
}


CVector::operator LONG_REAL*()
{
	m_P[0] = m_X;
	m_P[1] = m_Y;
	m_P[2] = m_Z;

	return ((LONG_REAL*)(m_P));
}

LONG_REAL CVector::GetX() const
{
	return m_X;
}
LONG_REAL CVector::GetY() const
{
	return m_Y;
}
LONG_REAL CVector::GetZ() const
{
	return m_Z;
}




