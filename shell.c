#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/types.h>
#include<sys/wait.h>
#define MAX 1000

void *thread(void *arg){
	char *ret;
	ret = (char*)malloc(50);
	system(arg);
	strcpy(ret,"Thank you for using the shell!");
	pthread_exit(ret);
}
void cd(char output[MAX][10]){
	char cwd[1024];
//	printf("%s\n",getcwd(cwd,sizeof(cwd)));
	output[1][strlen(output[1])-1] = '\0';
	if(output[1][0] == '.' && strlen(output[1])==3){
		if(output[1][1] !='.')exit(0);
	}
	printf("%s\n",getcwd(cwd,sizeof(cwd)));
	chdir(output[1]);
	printf("%s\n",getcwd(cwd,sizeof(cwd)));
}
void echo(char output[MAX][10],char str[MAX]){
	if(strcmp(output[1],"*\n")!=0 && strcmp(output[1],"-n")!=0){
		for(int i = 5;i<strlen(str)-1;i++){
			printf("%c",str[i]);
		}
		printf("\n");
	}
	if(strcmp(output[1],"*\n")==0){
		system("./ls");
	}
	if(strcmp(output[1],"-n")==0){
		for(int i =8;i<strlen(str);i++){
			if(str[i] == '\n'){
				break;
			}
			else{
				printf("%c",str[i]);
			}
		}
	}
}

void pwd(){
	char cwd[1024];
	getcwd(cwd,sizeof(cwd));
	printf("%s\n",cwd);
}

int main(){
	char str[MAX];
	int flag;
	printf("Welcome to my shell!\n");
	printf("Here are the commands that this shell can handle:\n");
	printf("1) cd(.. and /)\n");
	printf("2) echo(* and -n)\n");
	printf("3) pwd(-L and -P)\n");
	printf("4) ls (-a and -s)\n");
	printf("5) date (-u and -r)\n");
	printf("6) cat (-n and -E)\n");
	printf("7) rm (-r and -i)\n");
	printf("8) mkdir (-v and -p)\n");
	printf("Enter your input: ");
	fgets(str,MAX,stdin);
//	printf("%s",str);
	int j = 0,m = 0;
	char output[MAX][10];
	for(int i = 0;i<strlen(str);i++){
		if(str[i]== ' ' || str[i] == '\0'){
	//		output[m][j] = '\0';
			m++;
			j=0;
		}
		else{
			output[m][j] = str[i];
			j++;
		}
	}
//	printf("%s %d",output[0],strlen(str));
	if(strcmp(str,"pwd -L\n")==0|| strcmp(str,"pwd -P\n")==0|| strcmp(str,"pwd\n")==0){
		pwd();
		exit(0);
	}
	if(strcmp(output[0],"cd")==0){
		cd(output);
		exit(0);
	}
	if(strcmp(output[0],"echo")==0){
		echo(output,str);
		exit(0);
	}
	if(str[strlen(str)-3] == '&' && str[strlen(str)-2] == 't'){
		//thread shit
		pthread_t tid;
		void *ret;
		char final[MAX];
		str[strlen(str)-3] = '\0';
		snprintf(final,sizeof final,"./%s",str);
//		printf("%s",final);
		if(pthread_create(&tid,NULL,thread,final)!=0){
			perror("pthread_create() error");
			exit(1);
		}
		if(pthread_join(tid,&ret)!=0){
			perror("pthread_create() error");
			exit(3);
		}
		printf("%s\n",ret);
	}
	else{
		pid_t pr;
		pr = fork();
		if(pr==0){
			if(strcmp(output[0],"ls")==0 || strcmp(output[0],"ls\n")==0){
				char *temp;
				//need to have three if conditions, -a,-s and normal
				if(strcmp(output[1],"-s\n")==0){
					temp = "-s";
					execl(output[0],output[0],temp,NULL);
				}
				else if(strcmp(output[1],"-a\n")==0){
					temp = "-a";
					execl(output[0],output[0],temp,NULL);
				}
				else if(output[1][strlen(output[1])-1] == '\n'){
					output[1][strlen(output[1])-1] = '\0';
					execl(output[0],output[0],output[1],NULL);
				}
				else{
//					printf("hello");
					temp = "ls";
					execl(temp,temp,NULL);
				}
//				else{
//					perror("Not an available option");
//					exit(EXIT_FAILURE);
//				}
			}
			else if(strcmp(output[0],"cat")==0 || strcmp(output[0],"cat\n")==0){
				char *temp;
				int flag =0;
				//limiting this to two files
				if(output[1][0] != '-'&&strlen(str)!=4){
					//basically when the -n and the -E options dont exist
					//you are just opening the files
					if(output[1][strlen(output[1])-1]=='\n'){
						//there is only one file
						output[1][strlen(output[1]) -1] = '\0';
						execl(output[0],output[0],output[1],NULL);
					}
					else{
						//two files
						output[2][strlen(output[2])-1] = '\0';
						execl(output[0],output[0],output[1],output[2],NULL);
					}
					flag=1;
				}
				else if(strcmp(output[1],"-n")==0){
					if(output[2][strlen(output[2])-1]=='\n'){
						//one file
						output[2][strlen(output[2])-1] = '\0';
						execl(output[0],output[0],output[1],output[2],NULL);
					}
					else{
						//two files
						output[3][strlen(output[3])-1] = '\0';
						execl(output[0],output[0],output[1],output[2],output[3],NULL);
					}
					flag=1;
				}
				else if(strcmp(output[1],"-E")==0||strcmp(output[1],"-e")==0){
					if(output[2][strlen(output[2])-1]=='\n'){
						//one file
						output[2][strlen(output[2])-1] = '\0';
						execl(output[0],output[0],output[1],output[2],NULL);
					}
					else{
						//two files
						output[3][strlen(output[3])-1] = '\0';
					//	printf("%s",output[3]);
						execl(output[0],output[0],output[1],output[2],output[3],NULL);
					}
					flag =1;
				}			
				else if(flag==0){
					//stdin cat thing
					temp = "cat";
					execl("cat","cat",NULL);
				}
				else{
					perror("Not a viable option");
					exit(EXIT_FAILURE);
				}
				//printf("%d",flag);
			}
			else if(strcmp(output[0],"date\n")==0 || strcmp(output[0],"date")==0){
				char *temp;
				if(output[0][strlen(output[0])-1]=='\n'){
					temp = "date";
					execl(temp,temp,NULL);
				}
				else if(strcmp(output[1],"-u\n")==0){
					temp = "-u";
					execl(output[0],output[0],temp,NULL);
				}
				else if(strcmp(output[1],"-r")==0){
					temp = "-r";
					output[2][strlen(output[2])-1] = '\0';
					execl(output[0],output[0],temp,output[2],NULL);
				}
				else{
					perror("Not a viable option");
					exit(EXIT_FAILURE);
				}
			}
			else if(strcmp(output[0],"rm")==0){
				
			//	printf("%s",output[1]);
			//	printf("%c",output[1][strlen(output[1])-1]);
				if(output[1][strlen(output[1])-1]=='\n'){
			//		printf("Im here");
					output[1][strlen(output[1])-1] = '\0';
			//		printf("%s",output[1]);
					execl(output[0],output[0],output[1],NULL);
				}
				else if(strcmp(output[1],"-i")==0){
					output[2][strlen(output[2])-1] = '\0';
					execl(output[0],output[0],output[1],output[2],NULL);
				}
				else if(strcmp(output[1],"-r")==0){
					printf("Im here");
					output[2][strlen(output[2])-1] = '\0';
					execl(output[0],output[0],output[1],output[2],NULL);
				}
				else{
					perror("Not a viable option");
					exit(EXIT_FAILURE);
				}
			}
			else if(strcmp(output[0],"mkdir")==0){
				if(output[1][0] != '-'){
					output[1][strlen(output[1])-1]= '\0';
					execl(output[0],output[0],output[1],NULL);
				}
				else if(output[1][0] == '-' && (output[1][1]=='v'||output[1][1]=='p')){
					output[2][strlen(output[2])-1] = '\0';
					execl(output[0],output[0],output[1],output[2],NULL);
				}
				else{
					perror("Not a viable option");
					exit(EXIT_FAILURE);
				}
			}
			else{
				perror("Command not found");
				exit(EXIT_FAILURE);
			}
		}
		else{
			wait(NULL);
			printf("Thank you for using the shell\n");
		}
	}



}
