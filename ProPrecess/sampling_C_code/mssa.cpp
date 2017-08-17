#include "mssa.h"
#include <stdlib.h>

NonunifSample::NonunifSample()
{  a=2;
   j0=8;
   scale=1;
   for(int i=0;i<8;i++)
	  scale=scale*a;
};

NonunifSample::~NonunifSample()
{

}

double NonunifSample::UniformRN(long s1,long s2)
{
static double factor = 1.0/2147483563.0;
register long k,z;
	k= s1 /53668;
	s1 =40014*(s1%53668)-k*12211;
	if (s1 < 0) s1 += 2147483563;
	k=s2/52774;
	s2=40692*(s2%52774)-k*3791;
	if (s2 < 0) s2 += 2147483399;

//	z = abs(s1 ^ s2);

	z= (s1 - 2147483563) + s2;
	if (z < 1) z += 2147483562;
	
	return(((double)(z))*factor);
};

void NonunifSample::Inisample()
{

};


