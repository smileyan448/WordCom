#include "genfitem.h"
#include <iostream.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fstream.h>

char get_item(FILE * file, char * str)
{
	char c;
	int i=0;
	/*		do
	{c=getc(file);
	if (c==' ') continue;
	else
	{ 
			 *(str+i++)=char(c);
	}
	}while(c!=' ' && c!='\n' && c!=EOF);
	 *(str+i)='\0';
     // cout<<str;
  //  cout<<" ";*/
	do
	{
		c=getc(file);
	}while(c==' ');
	do
	{  	*(str+i++)=char(c);
		c=getc(file);
	}while(c!=' '&& c!='\n' && c!=EOF && c!='\r' && c!='\t');
	*(str+i)='\0';
//	cout<<str;
  // cout<<" ";

	return c;
};

void outputlink(struct StrItem * head)
{struct StrItem * p;

	p=head;
	if (head!=NULL)
		do
		{   int j=0;
		    while(p->attr[j]!='\0')
			{cout<<p->attr[j];
			 j++;
			}
			cout<<" ";
			cout<<p->count<<";";
			p=p->next;
		}while(p!=NULL);
		else
			cout<<"Linktable is NULL"<<endl;

};

struct StrItem * creatlink(FILE * file)
{
	struct StrItem * head;
	struct StrItem * p1, * p2, *p3;
	
	head=NULL;
	int n=0;
	char c1;
    p1=p2=(struct StrItem *)malloc(LEN);
	char * str;
	str=(char *)malloc(10*sizeof(char));
	c1=get_item(file,str);
	int i=0;
	while(*(str+i)!='\0')
	 p1->attr[i]=*(str+i++);
	p1->attr[i]='\0';
	p1->count=1;
  //  free(str);

	while(c1!=EOF)
	{
		n=n+1;
		if(n==1) head=p1;
		else p2->next=p1;
		p2=p1;
		int fg=0;
	//	str=(char *)malloc(10*sizeof(char));
		do{
	    c1=get_item(file,str);

		p3=head;
        int flag,i;
		int m=0;
        if(head!=NULL)
        do
		{flag=1;i=0;
		  
        while(*(str+i)!='\0')
		{if(p3->attr[i]!=*(str+i)) {
			flag=0;
			break;}
		i++;
		}
            
        if (flag==1 && p3->attr[i]=='\0') {(p3->count)++;
                 break;}
        else
		{ p3=p3->next;
		  m++;}
		}while(m<n);
        if(flag==0)
		{  
	       p1=(struct StrItem *)malloc(LEN);
		   i=0;
	       while(*(str+i)!='\0')
		      p1->attr[i]=*(str+i++);
	       p1->attr[i]='\0';
	       p1->count=1; 
	       fg=1;
		};
		}while(fg!=1);
		//	free(str);
	};
		p2->next=NULL;
			

//output the linktable;
		
    outputlink(head);	
    free(str);
	return(head);

};

void get_freitem(struct StrItem * head,int &finum,int &oneinum)
{   struct StrItem * p; 
    p=head;
//	int finum=0;
//	int oneinum=0;
	if (head!=NULL)
		do
		{   if(p->count>10)
		{int j=0;
		    while(p->attr[j]!='\0')
			{cout<<p->attr[j];
			 j++;
			}
			cout<<" ";
			cout<<p->count<<";";
			finum++;
		}
			p=p->next;
			oneinum++;

		}while(p!=NULL);
		cout<<endl;
		getch();
//		cout<<"The number of frequent one itemset is "<<finum<<endl;
//		cout<<"There are "<<oneinum<<" different one items."<<endl;

}

double distance1(FILE * file1,FILE * file2)
{   int finum1(0),finum2(0),oneinum1(0),oneinum2(0);
    double d1,d2(0),sup1,sup2;
	struct StrItem * head1, * p1;
	struct StrItem * head2, * p2;
	head1=creatlink(file1);
	head2=creatlink(file2);
	get_freitem(head1,finum1,oneinum1);
	get_freitem(head2,finum2,oneinum2);
	d1=double(abs(finum1-finum2)+abs(finum2-finum1))/double(abs(finum1)+abs(finum2));
	cout<<"The first distance measure is "<<d1<<endl;
    p1=head1;
//	p2=head2;
	if (head1!=NULL)
		do
		{   sup1=0;
		    sup2=0;
			p2=head2;
			if(head2!=NULL)
			do
			{int j=0;
			 int flag=1;
		    while(p1->attr[j]!='\0' && p2->attr[j]!='\0')
			{if(p1->attr[j]!=p2->attr[j]) {
				flag=0;
				break;}
			    j++;
			}
			if(flag==1 && p2->attr[j]=='\0' && p1->attr[j]=='\0')
				{sup1=double(p1->count)/double(oneinum1);
			     sup2=double(p2->count)/double(oneinum2);
				 d2=d2+(sup1-sup2)*(sup1-sup2);

				 break;}
			else
		    p2=p2->next;
			}
			while(p2!=NULL);
			if(p2==NULL) {sup1=double(p1->count)/double(oneinum1);
			              sup2=0;
						  d2=d2+(sup1-sup2)*(sup1-sup2);}
	
			p1=p1->next;			

		}while(p1!=NULL);

//	p1=head1;
	p2=head2;
	if (head2!=NULL)
		do
		{   sup1=0;
		    sup2=0;
			p1=head1;
			if(head1!=NULL)
			do
			{int j=0;
			 int flag=1;
		    while(p2->attr[j]!='\0' && p2->attr[j]!='\0')
			{if(p2->attr[j]!=p1->attr[j]) {
				flag=0;
				break;}
			 j++;
			}
			if(flag==1 && p1->attr[j]=='\0' && p2->attr[j]=='\0')
				break;
			else
		    p1=p1->next;
			}
			while(p1!=NULL);
			if(p1==NULL) {sup2=double(p2->count)/double(oneinum2);
			              sup1=0;
						  d2=d2+(sup1-sup2)*(sup1-sup2);}
	        p2=p2->next;			

		}while(p2!=NULL);

	
	return d2;     
}
