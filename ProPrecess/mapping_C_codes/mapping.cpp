// preprocess.cpp : Defines the entry point for the console application.
//

#include "getwordlist.h"

int strpos(char *str, char * substr)
{
	char *p;
	int i;
	for(p=str, i=0; p<str+strlen(str); p++, i++)
		if(strncmp(p, substr, strlen(substr)) == 0)
			return i;
	return -1;

}

void filecopy(FILE *ifp, char * szfilename) {/*行式文件读取*/
	char string[MAXLINE];
	int i,position;
	FILE *ofp;
	
	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("cann't open file");
      	exit(1);
    }
	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		position = strpos(string, "http");
		for(i=0; i<position-2; i++)
		 fputc(string[i], ofp);
		fputc('\n', ofp);
	}
	fclose(ofp);
}

void filecopyTittle(FILE *ifp, char * szfilename, char *ccfile) {/*行式文件读取:tnmf format*/
	char string[MAXLINE], temp0=0, temp1;
	int i, count=0, line = 1;
	FILE *ofp;

	FILE *cc;

	if ((cc=fopen(ccfile,"w"))==NULL)
    {	printf("4: cann't open file");
      	exit(1);
    }
	
	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("5: cann't open file");
      	exit(1);
    }
	//fprintf(ofp, "%d\n", 2630);
	int flag=1;
	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		if(flag)
		{
			for(i=0; string[i] != '|'; i++)
				printf("%c", string[i]);
			printf("\n");
			flag=0;
		}
		else
			for(i=0; string[i] != '|'; i++);

		fputs(string+i+1, ofp);
	
		temp1 = string[i-1];
		if(temp1 == temp0)
			fprintf(cc, "%d\t%d\n", line, count);
		else
		{
			count++;
			fprintf(cc,  "%d\t%d\n", line, count);
			flag=1;

			//output clusters tags.
			/*for(int j=0; j<i; j++)
				fputc(string[j],cc);
			fputc( '\n',cc);*/
			
			temp0 = temp1;
			
		}
		line++;
	}
	printf("clusters: %d\n", count);
	printf("lines: %d\n", line);
	fclose(cc);
	fclose(ofp);
}
void readyoutube(FILE *ifp, char * szfilename, char *ccfile) {/*行式文件读取:tnmf format*/
	char string[MAXLINE], temp0=0, temp1;
	int i, count=0, line = 1;
	FILE *ofp;

	FILE *cc;

	if ((cc=fopen(ccfile,"w"))==NULL)
    {	printf("4: cann't open file");
      	exit(1);
    }
	
	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("5: cann't open file");
      	exit(1);
    }

	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		for(i=0; string[i] != '|'; i++);
	
		temp1 = string[i-1];
		if(temp1 == temp0)
			fprintf(cc, "%d\t%d\n", line, count);
		else
		{
			count++;
			fprintf(cc,  "%d\t%d\n", line, count);

			//output clusters tags.
			/*for(int j=0; j<i; j++)
				fputc(string[j],cc);
			fputc( '\n',cc);*/
			
			temp0 = temp1;
			
		}

		for(i++;string[i]!='|'; i++)
			if(string[i]<128 && string[i]>=0)
			{
				if(string[i]>='A' && string[i]<='Z')
					string[i]=string[i]+32;
				fputc(string[i], ofp);
			}
		fputc('\n',ofp);
				
		line++;
	}
	printf("clusters: %d\n", count);
	fclose(cc);
	fclose(ofp);
}

void readyoutubetitle(FILE *ifp, char * szfilename, char *ccfile) {/*行式文件读取:tnmf format*/
	char string[MAXLINE], temp0=0, temp1;
	int i, count=0, line = 1;
	FILE *ofp;

	FILE *cc;

	if ((cc=fopen(ccfile,"w"))==NULL)
    {	printf("4: cann't open file");
      	exit(1);
    }
	
	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("5: cann't open file");
      	exit(1);
    }

	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		for(i=0; string[i] != '|'; i++);
	
		temp1 = string[i-1];
		if(temp1 == temp0)
			fprintf(cc, "%d\t%d\n", line, count);
		else
		{
			count++;
			fprintf(cc,  "%d\t%d\n", line, count);

			//output clusters tags.
			/*for(int j=0; j<i; j++)
				fputc(string[j],cc);
			fputc( '\n',cc);*/
			
			temp0 = temp1;
			
		}

		for(i++;string[i]!='|'; i++);
		for(i++; string[i]!='\n'; i++)
			if(string[i]<128 && string[i]>=0)
			{
				if(string[i]>='A' && string[i]<='Z')
					string[i]=string[i]+32;
				fputc(string[i], ofp);
			}
		fputc('\n',ofp);
				
		line++;
	}
	printf("clusters: %d\nlines: %d", count, line);
	fclose(cc);
	fclose(ofp);
}
void filecopyTittleT(FILE *ifp, char * szfilename, char *ccfile) {/*行式文件读取: GSPMM format*/
	char string[MAXLINE];
	int i,line=1;

	FILE *ofp;
	FILE *cc;
	
	if ((cc=fopen(ccfile,"w"))==NULL)
    {	printf("6:cann't open file");
      	exit(1);
    }

	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("7:cann't open file");
      	exit(1);
    }
	
//	fprintf(ofp, "%d\n", 2472);

	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		for(i=0; string[i] != ':'; i++);
		for(i+=3; string[i] != '"'; i++)
			fputc(string[i], ofp);
		fputc('\n', ofp);

		fprintf(cc, "%d\t", line);
		for(; string[i] != ':'; i++);
		for(i+=1; string[i] != '}'; i++)
			fputc(string[i], cc);
		fputc('\n', cc);
		line++;
	}
	fclose(cc);
	fclose(ofp);
}
void filecopyTittleTermcut(char *orgfilename, char * szfilename) {/*行式文件读取: GSPMM format*/
	char string[MAXLINE], temp[MAXLINE];
	int i,j,line=1;

	FILE *ofp;
	FILE *ifp;

	if ((ifp=fopen(orgfilename,"r"))==NULL)
    {	printf("6:cann't open file");
      	exit(1);
    }

	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("7:cann't open file");
      	exit(1);
    }
	
//	fprintf(ofp, "%d\n", 2472);

	while (fgets(string, MAXLINE, ifp) != NULL)
	{	j=0;
		for(i=0; string[i] != ':'; i++);
		for(i+=3; string[i] != '"'; i++)
		{
			temp[j]=string[i];
			j++;
		}
		temp[j]='\0';
		

		fprintf(ofp, "%d\t", line);
		for(; string[i] != ':'; i++);
		for(i+=2; string[i] != '}'; i++)
			fputc(string[i], ofp);
		fputc('|', ofp);

		for(j=0; temp[j] != '\0'; j++)
			fputc(temp[j], ofp);
		fputc('\n', ofp);

		line++;
	}
	fclose(ifp);
	fclose(ofp);
}
void filecopyTittleT1(FILE *ifp, char * szfilename, char *ccfile) {/*行式文件读取: GSPMM format*/
	char string[MAXLINE],stringR[MAXLINE];
	int i,j,line=1;

	FILE *ofp;
	FILE *cc;
	
	if ((cc=fopen(ccfile,"r"))==NULL)
    {	printf("6:cann't open file");
      	exit(1);
    }

	if ((ofp=fopen(szfilename,"w"))==NULL)
    {	printf("7:cann't open file");
      	exit(1);
    }
	
//	fprintf(ofp, "%d\n", 2472);

	while (fgets(string, MAXLINE, ifp) != NULL && fgets(stringR, MAXLINE, cc) != NULL)
	{
		for(i=0; string[i] != ':'; i++)
			fputc(string[i], ofp);
		for(; string[i] != '"'; i++)
			fputc(string[i],ofp);
		for(i++; string[i] != '"'; i++)
		{
			//fputc(string[i], ofp);
		}
		fputc('"',ofp);
		//for(j=0;stringR[j]!='\n'; j++)
		for(j=0;j < strlen(stringR)-2; j++)
			fputc(stringR[j], ofp);
		fputc('"',ofp);

		for(i+=1; string[i] != '\n'; i++)
		{
			fputc(string[i], ofp);
		}
		fputc('\n',ofp);
		line++;	
		printf("%d\n", line);
	}

	fclose(cc);
	fclose(ofp);
}

void printtops(LINK list, int idx[K][N], int cluster, int topn, char filename[])
{
	LINK p;
	FILE *fp;
	if((fp=fopen(filename, "w")) == NULL)
	{
		printf("6:canopen\n");
		exit(3);
	}
	int i, j, k;
	for(j=0; j<cluster; j++)
	{
		for(k=0; k<topn; k++)
		{
			p=list;
			for(i=1; i<idx[j][k]; i++)
				p=p->next;
			fprintf(fp, "%s\t%d\t", p->word, p->count);
		}
		fprintf(fp, "\n");
	}
	fclose(fp);
}

void printtfidftops(LINK list, int idx[], int topn)
{
	LINK p;
	FILE *fp;
	if((fp=fopen("F:\\test.txt", "w")) == NULL)
	{
		printf("6:canopen\n");
		exit(3);
	}
	int i, k;
	for(k=0; k<topn; k++)
	{
		p=list;
		for(i=1; i<idx[k] && p->next !=NULL; i++)
			p=p->next;
		fprintf(fp, "%s\t%d\n", p->word, p->count);
	}

	fclose(fp);
}

void filecopyUtoL(char *orgname, char *szfilename) {/*行式文件读取: GSPMM format*/
	char string[MAXLINE];
	int i,line=1;

	FILE *ifp;
	FILE *cc;


	if ((ifp=fopen(orgname,"r"))==NULL)
    {	printf("7:cann't open file");
      	exit(1);
    }
	
	if ((cc=fopen(szfilename,"w"))==NULL)
    {	printf("6:cann't open file");
      	exit(1);
    }	
//	fprintf(ofp, "%d\n", 2472);

	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		for(i=0; string[i] != '\n'; i++)
		{	if(string[i] >= '0' && string[i] <= '9' && i<strlen(string)-5)
				//fputc(string[i]+32, cc);
				continue;
			else
				fputc(string[i], cc);
		}
		fputc('\n', cc);
		line++;
		printf("%d\n", line);
	}
	fclose(cc);
	fclose(ifp);
}

void select(char *szorg, char *szfinal)
{
	char string[MAXLINE];
	int line=0,wordlen;

	FILE *ifp;
	FILE *ofp;


	if ((ifp=fopen(szorg,"r"))==NULL)
    {	printf("11:cann't open file");
      	exit(1);
    }
	
	if ((ofp=fopen(szfinal,"w"))==NULL)
    {	printf("12:cann't open file");
      	exit(1);
    }	

	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		wordlen=wordCount(string);
		if(wordlen >=6)
		{
			fputs(string, ofp);
			line++;
		}
	}
	printf("total lines: %d\n", line);
}

void generate(char *szorg, char *szfinal)
{
	char string[MAXLINE];
	int i, line=1,count=1;

	FILE *ifp;
	FILE *ofp;


	if ((ifp=fopen(szorg,"r"))==NULL)
    {	printf("11:cann't open file");
      	exit(1);
    }
	
	if ((ofp=fopen(szfinal,"w"))==NULL)
    {	printf("12:cann't open file");
      	exit(1);
    }	

	while (fgets(string, MAXLINE, ifp) != NULL)
	{
		if(! strstr(string, "+++++++"))
		{
			fprintf(ofp, "%d\t%d|", line, count);
			for (i=0; string[i] !='\0'; i++)
				fputc(string[i], ofp);
			line++;
		}
		else
		{
			count++;
			fprintf(ofp, "%d\t%d|", line, count);
			for (i=0; string[i] !='\0'; i++)
				fputc(string[i], ofp);
			line++;
		}

	}
	printf("total cluster %d and lines: %d\n", count, line);
}


LINK list = NULL;
char word[MAXLEN];

int main(int argc, char *argv[])
 {
    FILE  *fp1, *fp2;
	char filename[128], filterfile[128], docwordfile[128];
	//	char dfwords[128];

	if (argc<3)
	{
		printf("input argument error\n");
		printf("please input two parameters: filename clusternum.\n");
		return 0;
	}



	//orignial file name
	sprintf(filename, "%s_text.txt", argv[1]);
	//extract text file
	sprintf(filterfile,  "%s_text.txt",argv[2]);

	//doc-words matrix
	sprintf(docwordfile, "%s_sample_matrix.txt", argv[2]);
	//words id list of each topic


	if ((fp1=fopen(filename,"r"))==NULL)
	{	
		printf("1:cann't open file");
		exit(0);
	}

	if ((fp2=fopen(filterfile,"r"))==NULL)
	{	
		printf("2:cann't open file");
		exit(0);
	}
	while(getword(MAXLEN, word, fp2)!=0)
		list = addword(list, word);

//	printwords(list);

	docwordmatirx(list, fp1, docwordfile);

	fclose(fp2);
	fclose(fp1);


    return 0;
}

