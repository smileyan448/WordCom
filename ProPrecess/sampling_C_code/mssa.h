#include <fstream.h>


class NonunifSample
{
public:
	int a;
	int j0;
	int scale;
	ofstream origfile;
	ofstream sampfile;
public:
	double UniformRN(long seed1,long seed2);
	NonunifSample();
	~NonunifSample();
	void Inisample();
};