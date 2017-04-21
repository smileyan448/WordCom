#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream.h>

//#include <string.h>
#include <fstream.h>
#include <assert.h>

int rec_skip(FILE *file,ofstream outfile,int s)
{
	int c,count=0;
	char *str;
	char *str1;
	str=(char *) malloc(10000*sizeof(char));
    str1=str;

	if(!outfile)
	{
		cout<<"Output file can't open."<<endl;
		abort();
	}

	
	
    assert(file);
	if (s==(-1))
	  while(1)
	  {
		while ((c=getc(file))!='\n' )
		{
      	if(c==EOF)break;

		//ungetc(c,file);
	//	count++;
		};
		count++;		
		if(c==EOF)break;
	  }
	  else
	  {
		  for(int i=0;i<s;i++)
		{
			while ((c=getc(file))!='\n' )
		{
      	if(c==EOF)break;

		//ungetc(c,file);
	//	count++;
		};
		count++;		
		if(c==EOF)break;
		}
		  
		  while ((c=getc(file))!='\n' )
		  { // cout<<char(c);
			 if (c==EOF) break;
			  *str=char(c);
			 str++;
		  }
	//	 cout<<endl;
		   *str='\n';
		   while(*str1!='\n')
		   {  outfile<<*str1;
		   //cout<<*str1;
		     str1++;
		   }
		   outfile<<endl;
	  
	  }
//+	  free(str);
     	return count;
}
	

