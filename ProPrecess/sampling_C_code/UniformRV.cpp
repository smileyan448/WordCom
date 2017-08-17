#include <iostream.h>
#include <math.h>

double UniformRV(int seed1, int seed2, int seed3)
{
//const seed1 = 5, seed2 = 10000, seed3 = 3000;
int x, y, z;
double tmp, Unif;
       x = seed1;
       y = seed2; 
       z = seed3;
	    x = 171*int(fmod(x, 177)) - 2*(x %177);
        if (x<0) 
		 x = x + 30269;
        y = 172*int(fmod(y, 176)) -35*(y & 176);
        if (y<0) 
			y = y + 30307;
        z = 170*int(fmod(z, 178)) -63*(z & 178);
        if (z<0) 
			z = z + 30323;
        tmp =  x/30269.0 + y/30307.0 + z/30323.0;
        Unif = tmp - int(tmp);
       
	   return Unif;
       
}

/* uniform [0,1] random number generator
   developed by Pierre Lecuyer based on a clever
   and tested combination of two linear congruential
   sequences 
*/

/*
s1 and s2 are the seeds (nonnegative integers)
*/

/*#include <math.h>

double UniformRV()
{
static long s1 = 55555;
static long s2 = 99999;
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
}*/


