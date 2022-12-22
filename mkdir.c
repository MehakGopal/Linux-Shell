#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>

int main(int argc,char **argv){
	if(argc>2 && argv[1][0]!='-'){
		printf("Cannot make more than one directory in a go\n");
		exit(1);
	}
	if(argc==2 && argv[1][0]!='-'){
		int m = mkdir(argv[1],0755);
		if(m!=0 && errno !=EEXIST){
			printf("mkdir not possible\n");
			exit(1);
		}
		if(errno = EEXIST && m!=0){
			perror("ALready exists");
			exit(EXIT_FAILURE);
		}
	}
	if(argv[1][0] == '-'){
		if(argv[1][1] == 'v'&& strlen(argv[1])==2){
			int m = mkdir(argv[2],0755);
			if(m!=0 && errno != EEXIST){
				printf("mkdir not possible\n");
				exit(1);
			}
			if(errno=EEXIST && m!=0){
				perror("Already Exists");
				exit(EXIT_FAILURE);
			}
			if(m==0){
				printf("mkdir: Directory created '%s'\n",argv[2]);
			}
		}
	
		else if(argv[1][1] == 'p'&& strlen(argv[1])==2){
			char dirName[3][1024];
			int no = 0;
			int j = 0;
			for(int i = 0;i<strlen(argv[2]);i++){
				if(argv[2][i] == '/'){
					no++;
					j=0;
				}
				else{
					dirName[no][j] = argv[2][i];
					j++;
				}
			}
			int m = mkdir(dirName[0],0755);
			if(no==0)exit(1);
			strcat(dirName[0],"/");
			strcat(dirName[0],dirName[1]);
			mkdir(dirName[0],0755);
			if(no==1)exit(1);
			strcat(dirName[0],"/");
			strcat(dirName[0],dirName[2]);
			mkdir(dirName[0],0755);
			if(no==2)exit(1);
		}
		else{
			perror("Not a viable option");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
						
}
