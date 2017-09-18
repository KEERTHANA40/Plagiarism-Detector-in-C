#include <stdio.h>
#include <string.h>
#include <dirent.h>

/*Multiple files of type "txt" are taken here and called to main funtion*/
int mul_files(char file[100][100])
{
	char f[100];
	printf("Enter the path of directory:");
	scanf("%[^\n]s",f);
	chdir(f);
	DIR *d;
	int i=0,j;
	struct dirent *dir;
	d = opendir(f);
	{
		while((dir = readdir(d)) != NULL)
		{
			int k = strlen(dir->d_name);
			if(dir->d_name[k-1] == 't' && dir->d_name[k-2] == 'x' && dir->d_name[k-3] == 't')
			{
				j=0;
				while(j<k)
				{
					file[i][j] = dir->d_name[j];
					j++;
				}
				i++;

			}
		}
	closedir(d);
	
	}
return i;
}
