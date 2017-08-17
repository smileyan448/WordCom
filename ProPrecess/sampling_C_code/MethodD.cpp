#include <iostream.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <new.h>

double UniformRV(int seed1, int seed2, int seed3);
//double UniformRV();
void MethodA(long n,long N,int *S);

void MethodD(long n, long N,int *S)
{ 
   // int* S;
	//S=(int *) malloc(n);
    //int S[1000];
	double nreal,Nreal,ninv,nmin1inv,U,X,Vprime,y1,y2,top,bottom,negSreal,qu1real;
	int negalphainv,threshold,qu1,u,v,w,limit,t,flag,i=0;

//	assert(file);

//	static int tcount=0;
  	flag=1;
	nreal=n;
	ninv=1.0/nreal;
	Nreal=N;
	u=0;
	v=100;
	w=3;
	Vprime=exp(log(UniformRV(u,v,w))*ninv);
	//Vprime=exp(log(UniformRV())*ninv);
	qu1=-n+1+N;
	qu1real=-nreal+1.0+Nreal;
	negalphainv=-13;
	threshold=-negalphainv*n;
	while(n>1 && threshold<N)
	{  nmin1inv=1.0/(-1.0+nreal);
	  do
	  { 
		srand( (unsigned)time( NULL ) );
		u=u+rand();
	    v=v+15;
		w=w+rand();
		S[i]=0;
		do
		{
			X=Nreal*(-Vprime+1.0);
			S[i]=int(X);
	        Vprime=exp(log(UniformRV(u,v,w))*ninv);
		//	Vprime=exp(log(UniformRV())*ninv);
			
		}
		while(S[i]>=qu1);
		U=UniformRV(u,v,w);
		//U=UniformRV();
		negSreal=-S[i];
		y1=exp(log(U*Nreal/qu1real)*nmin1inv);
		Vprime=y1*(-X/Nreal+1.0)*(qu1real/(negSreal+qu1real));
		if(Vprime<=1.0) break;
	  	y2=1.0;
		top=-1.0+Nreal;
		if(-1+n>S[i])
		{
			bottom=-nreal+Nreal;limit=-S[i]+N;
		}
		else
		{
			bottom=-1.0+negSreal+Nreal;limit=qu1;
		}
		for(t=-1+N;t>limit;t--)
		{
			y2=(y2*top)/bottom;
			top=-1.0+top;bottom=-1.0+bottom;
		}
		if(Nreal/(-X+Nreal)>=y1*exp(log(y2)*nmin1inv))
		{
			Vprime=exp(log(UniformRV(u,v,w))*nmin1inv);
			//Vprime=exp(log(UniformRV())*nmin1inv);
			break;
		}
		Vprime=exp(long(UniformRV(u,v,w))*ninv);
		//Vprime=exp(long(UniformRV())*ninv);
	}
	while(flag);
//	cout<<S[i]<<":";

	N=-S[i]+(-1+N);
	Nreal=negSreal+(-1.0+Nreal);
	n=-1+n;
	nreal=-1+nreal;
	ninv=nmin1inv;
	qu1=-S[i]+qu1;
	qu1real=negSreal+qu1real;
	threshold=threshold|negalphainv;
    i=i+1;
	}	
//	for(int j=0;j<i;j++)
	//	cout<<"S["<<j<<"]  "<<S[j]<<"; ";

	if(n>1) 
		MethodA(n,N,S);
	else
	{
		S[i]=int(N*Vprime);
	}
	//	cout<<"S["<<i<<"]  "<<S[i]<<"; ";
	//	cout<<endl;
}

