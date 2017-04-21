#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

enum {MAXLEN = 128};
enum {MAXLINE=10000};
enum {K=200, N=20};


typedef struct node NODE, *LINK;
struct node//定义链接结构
{
	char word[MAXLEN];
	int count;
	LINK next;
};


int getword(int limit, char w[], FILE *fp);
LINK mknode(char w[]);
LINK addword(LINK list, char w[]);
LINK deletword(LINK list, int highest);
void printwords(LINK l, char file[]);
void docwordmatirx(LINK list, FILE *ifp, char * docwordfile);
int wordCount(char *string);