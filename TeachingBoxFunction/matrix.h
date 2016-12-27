/**********************************************************************************************
*
* This file created  according to the invese kinematics method invented  by JING Fengshui
*
* revised history
* ver 1.0  created by JING Fengshui, 2010/6/6
* Institute of Automation, Chinese Academy of Sciences
* ALL rights reserved
*/// matrix operation

#ifndef _MATRIX_H_
#define _MATRIX_H_

namespace Coor{
	//#ifdef __cplusplus
	//extern "C" {
	//#endif
	/************** matrix operation ********************************/
	void MatrixAdd(const double a[], const double b[], int m, int n, double c[]);

	/**************REAL MATRIX MULTIPLICATION********************************/
	void MatrixMul(const double a[], const double b[], int m, int n, int k, double c[]);


	/************** MATRIX inversion********************************/
	int MatrixInv(const double s[], double a[], int n);//n No more than 6£¬i.e.rank 2--6
	void HomeMatrixInv(const double hm1[], double hm2[]);
	void RP2HomeMatrix(const double R[], const double P[], double hm[]);
	void HomeMatrix2RP(const double hm[], double R[], double P[]);

	double  MatrixDet(const double M[], int n);

	void MatrixT(const double s[], double T[], int n);//turn transform n No more than 6£¬i.e.rank 2--6

	/*-------- HomoMatrix Position translation and rotation--------*/
	void Move_XYZ_Matrix(const double dx, const double dy, const double dz, double theMatrix[]);

	void Rote_X_Matrix(const double x_angle, double theMatrix[]);


	void Rote_Y_Matrix(const double y_angle, double theMatrix[]);


	void Rote_Z_Matrix(const double z_angle, double theMatrix[]);

	void Roll_Pitch_Yaw(const double x_angle, const double y_angle, const double z_angle, double theMatrix[]);
	//WARNING: this function is special designed in the folowing sequence
	//first rotate around x-axis, then y-axis,finally z-axis

	//the following function form a conversion matrix Aij from px,py,pz,and roll,pitch yaw


	/* call Acb=inv(Ab)*Ac;  or Ac=Ab*Acb ,*/
	//i.e.the transform matrix from c coor to b coor
	int Cal_Acb(const double Ab[], const double Ac[], double Acb[]);

	//this function calculate the roll pitch yaw angles from the conversion matrix
	void Matrix_RPY(const double A[], double *roll, double *pitch, double *yaw);

	/*-------------------------------------------------------------------------------*/
	/************ KINEMATICS IN VECTOR SPACE **************************************/
	/*VecCross::usage =
			"VecCross[vec_List]
			gives the  matrix vec¡Á ,
			Inputs: vec--a vector in
			Outputs:matrix vec¡Á
			*/
	void VecCross(const double vec[], double matrix[][3]);

	void VecCross_minus(const double vec[], double matrix[][3]);

	void AxisAngle2R(const double v[], const double angle, double R[][3]);
	void R2AxisAngle(const double R[][3], double v[], double *angle);

	/*IdentityMatrix[3] + Vect2Mat[v]*Sin[\[Theta]] +
	 Vect2Mat[v].Vect2Mat[v]*(1 - Cos[\[Theta]])*/

	/*
	xrot::usage =
	"
	xrot[E_List]:gives a 6¡Á6 transform matrix from B to A,
	based on the 3¡Á3rotation matrix E from B to A

	xrot[E_List]:=Block[{xe=Table[0,{i,1,6},{j,1,6}]},xe[[1;;3,1;;3]]=E;xe[[4;;6,4;;6]]=E;xe]
	*/
	void xrot(const double E[][3], double matrix[][6]);

	/*
	xlt::usage =
	"
	xlt[r_List]:gives a 6¡Á6 transform matrix from A to B,
	based on the 1¡Á3 transformation matrix E from B to A,or a transform vector expressed in A coordinate
	compare with xlt and xrot, see the differences
	"
	xlt[r_List]:=Block[{xl=Table[0,{i,1,6},{j,1,6}]},
	xl[[1;;3,1;;3]]=IdentityMatrix [3];xl[[4;;6,4;;6]]=IdentityMatrix [3];
	xl[[4;;6,1;;3]]=-VecCross[r];xl]
	*/
	void xlt(const double r[], double matrix[][6]);




	/*
	rotx::usage =
	"rotx[\[Theta]_]
	gives the motion spatial vector coordinate transform matrix from the fixed frame
	to the rotation frame,
	Inputs: \[Theta]--the rotation angle about the x-axis of the fixed frame
	Outputs:transform matrix from the fixed frame to the rotation frame
	"
	roty::usage =
	"roty[\[Theta]_]
	gives the motion spatial vector coordinate transform matrix from the fixed frame
	to the rotation frame,
	Inputs: \[Theta]--the rotation angle about the y-axis of the fixed frame
	Outputs:transform matrix from the fixed frame to the rotation frame
	"
	rotz::usage =
	"rotz[\[Theta]_]
	gives the motion spatial vector coordinate transform matrix from the fixed frame
	to the rotation frame,
	Inputs: \[Theta]--the rotation angle about the z-axis of the fixed frame
	Outputs:transform matrix from the fixed frame to the rotation frame
	"

	*/

	void rotx3(const double x_angle, double rotmatrix[][3]);

	void roty3(const double y_angle, double rotmatrix[][3]);

	void rotz3(const double z_angle, double rotmatrix[][3]);

	void rotx6(const double x_angle, double matrix[][6]);

	void roty6(const double y_angle, double matrix[][6]);

	void rotz6(const double z_angle, double matrix[][6]);

	/*
	XAB::usage =
	"XAB[E_List,r_List]
	gives the motion spatial vector coordinate transform matrix from the fixed frame A
	to the Moving frame B,
	Inputs: E--the 3¡Á3 rotation matrix
	r--the 1¡Á3 transform vector
	Outputs:the spatial vector coordinatetransform matrix from the fixed frame to */

	void XAB(const double E[][3], const double r[], double matrix[][6]);

	/*BA::usage =
			"XBA[E_List,r_List]
			gives the motion spatial vector coordinate transform matrix from the Moving frame B
			to the fixed frame A,
			Inputs: E--the 3¡Á3 rotation matrix FROM A->B
			r--the 1¡Á3 transform vector FROM A->B
			Outputs:the spatial vector coordinatetransform matrix from the Moving frame B
			to the fixed frame A
			XBA[E_List,r_List]:=Block[{xe=Table[0,{i,1,6},{j,1,6}],xl=Table[0,{i,1,6},{j,1,6}]},xe[[1;;3,1;;3]]=Transpose[E];xe[[4;;6,4;;6]]=Transpose[E];
			xl[[1;;3,1;;3]]=IdentityMatrix [3];xl[[4;;6,4;;6]]=IdentityMatrix [3];
			xl[[4;;6,1;;3]]=VecCross[r];
			Dot[xl,xe]
			]
			"
			*/
	void XBA(const double E[][3], const double r[], double matrix[][6]);

	/*
		Crm::usage =
		"Crm[v_List]give the motion spatial vector v cross matrix
		Crm[v_List]:=Block[{crm=Table[0,{i,1,6},{j,1,6}]},crm[[1;;3,1;;3]]=VecCross[v[[1;;3]]];crm[[4;;6,1;;3]]=VecCross[v[[4;;6]]];
		crm[[4;;6,4;;6]]=VecCross[v[[1;;3]]];crm
		]
		*/

	void Crm(const double v[], double matrix[][6]);



	int MatrixIsUnit(double R[3][3]);
	int MatrixIsOrthUnit(double R[3][3]);



	//#ifdef __cplusplus
	//}
	//#endif
}
#endif//_MATRIX_H_