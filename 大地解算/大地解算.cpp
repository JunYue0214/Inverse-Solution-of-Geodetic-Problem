//大地主题解算
//岳俊  2009301610186  09级实验班
//指导老师   郭际明

#include <iostream>
#include <math.h>
#include<iomanip>
#define PI 3.1415926

using namespace std;

//角度转化为弧度
double deg2arc(double deg)
{
	int degree,minute;
	double second;
	degree=(int)deg;
	minute=(int)((deg-degree)*100);
	second=(deg-degree-minute/100.0)*10000.0;
	return fabs((degree+minute/60.0+second/3600.0)*PI/180.0);
}

//弧度转化为角度
double arc2deg(double rad)
{        
	int degree,minute;
	double second,temp;	
	temp=rad*180/PI;
	degree=(int)temp;
	minute=(int)((temp-degree)*60);
	second=((temp-degree)*60.0-minute)*60;
	if (second>=59.995)
	{
		second=0.0;
		minute=minute+1;
	}
	if (minute>=60)
	{
		minute=0;
		degree=degree+1;
	}
	return fabs(degree+minute/100.0+second/10000.0);
}


void fan(double B1,double L1,double B2,double L2,double a,double f,double n)
{


	B1=deg2arc(B1);
	L1=deg2arc(L1);
	B2=deg2arc(B2);
	L2=deg2arc(L2);

	double W0,M0,N0,W,M,N,C,Af,dB,dS,dL,i,B,L,A,S,e;
	int TIME;

	e=sqrt(2*f-f*f);
	W0=sqrt(1-e*e*sin(B1)*sin(B1));
	M0=a*(1-e*e)/pow(W0,3);
	N0=a/W0;
	Af=atan(  N0*cos(B1)/M0*(L2-L1)/(B2-B1)  );
	dB=(B2-B1)/n;
	TIME=1;

	do{
		B=B1;
		L=L1;	
		C=N0*cos(B1)*sin(Af);
		S=0;
		A=Af;
		for(i=0;i<n;i++)
		{
			W=sqrt(1-e*e*sin(B)*sin(B));
			M=a*(1-e*e)/pow(W,3);
			N=a/W;
			dS=M/cos(A)*dB;
			dL=dS*sin(A)/(N*cos(B));
			A=asin(  C/(  N*cos(B)  )  );
			B=B+dB;
			L=L+dL;
			S=S+dS;

		}
		Af=Af+(L2-L)*N*cos(B)/S;
		TIME++;

	}while (fabs(L-L2)>0.00000001);
	cout<<endl;
	cout<<"大地主题解算反算结果："<<endl;
	cout<<"迭代次数:"<<setiosflags(ios::fixed)<<setprecision(8)<<TIME<<"  S="<<S<<"  A12="<<arc2deg(Af)<<"  A21="<<arc2deg(A)+180<<endl<<endl;


}

void  zheng(double B,double L,double A,double S,double a,double f,int n)
{
	B=deg2arc(B);
	L=deg2arc(L);
	A=deg2arc(A);

	double e=sqrt(2*f-f*f);
	double dS=S/n;
	double W0=sqrt(1-e*e*sin(B)*sin(B));
	double N0=a/W0;
	double C=N0*cos(B)*sin(A);
	double W,M,N,dB,dL,sinA;

	for(int i=0;i<n;i++)
	{ 
		W=sqrt(1-e*e*sin(B)*sin(B));
		M=a*(1-e*e)/pow(W,3);
		N=a/W;
		dB=dS*cos(A)/M;
		dL=dS*sin(A)/(N*cos(B));
		B=B+dB;
		L=L+dL;
		sinA=C/(N*cos(B));
		A=asin(C/(N*cos(B)));
	}
    cout<<endl;
	cout<<"大地主题解算正算结果:"<<endl;
	cout<<"dS="<<setiosflags(ios::fixed)<<setprecision(8)<<dS<<"  B2="<<arc2deg(B)<<"  L2="<<arc2deg(L)<<"  A21="<<arc2deg(A)+180<<endl<<endl;
}
void main()
{
	double B=45.0000;
	double L=10.0000;
	double S=1320284.36837;
	double A=29.0315458713;
	double a=6377397.155;
	double f=1/299.15281285;
	int n=100000;

	double B1=45.0;
	double L1=10.0;
	double B2=55.000000016;
	double L2=19.595999952;

	int MODE;
	cout<<"请选择椭球体："<<endl;
	cout<<"选择WGS-84椭球体,请按1"<<endl;
	cout<<"选择CGC2000椭球体,请按2"<<endl;
	cout<<"选择1975国际椭球体,请按3"<<endl;
	cout<<"选择克拉索夫斯基椭球体,请按4"<<endl;
	cout<<"自定义椭球体,请按5"<<endl;
	cin>>MODE;
	//选择坐标系
	switch (MODE)
	{	
	case 1:
		{
			a=6378137;
			f=1/298.257223563;
			break;
		}
	case 2:
		{
		    a=6378137;
			f=1/298.257222101;
			break;
		} 
	case 3:
		{
			a=6378140;
			f=1/298.257;
			break;
		}
	case 4:
		{
			 a=6378245;
			 f=1/298.3;
			 break;
		}
	case 5:
		{
			cout<<endl;
			cout<<"请输入椭球长轴："<<endl;
			cin>>a;
			cout<<"请输入椭球扁率分母："<<endl;
			cin>>f;
			f=1/f;
			break;
		}
	default: break;
	}

	cout<<endl;
	cout<<"请选择计算方式,正算请按1，反算请按2:"<<endl;
	cin>>MODE;

	switch (MODE)
	{	
	case 1:
		{
			cout<<"请输入起始点纬度B1：";
			cin>>B;
			cout<<"请输入起始点经度L1：";
			cin>>L;
			cout<<"请输入起始点大地线方位角A12：";
			cin>>A;
			cout<<"请输入大地线长S：";
			cin>>S;
			cout<<"请输入微分段数n：";
			cin>>n;
			zheng(B,L,A,S,a,f,n);
			break;
		}
	case 2:
		{
			cout<<"请输入起始点纬度B1：";
			cin>>B1;
			cout<<"请输入起始点经度L1：";
			cin>>L1;
			cout<<"请输入大地线终点纬度B2：";
			cin>>B2;
			cout<<"请输入大地线终点经度L2：";
			cin>>L2;
			cout<<"请输入微分段数n：";
			cin>>n;
			fan(B1,L1,B2,L2,a,f,n);
			break;
		} 
	default: break;
	}

	getchar();

}

