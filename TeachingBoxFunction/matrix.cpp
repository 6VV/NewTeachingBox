
/**********************************************************************************************
*
* This file created  according to the invese kinematics method invented  by JING Fengshui
* all the matrix functions are specially designed for robotics use
* with no use of  heap memory, the program maybe  more robust
* WARNNing! manny functions assume the size of matrix is no more than 6. 
* revised history
* ver 1.3 by JING Fengshui, 2010/10/17 modify rotz3()
* ver 1.2 by JING Fengshui, 2010/10/17 add HomeMatrixInv();HomeMatrix2RP() and RP2HomeMatrix()
* ver 1.1 by JING Fengshui, 2010/7/11
* ver 1.0  created by JING Fengshui, 2010/6/6
* Institute of Automation, Chinese Academy of Sciences
* ALL rights reserved
*/// matrix operation
//#include "stdafx.h"


#include "matrix.h"
#include "Target_Math.h"
//#define PI 3.1415926

double MatrixUnit3[3][3] = { {1,0,0}, {0,1,0}, {0,0,1} };


/**************REAL MATRIX ADD********************************/
void MatrixAdd(const double a[],const double b[],int m,int n,double c[])
{
	register int i,j;
	for (i=0; i<m; i++)
		for (j=0; j<n; j++)
			c[i*n+j]=a[i*n+j]+b[i*n+j];

}
/**************REAL MATRIX MULTIPLICATION********************************/
void MatrixMul(const double a[],const double b[],int m,int n,int k,double c[])
{
	register int i,j,l,u;
	for (i=0; i<=m-1; i++)
		for (j=0; j<=k-1; j++)
		{ u=i*k+j; c[u]=0.0;
	for (l=0; l<=n-1; l++)
		c[u]=c[u]+a[i*n+l]*b[l*k+j];
	}
	return;
}
/**************REAL MATRIX invsaTION********************************/
int MatrixInv(const double s[],double a[],int n)//n No more than 6，i.e.rank 2--6
{
	int is[6],js[6];
	register int i,j,k;
	int l,u,v;
	double d,p;
	if(n>6||n<2) return (0);//n must nomore than 6
	for(i=0;i<n*n;i++)a[i]=s[i];
	for (k=0; k<=n-1; k++)
	{ d=0.0;
	for (i=k; i<=n-1; i++)
		for (j=k; j<=n-1; j++)
		{ l=i*n+j; p=fabs(a[l]);
	if (p>d) { d=p; is[k]=i; js[k]=j;}
	}
	if (d+1.0==1.0)
	{  //printf("err**not inv\n");
		return(0);
	}
	if (is[k]!=k)
		for (j=0; j<=n-1; j++)
		{ u=k*n+j; v=is[k]*n+j;
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	if (js[k]!=k)
		for (i=0; i<=n-1; i++)
		{ u=i*n+k; v=i*n+js[k];
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	l=k*n+k;
	a[l]=1.0/a[l];
	for (j=0; j<=n-1; j++)
		if (j!=k)
		{ u=k*n+j; a[u]=a[u]*a[l];}
		for (i=0; i<=n-1; i++)
			if (i!=k)
				for (j=0; j<=n-1; j++)
					if (j!=k)
					{ u=i*n+j;
		a[u]=a[u]-a[i*n+k]*a[k*n+j];
		}
		for (i=0; i<=n-1; i++)
			if (i!=k)
			{ u=i*n+k; a[u]=-a[u]*a[l];}
	}
	for (k=n-1; k>=0; k--)
	{ if (js[k]!=k)
	for (j=0; j<=n-1; j++)
	{ u=k*n+j; v=js[k]*n+j;
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	if (is[k]!=k)
		for (i=0; i<=n-1; i++)
		{ u=i*n+k; v=i*n+is[k];
	p=a[u]; a[u]=a[v]; a[v]=p;
	}
	}
	return(1);
}
/**************home MATRIX inversion********************************/
//input hm1[] 4*4 home transmation matrix
//output hm2[] 4*4 home transmation matrix
void HomeMatrixInv(const double hm1[],double hm2[])
{
	double p1[3],p2[3],RT[3][3];
	int i,j;
	//calcualte hm2[3][3]
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			RT[i][j]=hm1[j*4+i];
			hm2[i*4+j]=hm1[j*4+i];
		}
		p1[i]=-hm1[i*4+3];
	}
	//calculate hm2[:,4];
	MatrixMul((double *)RT,p1,3,3,1,p2);
	for(i=0;i<3;i++)
	{
		hm2[i*4+3]=p2[i];
	}
	//calculate hm2[4,:];
	for(j=0;j<3;j++)

	{
		hm2[3*4+j]=0;
	}

	hm2[4*4-1]=1;



}
/*
*input:
*	R[] 3 by 3 rotaion matrix
*	p[] 3 by 1 position vector
*output:
*	hm[] 4 by 4 hometransformation matrix
*return void
*/
void RP2HomeMatrix(const double R[],const double p[],double hm[])
{
	int i,j;
	for(i=0;i<3;i++)	  
	{
		for(j=0;j<3;j++)
		{
			hm[i*4+j]=R[i*3+j];
		}
		hm[i*4+3]=p[i];

	}
	//calculate hm[4,:];
	for(j=0;j<3;j++)

	{
		hm[3*4+j]=0;
	}

	hm[4*4-1]=1;
}

/*
*input:
*	hm[] 4 by 4 hometransformation matrix
*output:
*	R[] 3 by 3 rotaion matrix
*	p[] 3 by 1 position vector

*return void

*/
void HomeMatrix2RP(const double hm[], double R[], double p[])
{
	int i,j;
	for(i=0;i<3;i++)	  
	{
		for(j=0;j<3;j++)
		{
			R[i*3+j]=hm[i*4+j];
		}
		p[i]=hm[i*4+3];

	}

}	
double  MatrixDet(const double M[], int n)
{//计算行列式


	register int i,j;
	int k,is,js,l,u,v;
	double f,det,q,d;
	double a[36];
	for(i=0;i<36;i++)a[i]=M[i];
	f=1.0; det=1.0;
	for (k=0; k<=n-2; k++)
	{ q=0.0;
	for (i=k; i<=n-1; i++)
		for (j=k; j<=n-1; j++)
		{ l=i*n+j; d=fabs(a[l]);
	if (d>q) { q=d; is=i; js=j;}
	}
	if (q+1.0==1.0)
	{ det=0.0; return(det);}
	if (is!=k)
	{ f=-f;
	for (j=k; j<=n-1; j++)
	{ u=k*n+j; v=is*n+j;
	d=a[u]; a[u]=a[v]; a[v]=d;
	}
	}
	if (js!=k)
	{ f=-f;
	for (i=k; i<=n-1; i++)
	{ u=i*n+js; v=i*n+k;
	d=a[u]; a[u]=a[v]; a[v]=d;
	}
	}
	l=k*n+k;
	det=det*a[l];
	for (i=k+1; i<=n-1; i++)
	{ d=a[i*n+k]/a[l];
	for (j=k+1; j<=n-1; j++)
	{ u=i*n+j;
	a[u]=a[u]-d*a[k*n+j];
	}
	}
	}
	det=f*det*a[n*n-1];
	return(det);

}


void MatrixT(const double s[],double T[],int n)//turn transform n No more than 6，i.e.rank 2--6
{
	register int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			T[j*n+i]=s[i*n+j];


}
/*-------- HomoMatrix Position translation and rotation--------*/
void Move_XYZ_Matrix(const double dx, const double dy,const double dz,double theMatrix[])
{
	int i,j;
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(i==j) theMatrix[i*4+j]=1;
			else  theMatrix[i*4+j]=0;
		}
		theMatrix[3]=dx;
		theMatrix[7]=dy;
		theMatrix[11]=dz;
}


void Rote_X_Matrix(const double x_angle,double theMatrix[]) 
{

	int i,j;
	double c,s;
	c=cos(x_angle);
	s=sin(x_angle);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(i==j) theMatrix[i*4+j]=1;
			else  theMatrix[i*4+j]=0;
		}
		theMatrix[5]=c; theMatrix[6]=-s;
		theMatrix[9]=s; theMatrix[10]=c;
}

void Rote_Y_Matrix(const double y_angle,double theMatrix[]) 
{

	int i,j;
	double c,s;
	c=cos(y_angle);
	s=sin(y_angle);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(i==j) theMatrix[i*4+j]=1;
			else  theMatrix[i*4+j]=0;
		}
		theMatrix[0]=c; theMatrix[2]=s;
		theMatrix[8]=-s; theMatrix[10]=c;
}

void Rote_Z_Matrix(const double z_angle,double theMatrix[]) 
{

	int i,j;
	double c,s;
	c=cos(z_angle);
	s=sin(z_angle);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			if(i==j) theMatrix[i*4+j]=1;
			else  theMatrix[i*4+j]=0;
		}
		theMatrix[0]=c; theMatrix[1]=-s;
		theMatrix[4]=s; theMatrix[5]=c;
}
void Roll_Pitch_Yaw(const double x_angle,const double y_angle, const double z_angle,double theMatrix[]) //in degree
//WARNING: this function is special designed in the folowing sequence
//first rotate around x-axis, then y-axis,finally z-axis
{
	double R[16];
	double P[16];
	double Y[16];
	double temp[16];
	Rote_X_Matrix(x_angle,R);
	Rote_Y_Matrix(y_angle,P);
	Rote_Z_Matrix(z_angle,Y);
	MatrixMul(P,R,4,4,4,temp);
	MatrixMul(Y,temp,4,4,4,theMatrix);

}
//the following function form a conversion matrix Aij from px,py,pz,and roll,pitch yaw


/* call Acb=inv(Ab)*Ac;  or Ac=Ab*Acb ,*/
//i.e.the transform matrix from c coor to b coor
int Cal_Acb(const double Ab[],const double Ac[],double Acb[])
{
	static double temp1[16];
	int i,j;
	//first give origin value to temp1

	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
		{
			temp1[i*4+j]=Ab[i*4+j];
		}
		if(!MatrixInv(temp1,temp1,4))MatrixMul(temp1,Ac,4,4,4,Acb);

		else return 0;//if 1 success or error when do inverse
		return 1;
}
//this function calculate the roll pitch yaw angles from the conversion matrix
void Matrix_RPY(const double A[],double *roll, double *pitch, double *yaw )
{
	*roll=atan2(A[9],A[10]);
	*pitch=asin(-A[8]);
	*yaw=atan2(A[4],A[0]);
}
/*-------------------------------------------------------------------------------*/
/************ KINEMATICS IN VECTOR SPACE **************************************/
/*VecCross::usage =
"VecCross[vec_List]
gives the  matrix vec× ,
Inputs: vec--a vector in  				
Outputs:matrix vec× 
*/
void VecCross(const double vec[], double matrix[][3])
{
	register int i,j;
	for(i=0;i<3;i++)// creat  3 by 3 zero matrix
	{
		for(j=0;j<3;j++)
		{
			matrix[i][j]=0;
		}
	}
	matrix[0][1] = -vec[2];	
	matrix[0][2] = vec[1]; 
	matrix[1][0] = vec[2]; 
	matrix[1][2] = -vec[0]; 
	matrix[2][0] = -vec[1]; 
	matrix[2][1] = vec[0];
}
void VecCross_minus(const double vec[], double matrix[][3])
{
	register int i,j;
	for(i=0;i<3;i++)// creat  3 by 3 zero matrix
	{
		for(j=0;j<3;j++)
		{
			matrix[i][j]=0;
		}
	}

	matrix[0][1] = vec[2];	
	matrix[0][2] = -vec[1]; 
	matrix[1][0] = -vec[2]; 
	matrix[1][2] = vec[0]; 
	matrix[2][0] = vec[1]; 
	matrix[2][1] = -vec[0];
}
/**
AxisAngle2R()
v[], 3x1 axis vector
angle,as the name imply in unit rad

*/
void AxisAngle2R(const double v[], const double angle, double R[][3])
{
	register int i,j;
	double imax[3][3],vtemp[3][3],vtemp2[3][3];
	double c,s;
	s=sin(angle);
	c=1-cos(angle);
	VecCross(v, vtemp);
	MatrixMul((double *)vtemp,(double *)vtemp,3,3,3,(double *)vtemp2);
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(i==j)imax[i][j]=1;
			else
				imax[i][j]=0;

			vtemp[i][j]*=s;
			vtemp2[i][j]*=c;
			R[i][j]=imax[i][j]+vtemp[i][j]+vtemp2[i][j];

		}
	}
	/*IdentityMatrix[3] + Vect2Mat[v]*Sin[\[Theta]] + 
	Vect2Mat[v].Vect2Mat[v]*(1 - Cos[\[Theta]])*/

	//if (Equal(v[0], 0) && Equal(v[1], 0) && Equal(v[2], 0))
	//	TARGET_MEMSET(&R[0][0], 0, 9*sizeof(double));
}

double MatrixTrace(const double A[], int n)
{
	int i;
	double sum=0;

	for(i = 0; i < n; i++) sum +=A[i*n+ i]; 
	return sum;
}

/**
UNIT QUARTERNION 是关于乘法的一个群 （非交换的） 。对于 SO3 即R上每个点 （除了IDENTITY外） ，在UNIT \
QUARTERNION 上都有两个点与其对应，如果当\[Theta] = 
0 时，我们定义 \[Omega] = 
0 ；那么对于 SO3 即R上每个点 （除了IDENTITY外） ，都有两个点 （\[Omega], \[Theta]） （-\
\[Omega], 2 Pi - \[Theta]） 与其对应
anxis anle 可以看作是UNIT QUARTERNION的几何表示。即其本质上是一样的。在这个函数中， 我们考虑了机器人末端
每次姿态变换不超出180度，如果超出了，那么就要分作两次操作。否则机器人会按角度的最短路径（即沿反方向旋转360-theta）运动。
*/

void R2AxisAngle(const double R[][3], double v[],  double *angle)
{

	double c;
	double val;
	val=(MatrixTrace((double *)R, 3) - 1)/2;
	//判断val是否超出有效值边界
	if(val>1.0f) val=1.0f;
	if(val<-1.0f) val=-1.0f;
	*angle=acos(val);

	if(fabs(*angle)<0.000001)//R==IDENTITY[3];
	{
		*angle=0;
		v[0]=0;v[1]=0;v[2]=0;
		return;
	}

	c=1/(2*sin(*angle));
	v[0]=R[2][1]*c - R[1][2]*c;
	v[1]=R[0][2]*c - R[2][0]*c;
	v[2]=R[1][0]*c - R[0][1]*c;	

	if (Equal(v[0], 0) && Equal(v[1], 0) && Equal(v[2], 0))
		*angle = 0;
}

/*xrot::usage =
"        
xrot[E_List]:gives a 6×6 transform matrix from B to A,
based on the 3×3rotation matrix E from B to A

xrot[E_List]:=Block[{xe=Table[0,{i,1,6},{j,1,6}]},xe[[1;;3,1;;3]]=E;xe[[4;;6,4;;6]]=E;xe]
*/
void xrot(const double E[][3],double matrix[][6])
{
	register int i,j;
	for(i=0;i<6;i++)// creat  6 by 6 zero matrix
	{
		for(j=0;j<6;j++)
		{
			matrix[i][j]=0;
		}
	}

	for(i=0;i<3;i++)// creat  3 by 3 zero matrix
	{
		for(j=0;j<3;j++)
		{
			matrix[3+i][3+j]=E[i][j];
			matrix[i][j]=E[i][j];

		}
	}
}
/*
xlt::usage =
"      
xlt[r_List]:gives a 6×6 transform matrix from A to B,
based on the 1×3 transformation matrix E from B to A
"
xlt[r_List]:=Block[{xl=Table[0,{i,1,6},{j,1,6}]},
xl[[1;;3,1;;3]]=IdentityMatrix [3];xl[[4;;6,4;;6]]=IdentityMatrix [3];
xl[[4;;6,1;;3]]=-VecCross[r];xl]
*/
void xlt(const double r[],double matrix[][6])
{
	register int i,j;
	double block[3][3];
	for(i=0;i<6;i++)// creat  6 by 6 zero matrix
	{
		for(j=0;j<6;j++)
		{
			matrix[i][j]=0;
		}
	}

	for(i=0;i<3;i++)// creat  2 Identity matrix
	{
		for(j=0;j<3;j++)
		{
			if(i==j)
			{
				matrix[3+i][3+j]=1;
				matrix[i][j]=1;
			}
		}
	}
	VecCross_minus(r,block); 
	for(i=3;i<6;i++)// create  the low left corner block
	{
		for(j=0;j<3;j++)
		{
			matrix[i][j]=block[i-3][j];

		}
	}
}



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

void rotx3(const double x_angle,double rotmatrix[][3])
{
	int i,j;
	double c,s;

	c=cos(x_angle);
	s=sin(x_angle);
	for(i=0;i<3;i++)// create zero matrix
		for(j=0;j<3;j++)
		{
			rotmatrix[i][j]=0;
		}
		// create rotation matrix about x
		rotmatrix[0][0]=1;
		rotmatrix[1][1]=c; 	rotmatrix[1][2]=-s;
		rotmatrix[2][1]=s;	rotmatrix[2][2]=c;

}
void roty3(const double y_angle,double rotmatrix[][3])
{
	int i,j;
	double c,s;

	c=cos(y_angle);
	s=sin(y_angle);
	for(i=0;i<3;i++)// create zero matrix
		for(j=0;j<3;j++)
		{
			rotmatrix[i][j]=0;
		}
		// create rotation matrix about y
		rotmatrix[1][1]=1;
		rotmatrix[0][0]=c; 	rotmatrix[0][2]=s;
		rotmatrix[2][0]=-s;	rotmatrix[2][2]=c;

}
void rotz3(const double z_angle,double rotmatrix[][3])
{
	int i,j;
	double c,s;

	c=cos(z_angle);
	s=sin(z_angle);
	for(i=0;i<3;i++)// create zero matrix
		for(j=0;j<3;j++)
		{
			rotmatrix[i][j]=0;
		}
		// create rotation matrix about y
		rotmatrix[2][2]=1;
		rotmatrix[0][0]=c; 	rotmatrix[0][1]=-s;
		rotmatrix[1][0]=s;	rotmatrix[1][1]=c;

}
void rotx6(const double x_angle,double matrix[][6])
{
	int i,j;
	double c,s;
	double rotmatrix[3][3];
	c=cos(x_angle);
	s=sin(x_angle);
	for(i=0;i<3;i++)// create zero matrix
		for(j=0;j<3;j++)
		{
			rotmatrix[i][j]=0;
		}
		// create rotation matrix about x
		rotmatrix[0][0]=1;
		rotmatrix[1][1]=c; 	rotmatrix[1][2]=-s;
		rotmatrix[2][1]=s;	rotmatrix[2][2]=c;
		xrot(rotmatrix,matrix);
}
void roty6(const double y_angle,double matrix[][6])
{
	int i,j;
	double c,s;
	double rotmatrix[3][3];
	c=cos(y_angle);
	s=sin(y_angle);
	for(i=0;i<3;i++)// create zero matrix
		for(j=0;j<3;j++)
		{
			rotmatrix[i][j]=0;
		}
		// create rotation matrix about y
		rotmatrix[1][1]=1;
		rotmatrix[0][0]=c; 	rotmatrix[0][2]=s;
		rotmatrix[2][0]=-s;	rotmatrix[2][2]=c;
		xrot(rotmatrix,matrix);
}
void rotz6(const double z_angle,double matrix[][6])
{
	int i,j;
	double c,s;
	double rotmatrix[3][3];
	c=cos(z_angle);
	s=sin(z_angle);
	for(i=0;i<3;i++)// create zero matrix
		for(j=0;j<3;j++)
		{
			rotmatrix[i][j]=0;
		}
		// create rotation matrix about y
		rotmatrix[3][3]=1;
		rotmatrix[0][0]=c; 	rotmatrix[0][2]=-s;
		rotmatrix[1][0]=s;	rotmatrix[1][2]=c;
		xrot(rotmatrix,matrix);
}
/*
XAB::usage =
"XAB[E_List,r_List]
gives the motion spatial vector coordinate transform matrix from the fixed frame A
to the Moving frame B,
Inputs: E--the 3×3 rotation matrix from frame B->A
r--the 1×3 transform vector from frame A->B				
Outputs:the spatial vector coordinatetransform matrix from the  frame A to
frame B
XAB[E_List,r_List]:=Block[{xe=Table[0,{i,1,6},{j,1,6}],xl=Table[0,{i,1,6},{j,1,6}]},xe[[1;;3,1;;3]]=E;xe[[4;;6,4;;6]]=E;
xl[[1;;3,1;;3]]=IdentityMatrix [3];xl[[4;;6,4;;6]]=IdentityMatrix [3];
xl[[4;;6,1;;3]]=-VecCross[r];
Dot[xe,xl]
]


*/

void XAB(const double E[][3],const double r[], double matrix[][6])
{
	double temp1[6][6],temp2[6][6];
	xrot(E,temp1);
	xlt(r,temp2);
	MatrixMul((double *)temp1,(double *)temp2,6,6,6,(double *)matrix);
}
/*BA::usage =
"XBA[E_List,r_List]
gives the motion spatial vector coordinate transform matrix from the Moving frame B
to the fixed frame A,
Inputs: E--the 3×3 rotation matrix FROM A->B
r--the 1×3 transform vector FROM B->A				
Outputs:the spatial vector coordinatetransform matrix ffrom the Moving frame B
to the fixed frame A
XBA[E_List,r_List]:=Block[{xe=Table[0,{i,1,6},{j,1,6}],xl=Table[0,{i,1,6},{j,1,6}]},xe[[1;;3,1;;3]]=Transpose[E];xe[[4;;6,4;;6]]=Transpose[E];
xl[[1;;3,1;;3]]=IdentityMatrix [3];xl[[4;;6,4;;6]]=IdentityMatrix [3];
xl[[4;;6,1;;3]]=VecCross[r];
Dot[xl,xe]
]
"
*/
void XBA(const double E[][3],const double r[], double matrix[][6])
{
	register int i,j;
	double temp1[6][6],temp2[6][6],block[3][3];
	for(i=0;i<6;i++)// creat  6 by 6 zero matrix
	{
		for(j=0;j<6;j++)
		{
			temp1[i][j]=0;temp2[i][j]=0;
		}
	}

	for(i=0;i<3;i++)// creat xe=temp1 and xl=temp2
	{
		for(j=0;j<3;j++)
		{
			if(i==j)
			{
				temp2[3+i][3+j]=1;
				temp2[i][j]=1;
			}
			temp1[i][j]=E[j][i];
			temp1[i+3][j+3]=E[j][i];

		}
	}
	VecCross(r,block); 
	for(i=3;i<6;i++)// create  the low left corner block
	{
		for(j=0;j<3;j++)
		{
			temp2[i][j]=block[i-3][j];

		}
	}
	MatrixMul((double *)temp1,(double *)temp2,6,6,6,(double *)matrix);
}
/*
Crm::usage =
"Crm[v_List]give the motion spatial vector v cross matrix 
Crm[v_List]:=Block[{crm=Table[0,{i,1,6},{j,1,6}]},crm[[1;;3,1;;3]]=VecCross[v[[1;;3]]];crm[[4;;6,1;;3]]=VecCross[v[[4;;6]]];
crm[[4;;6,4;;6]]=VecCross[v[[1;;3]]];crm
]
*/

void Crm(const double v[], double matrix[][6])
{
	register int i,j;
	double block1[3][3],block2[3][3];
	for(i=0;i<6;i++)// create  6 by 6 zero matrix
	{
		for(j=0;j<6;j++)
		{
			matrix[i][j]=0;
		}
	}
	VecCross(v,block1);	
	VecCross(&v[3],block2);
	for(i=0;i<3;i++)// create crm
	{
		for(j=0;j<3;j++)
		{

			matrix[i][j]=block1[i][j];
			matrix[i+3][j+3]=block1[i][j];
			matrix[i+3][j]=block2[i][j];

		}
	}
}

//是否是单位阵
//返回值：1：是单位阵	0：不是单位阵
int MatrixIsUnit(double R[3][3])
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			if (i == j)
			{
				if (!Equal(R[i][j], 1))
					return 0;
			}
			else
			{
				if (!Equal(R[i][j], 0))
					return 0;
			}
		}
	}
	return 1;
}

//是否是正交阵
//返回值：1：是正交阵	0：不是正交阵
int MatrixIsOrthUnit(double R[3][3])
{
	double RInverse[3][3], RResult[3][3];
	MatrixT((LONG_REAL*)R, (LONG_REAL*)RInverse, 3);
	MatrixMul((LONG_REAL *)R, (LONG_REAL *)RInverse, 3, 3, 3, (LONG_REAL *)RResult);
	
	return MatrixIsUnit(RResult);

}


