
		//[  le père envoie et le fils lis explication celui qui lit on ferme son fd[1] et son fd[0] est ouvert ] De même celui qui recoit ferme son fd[0] et ouvre son fd[1] */
		
		/*  Exo 9 : Modifier le programme suivant de manière à ce que le père puisse envoyer à son fils le pid de son père à lui. */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(int argc, char *argv[]){
  int fd[2], ret;
  pid_t pid;
  /* demande de création du pipe au système*/
  ret = pipe(fd);
  if(ret < 0){ /* Une erreur s'est produite lors de la création du pipe*/
    fprintf(stderr, "Erreur de création du pipe (%d)\n", errno);
    return 1;
  }
  pid = fork(); /* demande de création du processus fils*/
  if(pid < 0){ /* Une erreur s'est produite lors de la création du processus fils*/
    fprintf(stderr, "Erreur de création du fils(%d)\n", errno);
    return 1;
  }
  if(pid == 0){ /*Nous sommes dans le fils*/
    close(fd[1]); /* Le fils ferme l'extrémité d'écriture du pipe*/
    char buffer[10];
    int n = read(fd[0], buffer, 10);
      printf("Fils(%s)\n", buffer);
      printf("le pid du fils est %d",getpid());
   
  }
  else{
    close(fd[0]); /* Le père ferme l'extrémité de lecture du pipe*/
    char buffer[10];
	pid_t pid2 = getppid();
	printf("je suis le père %d qui envoie le pid de mon x= %d ",getpid(),getppid());
	memcpy(&pid2, buffer,4);
     /*	cas1--> memcpy(&pid2, buffer,4)
	cas2--> sprintf(buffer,"%d", pid2);
	NB: cas1 ou cas2 car la valeur est un entier */
  
      write(fd[1], buffer, strlen(buffer)); /* le père écrit la chaine de caractère dans le pipe */
    
    int status;
    pid_t pid3 = wait(&status); /* Le père attend la fin du fils. */
    printf("Père (%s)\n", buffer);
   
    
  } 
}
