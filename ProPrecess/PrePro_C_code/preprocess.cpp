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

void filecopy(FILE *ifp, char * szfilename) {/*read by lines*/
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

//This function is used to read the original title and Baidu_QA data sets
//ifp is the file point
//szfilename stores the texts line by line
//ccfile stores the cluster labels of the texts  
void filecopyTittle(FILE *ifp, char * szfilename, char *ccfile) {/* TNMF format*/
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

//This function is used to read the original Tweet and Tset data sets
//ifp is the file point
//szfilename stores the texts line by line
//ccfile stores the cluster labels of the texts 

void filecopyTittleT(FILE *ifp, char * szfilename, char *ccfile) {/* GSDMM format*/
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

//Transform the filetype of Title and Baidu_QA to Tweet and Tset
void filecopyTittleTermcut(char *orgfilename, char * szfilename) {/*GSDMM format*/
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

void filecopyTittleT1(FILE *ifp, char * szfilename, char *ccfile) {/*GSDMM format*/
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
		for(j=0;j < int(strlen(stringR)-2); j++)
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

void filecopyUtoL(char *orgname, char *szfilename) {/*GSDMM format*/
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
		{	if(string[i] >= '0' && string[i] <= '9' && i< int(strlen(string)-5))
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

//keep the short text with length large than 10
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
		if(wordlen >=10)
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
    FILE  *fp;
	int cluster, readtop;
	char filename[128], filterfile[128], fwords[128], docwordfile[128], topicwordfile[128], ccfile[128], topwordfile[128];
	//	char dfwords[128];
	//  This code is used to change the upcase to lowcase
	//	filecopyUtoL("youtube_title.txt", "youtube_title1.txt");
	//	exit(0);

	// This code is used to generate the file of TermCut format
	//  filecopyTittleTermcut("smsnew_title.txt", "smsnew_termcut.txt");
	// exit(0);

	//orignial file name
	sprintf(filename, "%s_title.txt", argv[1]);
	//extract text file with only words list for each line
	sprintf(filterfile,  "%s_text.txt",argv[1]);
	//extract groundthuth
	sprintf(ccfile,  "%s_cc.txt",argv[1]);
	//file contained with m words and their frequency
	sprintf(fwords, "%s_words.txt", argv[1]);
	//doc-words matrix
	sprintf(docwordfile, "%s_matrix.txt", argv[1]);
	//words id list of each topic
	sprintf(topicwordfile, "%s_topicwords.txt", argv[1]);
	//Top 20 words of each topic
	sprintf(topwordfile, "%s_topwords.txt", argv[1]);

	//file contained with m words and their frequency
	//	sprintf(dfwords, "%s_refwords.txt", argv[1]);



	int flag0=1;//extract texts and their labels

	if (flag0 || argc == 2)
	{	
		if ((fp=fopen(filename,"r"))==NULL)
		{	printf("1:cann't open file");
      		exit(0);
		}
    //After stemming, generate GSDMM format
	//	filecopyTittleT1(fp, filterfile,  "TSR_text.txt");
	//	exit(1);

		if(strstr(argv[1], "Title") || strstr(argv[1], "QA"))
		{
			printf("read tag format.\n");
			filecopyTittle(fp, filterfile, ccfile);//read baidu format
		}
		else
		{
			printf("read GSDMM format.\n");
			filecopyTittleT(fp, filterfile, ccfile);//read Tweet format
		}

		fclose(fp);

	}
	
	int flag1=1; //read words
	if(flag1)
	{
		if ((fp=fopen(filterfile,"r"))==NULL)
		{	
			printf("2:cann't open file");
			exit(0);
		}
		while(getword(MAXLEN, word, fp)!=0)
			list = addword(list, word);

		
		printwords(list, fwords);
		
		
	}
//	deletword(list, 60);
//	printwords(list, dfwords);

	if(flag0)//generate document-term matrix
	{
		rewind(fp);
		docwordmatirx(list, fp, docwordfile);
		
	}

	fclose(fp);

	if(argc==4)
	{

		cluster=atoi(argv[2]);
		readtop = atoi(argv[3]);

		//if readtop != 0
		//read top 20 words with largest pagerank centrality

		if(readtop)
		{
			int j;
			char strline[10*MAXLINE];
			int wordsidx[K][N]={0};
			
			if ((fp=fopen(topicwordfile,"r"))==NULL)
			{	
				printf("3: cann't open file");
				exit(0);
			}

			j=0;	
			while (fgets(strline, 10*MAXLINE, fp) != NULL)
			{
						
				sscanf(strline, "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d", &wordsidx[j][0], &wordsidx[j][1],&wordsidx[j][2],&wordsidx[j][3],&wordsidx[j][4],
					&wordsidx[j][5],&wordsidx[j][6],&wordsidx[j][7],&wordsidx[j][8],&wordsidx[j][9],&wordsidx[j][10], &wordsidx[j][11],&wordsidx[j][12],&wordsidx[j][13],&wordsidx[j][14],
					&wordsidx[j][15],&wordsidx[j][16],&wordsidx[j][17],&wordsidx[j][18],&wordsidx[j][19]);
				j++;
			}
			fclose(fp);
			//This function is used to extract the top N important words in each clusters
			printtops(list, wordsidx, cluster, N, topwordfile);
		}
	}

    return 0;
}

