#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<errno.h>

int main(int argc,char **argv){
	int _n=0,_E=0;
	int o;
	while((o = getopt(argc,argv,"Een?"))!=-1){
		switch(o){
			case 'E':
				_E++;
				break;
			case 'n':
				_n++;
				break;
			case 'e':
				_E++;
				break;
			case '?':
				perror("Not a viable option");
				exit(EXIT_FAILURE);
		}
	}
	const int bS = 4096;
	char buff[bS];
	int cf = optind;
//	printf("%d %d",cf,argc);
	FILE *f;
	while(cf<=argc){
		if(cf!=argc){
			f = fopen(argv[cf],"rb");
			if(f==NULL){
				perror("No such file or directory");
				exit(EXIT_FAILURE);
			}
		}
		int line_number = 1;
		while(fgets(buff,bS,(f==NULL?stdin:f))){
			int len = strlen(buff);
			buff[len-1] = '\0';
			if(_n){
				char *tmp = strdup(buff);
			//	buff[0] = '\0';
				sprintf(buff,"%*d\t",6,line_number++);
				strcat(buff,tmp);
			}
			if(_E){
				len = strlen(buff);
				buff[len] = '$';
				buff[len+1] = '\0';
			}
			fprintf(stdout,"%s\n",buff);
		}
		fclose(f);
		cf++;
		if(cf==argc)exit(1);
	}
	return 0;
}
