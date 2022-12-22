#include<stdio.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>

int main(int argc,char **argv){
	char permission;
	int i = argc;
	struct stat name;
	if(argv[1][0]!='-'){
		stat(argv[1],&name);
		if(S_ISREG(name.st_mode)==0&&access(argv[1],F_OK)==0){
			printf("rm: Cannot remove '%s':Is a directory\n",argv[1]);
			exit(1);
		}
		if(access(argv[1],F_OK)!=0){
			perror("File doesn't exist");
			exit(EXIT_FAILURE);
		}
		int m= remove(argv[1]);
//		printf("Done");
	}
	if(argv[1][0]=='-'){
		if(argv[1][1]=='i'&& strlen(argv[1])==2){
			stat(argv[2],&name);
			if(S_ISREG(name.st_mode)==0 && access(argv[2],F_OK)==0){
				printf("rm: Cannot remove '%s':Is a directory\n",argv[2]);
				exit(1);
			}
			if(access(argv[2],F_OK)!=0){
				perror("File doesn't exist");
				exit(EXIT_FAILURE);
			}
			printf("rm: remove regular file '%s'?",argv[2]);
			scanf("%c",&permission);
			if(permission=='y'){
				int m = remove(argv[2]);
			}
			else{
				exit(1);
			}
		}
		else if(argv[1][1] == 'r'){
			int m = remove(argv[2]);
		}
		else{
			perror("Not a viable option");
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}
