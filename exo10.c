#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]){
  int fd[2],ret,fda[2],reta,a;
  pid_t pid;
 ret=pipe(fd); 
 reta=pipe(fda);
 if(ret<0 || reta<0){
	 fprintf(stderr,"Erreur de creation du pipe %d \n",errno);
	 return 1;
	 
 }
 pid=fork();
 if(pid<0){
	 
	 fprintf(stderr,"erreur de creation du fils(%d)\n",errno);
	 return 1;
 }
 if(pid==0){
	 close(fd[1]); 
	 close(fda[0]);
	 char buffer[10];
	
	 do{
		 read(fd[0],buffer,10);
		 a= atoi(buffer);
		 printf("La valeur recu du pere est %d",a);
		 a--;
		 memcpy(&a,buffer,4);
		 write(fda[1],buffer,strlen(buffer));
		 
		 }
		 while(a!=0);
		 
		} else{
			 
			 close(fd[0]); 
			 close(fda[1]);
			 char buffer[10];
			 pid_t pid2=getpid();
			 do {
				 memcpy(&pid2,buffer,4);
				 write(fd[1],buffer,strlen(buffer));
				 read(fda[0],buffer,10);
				 pid2=atoi(buffer);
				 printf("la valeur recu du fils est %d",a);
				pid2--;
			 }
			 while(pid2!=0);
			 
			 int status;
			 pid_t pid3 =wait(&status);
		 }
}

