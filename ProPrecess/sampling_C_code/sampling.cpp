#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
//#include <string.h>
#include <assert.h>
#include "genfitem.h"


//#include <fstream.h>
#include <stdio.h>



#define SEC_SINCE(t) ((clock()-(t))/(double)CLOCKS_PER_SEC)

double UniformRV(int seed1, int seed2, int seed3);
//double UniformRV();
void MethodA(long n,long N,int * S);
void MethodD(long n,long N, int * S);
int rec_skip(FILE *file,ofstream outfile,int s);
char get_item(FILE * file,char * str);
struct StrItem * creatlink(FILE * file);
void get_freitem(struct StrItem * head,int &finum,int &oneinum);
double distance1(FILE * file1,FILE * file2);


void main(int argc, char * argv[])
 {  clock_t t;
	long n,N;
	int * S;
/*These codes are used to output the skip sample size.
	N=100000;
	n=long(N/640);
	int * S;
	S=(int *)malloc(n*sizeof(int));
	t=clock();
	MethodA(n,N,S);
	cout<<SEC_SINCE(t)<<"s"<<endl;
	getch();
    t=clock();
    MethodD(n,N,S);
    cout<<SEC_SINCE(t)<<"s"<<endl;
	free(S);*/
  //  ScanItems item;
	static FILE * in=NULL;
	char fn_in[128], fn_out[128];
	int count,tmp(-1);

	sprintf(fn_in, "%s_title.txt", argv[1]);
	sprintf(fn_out, "%s_%s_title.txt", argv[1], argv[2]);


	ofstream outfile;
	outfile.open(fn_out, ios::trunc);
		
	t=clock();

	
	if(!fn_in)

	{
		in=stdin;
		strcpy(fn_in, "<stdin>");
	}
	else
	{
		in=fopen(fn_in,"r");
	    if(!in) cout<<"can't open file"<<endl;
	}
    cout<<"reading  "<<fn_in<<"..."<<endl;
	N=rec_skip(in,outfile,-1);
	fclose(in);
	double sr, ratio;
	sr=1.0/16.0;

	ratio = atof(argv[2]);
	ratio = ratio/100.0;

	printf("%f", ratio);

	n=long(N*ratio);
	cout<<"There are "<<N<<" transaction and "<<n<<" samples."<<endl;
	cout<<"Reading the orignal file uses the time "<<SEC_SINCE(t)<<"s."<<endl;
//	getch();
    S=(int *)malloc(n*sizeof(int));
    t=clock();
	in=fopen(fn_in,"r");
   	MethodD(n,N,S);
	count=0;
//	for(int i=n;i<n-10;i--)
//		cout<<S[i]<<";";
//	    cout<<endl;
	for(int i=0;i<n;i++)
	{
		count=count+rec_skip(in,outfile,S[i]);
		count++;
	  //  cout<<"the "<<count<<"'s sample should be sampled."<<endl;
	}
	fclose(in);
	outfile.close();
	free(S);

    cout<<"Sample file genetor uses time "<<SEC_SINCE(t)<<"s."<<endl;

	
}
   
