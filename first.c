#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>



void filter(const char**,int n);
char* myStrstr(const char*,const char*);


int main()
{
	int BUF_SIZE=16;
	int SIZE_STRING=8;
	char c='1';
	int i=0,j=0;
	int flag=0;
	char *str=(char*)calloc(BUF_SIZE+1,sizeof(char));
	if(str==NULL)
	{
		printf("[error]");
	}
	char **mas_str=(char**)calloc(SIZE_STRING,sizeof(char*));
        if(mas_str==NULL)
        {
                printf("[error]");
        }
	while((c!='\n' || flag!=1))
	{
		i=0;
		scanf("%c",&c);
		if(feof(stdin))
			break;
		if(c=='\n')
			flag=1;
		else
		{
			if(j>=SIZE_STRING)
			{
				mas_str=(char**)realloc(mas_str,SIZE_STRING+2);
				SIZE_STRING+=2;
			}
			flag=0;
			mas_str[j]=(char*)calloc(BUF_SIZE+1,sizeof(char));
			while(c!='\n')
			{
				if(i>=BUF_SIZE)
				{
					mas_str[j]=(char*)realloc(mas_str[j],BUF_SIZE+5);
					BUF_SIZE+=5;
				}
				mas_str[j][i++]=c;
				scanf("%c",&c);
				if(feof(stdin))
					break;
			}
			mas_str[j][i++]='\0';
			j++;
		}
		if(feof(stdin))
			break;
	}
	filter((const char**)mas_str,j);
	for(i=0;mas_str[i];i++)
	{
		free(mas_str[i]);
	}
	free(mas_str);
	free(str);
	return 0;
}

void filter(const char** mas_str,int n)
{
	int SIZE=16;
	char* str=(char*)calloc(SIZE+1,sizeof(char));
	for(int i=0;i<n;i++)
	{
		if(i>=SIZE)
		{
			str=(char*)realloc(str,SIZE+5);
			SIZE+=5;
		}
		if(mas_str[i][0]==' ')
			continue;
		while(strlen(mas_str[i])>=SIZE)
		{
			str=(char*)realloc(str,SIZE+16);
			SIZE+=16;

		}
		sscanf(mas_str[i],"%s[a-zA-Z 0-9\\n\\0]",str);
		if((myStrstr(str,"From:")-str)==0)
		{
			printf("%s\n",mas_str[i]);
			continue;
		}
		if((myStrstr(str,"Date:")-str)==0)
		{
			printf("%s\n",mas_str[i]);
			continue;
		}
                if((myStrstr(str,"To:")-str)==0)
                {
                        printf("%s\n",mas_str[i]);
			continue;
                }
                if((myStrstr(str,"Subject:")-str)==0)
                {
                        printf("%s\n",mas_str[i]);
			continue;
                }		
	}
	free(str);
}

char* myStrstr(const char *string1, const char *string2)
{
  	int i, j, n=strlen(string2);
      	for(i=0,j=0;string1[i]; i++, j++)
        {
		if (string1[i]!=string2[j]) 
			return NULL;
                if (j==n-1)
		{
			return ((char*)string1+i-n+1);
		}
        }
    	return NULL;
}


