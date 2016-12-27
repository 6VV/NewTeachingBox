#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "Target_GlobalDefine.h"
#include "Target_Math.h"

namespace Coor{
	//typedef struct
	//{
	//	LONG_REAL m_X;
	//	LONG_REAL m_Y;
	//	LONG_REAL m_Z;
	//
	//}tCartesian3;

	typedef struct
	{
		LONG_REAL m_R[3][3];

	}tRotary33;



	class CVector
	{
	public:
		LONG_REAL m_X;
		LONG_REAL m_Y;
		LONG_REAL m_Z;
		LONG_REAL m_P[3];//仅在转换为LONG_REAL*类型时使用。

	public:
		CVector();
		CVector(LONG_REAL x_p, LONG_REAL y_p, LONG_REAL z_p);
		/*CVector(LONG_REAL Position[3]);*/
		CVector(const CVector& Vector_p);
		~CVector();

		CVector& operator= (const CVector& Vector_p);
		CVector operator+ (const CVector& B) const;
		CVector operator- (const CVector B) const;
		CVector operator- () const;
		CVector operator* (LONG_REAL n) const;
		friend CVector operator*(LONG_REAL n, const CVector & A);
		LONG_REAL operator* (const CVector B) const;// 点乘

		TYPE_BOOL IsZero() const;
		LONG_REAL Length() const;
		CVector Cross(const CVector & B) const;
		CVector Unit() const;

		operator LONG_REAL*();

		LONG_REAL GetX() const;
		LONG_REAL GetY() const;
		LONG_REAL GetZ() const;
	};

}

#endif//_VECTOR_H_
