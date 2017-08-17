#include <iostream.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <new.h>
#include <malloc.h>

double UniformRV(int seed1, int seed2, int seed3);
//double UniformRV();

void MethodA(long n,long N,int * S)
{   
  //	int* S;
 //	S=(int *)malloc(n);
	//int S[100];
	int *p;
	int u,v,w,i (0);
   	double V,quot,Nreal,top;
   
	p=S;
	top=N-n;
	Nreal=N;
	u=0;
	v=100;
	w=3;

	while(n>=2)
	{   srand( (unsigned)time( NULL ) );
		u=u+rand();
	    v=v+15;
		w=w+rand();
		//V=UniformRV();
	   V=UniformRV(u,v,w);
	//	cout<<V<<endl;
	    *p=0;
	   	quot=top/Nreal;
		while(quot>V)
		{
		    *p=*p+1;
			top=-1.0+top;
			Nreal=-1.0+Nreal;
			quot=(quot*top)/Nreal;
		}
	//	cout<<*p<<";";
		Nreal=-1.0+Nreal;
		n=-1+n;
		i=i+1;
		p++;
	}
		if (n=1)
	{
	    *p=int(Nreal*UniformRV(u,v,w));
	
      	}
	//	S[i]=int(Nreal*UniformRV());
	/*	 for(j=0;j<=i;j++,S++)
		cout<<"S["<<j<<"]  "<<*S<<"; ";
	cout<<endl;*/
}
   
