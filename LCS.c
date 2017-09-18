#include<stdio.h>
#include<string.h>
#include "Multiple_files.h"     //Included Multiple_files header file

/*Function below splits the words by not considering/ignoring spaces*/
int SplitWords(char str[],char words[][100])
{
    int i=0,j=0,k=0;
    strlwr(str);
    for(i=0;i<strlen(str);i++)
    {
        if(str[i]==' '|str[i]=='?'|str[i]==',')
        {
            while(i+1<strlen(str) && (str[i+1]==' '|str[i+1]=='?'|str[i+1]==','))
                i++;
                words[k][j] = '\0';
                j++;
                k=0;
        }
        else
        {
            if(str[i]!='\n')
            {                
                words[j][k] = str[i];
                k++;
            }
        }
    }
    words[j][k] = '\0';
    return j;
}

/*Function below prints the plagariased output in matrix file*/
void matrix(char file[100][100], float res[100][100], int len)
{
    int i=0,j=0;
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

/*In main function all the functions created above are called and the final output is calculated below.*/
int main()
{
    int i,j=0,k=0;
    int WordsLength,WordsLength2;
    char file[100][100];
    int count = 0,count2=0,temp;
    float res[100][100];
    int len=mul_files(file);
    float percentage;
    
    /*Files from header file "Multiple_files.h" are opened and read here*/
    for(i=0;i<len;i++)
    {
        char str[10000] = {0}; 
        char Words[100][100] = {'0'};
        FILE *fp;
        fp = fopen(file[i],"r");
        fgets(str,1000,(FILE*)fp);
         WordsLength = SplitWords(str,Words);
        for(j=0;j<len;j++)
        {
            if(strcmp(file[i],file[j])==0)
            {
                res[i][j]=100.0;
            }
            else
            {
                char str2[10000] = {0};
                char Words2[100][100] = {0};
                FILE *fp2;
                fp2 = fopen(file[j],"r");
                fgets(str2,1000,(FILE*)fp2);
                WordsLength2 = SplitWords(str2,Words2);
                int len1=strlen(str);
                int len2=strlen(str2);
                int maxcount=0;
                
                /*Plagiarism between files is calculated below*/
                for(k=0;k<=WordsLength;k++)
                {
                    int s=0;
                    count2=0;
                    int temp=k;
                    for(s=0;s<=WordsLength2;s++)
                    {
                        if(strcmp(Words[temp],Words2[s])==0)
                        {
                            while((s<=WordsLength2) && (strcmp(Words[temp],Words2[s])==0))
                            {
                                count2 += strlen(Words[temp]);   
                                temp++;
                                s++;
                            }
                        } 
                        if(count2>maxcount)
                        {
                            maxcount=count2;
                        }           
                    }
                }
                percentage = (maxcount*200.0)/(len1+len2);
                res[i][j] = percentage;

            }
        }
    }
    matrix(file,res,len); //Calling the function "matrix" to print the output in matrix form.
    

}