#ifndef _TARGET_MATH_H_
#define _TARGET_MATH_H_

	#include "Target_GlobalDefine.h"
	#include "matrix.h"
	#include <math.h>
	#include "CVector.h"
	

	#define REAL_ZERO				0.0000001		//+0
	#define REAL_ZERO_MINUS			-0.0000001		//-0

	#define Equal(x,y)			(fabs((x)-(y)) < REAL_ZERO)	// ==
	#define Big(x,y)			((x)-(y) > REAL_ZERO)	// >
	#define BigEqual(x,y)		((x)-(y) > REAL_ZERO_MINUS)	// >=
	#define Small(x,y)			((x)-(y) < REAL_ZERO_MINUS)		// <
	#define SmallEqual(x,y)		((x)-(y) < REAL_ZERO)	// <=



	#define PI 3.141592653589793
	#define DEGREE2RAD 0.01745329252
	#define RAD2DEGREE 57.2957795131

	#define	Max(a,b)	((a)>(b)?(a):(b))
	#define	Min(a,b)	((a)>(b)?(b):(a))





#endif	//_TARGET_MATH_H_

