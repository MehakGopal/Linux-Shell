#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/stat.h>
#include<string.h>

void ls(const char *d,int _a,int _s){
	struct dirent *dir;
	struct stat ss;
	DIR *obj = opendir(d);
	int total =0;
	if(!obj){
		if(errno = ENOTDIR){
			perror("Not a directory");//path is not correct or doesn't exist
		}
		else if(errno = ENOENT){
			perror("Not a file or directory");//basically when it's not a directory 
                }
		else{
			perror("Unable to read directory");//any other undefined error
		}
		exit(EXIT_FAILURE);
	}
	while((dir = readdir(obj))!= NULL){
		if(!_a && dir->d_name[0] == '.'){
			continue;
		}
		printf("%s ",dir->d_name);
		if(_s){
			if(stat(dir->d_name,&ss) == 0){
				printf(" %d  ", (int)ss.st_blocks/2);
				total+= ((int)ss.st_blocks/2);
			}
		}
		if(!_s){printf("  ");}
	}
	if(_s){printf("\ntotal %d", total);}
	printf("\n");
}

int main(int argc,const char *argv[]){
	if(argc==1){
		ls(".",0,0);
	}
	else if(argc ==2){
		int _a=0,_s=0;
		if(argv[1][0] == '-'){
		char p =argv[1][1];
		if(p =='a'&& strlen(argv[1])==2)_a=1;
		else if(p=='s'&& strlen(argv[1])==2)_s=1;
		else{
			perror("Option not available");
			exit(EXIT_FAILURE);
		}
		ls(".",_a,_s);
		}
		else{
			ls(argv[1],_a,_s);
		}
	}
	return 0;
}

