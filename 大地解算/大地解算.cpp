//����������
//����  2009301610186  09��ʵ���
//ָ����ʦ   ������

#include <iostream>
#include <math.h>
#include<iomanip>
#define PI 3.1415926

using namespace std;

//�Ƕ�ת��Ϊ����
double deg2arc(double deg)
{
	int degree,minute;
	double second;
	degree=(int)deg;
	minute=(int)((deg-degree)*100);
	second=(deg-degree-minute/100.0)*10000.0;
	return fabs((degree+minute/60.0+second/3600.0)*PI/180.0);
}

//����ת��Ϊ�Ƕ�
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
	cout<<"���������㷴������"<<endl;
	cout<<"��������:"<<setiosflags(ios::fixed)<<setprecision(8)<<TIME<<"  S="<<S<<"  A12="<<arc2deg(Af)<<"  A21="<<arc2deg(A)+180<<endl<<endl;


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
	cout<<"����������������:"<<endl;
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
	cout<<"��ѡ�������壺"<<endl;
	cout<<"ѡ��WGS-84������,�밴1"<<endl;
	cout<<"ѡ��CGC2000������,�밴2"<<endl;
	cout<<"ѡ��1975����������,�밴3"<<endl;
	cout<<"ѡ���������˹��������,�밴4"<<endl;
	cout<<"�Զ���������,�밴5"<<endl;
	cin>>MODE;
	//ѡ������ϵ
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
			cout<<"�����������᣺"<<endl;
			cin>>a;
			cout<<"������������ʷ�ĸ��"<<endl;
			cin>>f;
			f=1/f;
			break;
		}
	default: break;
	}

	cout<<endl;
	cout<<"��ѡ����㷽ʽ,�����밴1�������밴2:"<<endl;
	cin>>MODE;

	switch (MODE)
	{	
	case 1:
		{
			cout<<"��������ʼ��γ��B1��";
			cin>>B;
			cout<<"��������ʼ�㾭��L1��";
			cin>>L;
			cout<<"��������ʼ�����߷�λ��A12��";
			cin>>A;
			cout<<"���������߳�S��";
			cin>>S;
			cout<<"������΢�ֶ���n��";
			cin>>n;
			zheng(B,L,A,S,a,f,n);
			break;
		}
	case 2:
		{
			cout<<"��������ʼ��γ��B1��";
			cin>>B1;
			cout<<"��������ʼ�㾭��L1��";
			cin>>L1;
			cout<<"�����������յ�γ��B2��";
			cin>>B2;
			cout<<"�����������յ㾭��L2��";
			cin>>L2;
			cout<<"������΢�ֶ���n��";
			cin>>n;
			fan(B1,L1,B2,L2,a,f,n);
			break;
		} 
	default: break;
	}

	getchar();

}

