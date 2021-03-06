#include "getwordlist.h"
extern char word[MAXLEN];
int getword(int limit, char w[], FILE *fp)
 {
	int c, i = 0;
	while(i<limit-2 && (c=fgetc(fp))!=EOF && c!='\n' && c!=' ' && c !='\t')
 	{
		word[i] = c;  ++i;
	} 
	word[i] = '\0';   
	return i;
}

LINK mknode(char w[])  //Creat a node node
{	LINK p = (LINK)malloc(sizeof(NODE));
	if(p != NULL)
	{	strncpy(p->word, w, MAXLEN);
		p->count = 1;
		p->next = NULL;
	}
	return p;
}

LINK addword(LINK list, char w[]) 
//Creat a link by adding word one by one
{	LINK p;
	if (list == NULL) return mknode(w);
	for(p=list; ; p=p->next)
	{	if(strcmp(p->word,w)==0)
		{	p->count++;
			break;
		}
		if(p->next == NULL)
		{	p->next = mknode(w);
			break;
		}
	}
	return list;
}

LINK deletword(LINK list, int highest) 
//delelt a node
{	LINK p, q;
	if (list == NULL) return list;
	for(q=p=list; ; p=p->next)
	{
		if(p->count > highest)
		{	
			printf("%s\t%d\n", p->word, p->count);
		//	q->next=p->next;
		//	free(q);
		}
		q=p;	
		if(p->next == NULL)
		{
			break;
		}
	
	}
	return list;
}



void printwords(LINK p, char filename[])    //print the link
{
	int count = 0;
	FILE *fp;

	if ((fp=fopen(filename,"w"))==NULL)
	{	printf("1:cann't open file");
      	exit(0);
	}

	for(; p!=NULL; p=p->next)
	{
		fprintf(fp, "%d %s\n", p->count, p->word);
		count++;	
	}

	printf("total words: %d\n", count);

	fclose(fp);
}


void docwordmatirx(LINK list, FILE *ifp, char * docwordfile)
{
	char string[MAXLINE];
	FILE *ofp;
	LINK p;
	
	if ((ofp=fopen(docwordfile,"w"))==NULL)
    {	printf("cann't open file");
      	exit(2);
    }
	while (fgets(string, MAXLINE, ifp) != NULL)
	{
			for(p=list; p!=NULL; p=p->next)
			{
				if(p->next != NULL)
				{
					if(strstr(string, p->word))
						fprintf(ofp, "%d\t", 1);
					else
						fprintf(ofp, "%d\t", 0);
				}
				else
				{
					if(strstr(string, p->word))
						fprintf(ofp, "%d\n", 1);
					else
						fprintf(ofp, "%d\n", 0);
				}
		
			}
				
	}
	fclose(ofp);
}

int wordCount(char *string) 
{
   int c = ' ', count = 0, i=0;
   while (c != '\n') 
	{
      while ((c=string[i]) != '\n' && 
             (c==' ' || c=='\t'))
          i++;
      if (c == '\n') break;
      ++count;
      while ((c=string[i]) != '\n' && 
           c!=' ' && c!='\t')
          i++;
   }
 //  printf("word count: %d\n", count);
   return count;
}

