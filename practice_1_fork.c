/*
*
* Практика 1
*
* Практическое занятие на fork.
* Написать программу, которая запускает другую программу при помощи fork и ждет ее завершения.
*
*/


#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>


int main(){
	
	pid_t pid;
	int status;

	pid = fork();

	if (pid > 0){
		printf("I'm papa, my pid = %d, cpid = %d\n", getpid(), pid);
		wait (&status);
		printf("Son status: %d\n", status);
	}
	else if (!pid){
		printf("I'm son,  pid = %d, my pid = %d, ppid = %d\n", pid, getpid(), getppid());
		sleep(5);
		printf("Son: Bye!\n");
		return 0;
	}
		
	else if (pid == -1)
		perror("fork");

	return 0;
}