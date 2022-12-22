#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#define LEN 1024

int main(int argc,char **argv){
	char buf[LEN] = {0};
	time_t rt = time(NULL);
	struct stat attr;
	struct tm *ptm = localtime(&rt);
	if(argc==1){
		strftime(buf,LEN,"%a %b %e %r %Z %Y",ptm);
		puts(buf);
		exit(1);
	}
	else if(argv[1][0] == '-' && argv[1][1] == 'u'&& strlen(argv[1])==2){
		ptm = gmtime(&rt);
		strftime(buf,LEN,"%a %b %e %r UTC %Y",ptm);
		puts(buf);
		exit(1);
	}
	else if(argv[1][0] == '-' && argv[1][1] == 'r'&&argc>1&& strlen(argv[1])==2){
		stat(argv[2],&attr);
		if(access(argv[2],F_OK)!=0){
			perror("File doesn't exist");
			exit(EXIT_FAILURE);
		}
		ptm = localtime(&(attr.st_ctime));
		strftime(buf,LEN,"%a %b %e %r %Z %Y",ptm);
		puts(buf);
		exit(1);
	}
	else{
		perror("Not a viable option");
		exit(EXIT_FAILURE);
	}
	return 0;
}
