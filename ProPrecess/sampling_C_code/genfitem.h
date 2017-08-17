#include <stdio.h>
#include <string.h>

#define LEN sizeof(struct StrItem)

struct StrItem
{
	char attr[10];
	long count;
	struct StrItem * next;
};

class ScanItems
{
public:
	StrItem item;
	FILE * infile;

public:
	char get_item(FILE *infile,char * str);
	struct StrItem * creatlink(FILE * file);
	void outputlink(struct StrItem * head);
	void get_freitem(struct StrItem * head,int &finum,int & oneinum);
	double distance(FILE * file1, FILE * file2);
};

