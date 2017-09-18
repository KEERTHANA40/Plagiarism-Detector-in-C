#include<stdio.h>
#include<string.h>
#include<math.h>
#include "Multiple_files.h"     //Included Multiple_files header file


int Contains(char text[], char words[][100],int length);        //Checks whether word is present or not.
int SplitWords(char str[],char words[][100],int count[]);       //Splits the words if spaces and special characters are present.

/*The function below splits the words when spaces and special characters are present*/
int SplitWords(char str[],char words[100][100],int count[])
{
    int i=0,j=0,k=0,index;
    strlwr(str); 
    for(i=0;i<strlen(str);i++)
    {
        char temp[100] = {'0'};
        if(str[i]!=' ')
        {
            while(i<strlen(str)&&str[i]!=' ')
            {
                int asc=(int)str[i];
                if(asc>=65&&asc<=91||asc>=97&&asc<=122||asc>=48&&asc<=57)
                {
                    temp[k]=str[i];
                    k++;
                    i++;
                }
                else
                {
                    i++;
                }
            }
            temp[k]='\0';
        }
        else
        {
            i++;
        }
        
        index = Contains(temp,words,j);
        if(index==-1)
        {
            int d=0;    
            while(temp[d]!='\0')
            {
                words[j][d]=temp[d];
                d++;
            }
            words[j][d]='\0';
            count[j] = 1;
                j++;
            k=0;
        }
        else
        {
            memset(temp,0,strlen(temp));
            count[index]++;
            k=0;
        }
    }
    return j;
}

/*Function below checks whether word is present or not*/
int Contains(char text[], char words[][100],int length)
{
    int a=0;
    for(a=0;a<length;a++)
    {
        if(strcmp(text,words[a])==0)
        return a;
    }
    return -1;
}

/*Plagiarism Percentage is calculated for several files in the below function*/
float plagcal(int wordsLength,int wordsLength2,char words[1000][100],char words2[1000][100],int count[],int count2[])
{
    int i,j;
    int Norm1=0,Norm2=0,Dotsum=0;
    float Result;
    for(i=0;i<wordsLength;i++)
    {
        for(j=0;j<wordsLength2;j++)
        {
            if(strcmp(words[i],words2[j])==0)
            {
                Dotsum += count[i]*count2[j];
            }
        }
    }
    for(i=0;i<wordsLength;i++)
    {
        Norm1 += count[i]*count[i];
    }
    float res1=sqrt(Norm1);
    for(i=0;i<wordsLength2;i++)
    {
        Norm2 += count2[i]*count2[i];
    }
    float res2=sqrt(Norm2); 
    Result = ((Dotsum*100.0)/(res1*res2));
    return Result;
}

int main()
{
    int i,j=0,k=0;
    int wordsLength,wordsLength2;
    char file[100][100];
    int len=mul_files(file);
    float res[len][len];

    /*Files from header file "Multiple_files.h" are opened and read here*/
    for(i=0;i<len;i++)
    {
        char str[10000] = {0}; 
        char words[100][100] = {'0'};
        int count[100]={0};
        FILE *fp;
        fp = fopen(file[i],"r");
        fgets(str,1000,(FILE*)fp);
        wordsLength = SplitWords(str,words,count);
        for(j=0;j<len;j++)
        {
            char str2[10000] = {0};
            char words2[100][100] = {0};
            int count2[100] = {0};
            FILE *fp2;
            fp2 = fopen(file[j],"r");
            fgets(str2,1000,(FILE*)fp2);
            wordsLength2 = SplitWords(str2,words2,count2);
            float Result=plagcal(wordsLength,wordsLength2,words,words2,count,count2);
            res[i][j]=Result;
        }
    }

    /*Function below prints the plagariased output in matrix file*/
    printf("\n");
    printf("\t   ");
    for(i=0;i<len;i++)
    {
        printf("  %s    ",file[i]);
    }
    printf("\n");
    for(i=0;i<len;i++)
    {
        printf("%s    ",file[i]);
        for(j=0;j<len;j++)
        {
        printf("  %.2f\t  ",res[i][j]);
        }
        printf("\n");
    }   
}
