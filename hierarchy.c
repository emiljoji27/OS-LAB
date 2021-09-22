#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>


void main(){
    int n ;
    int i = 0;
    printf("Enter the value of N : ");
    scanf("%d", &n);
    printf("Level 0:  Process id: %d \n",getpid());
    for(i =1; i<=n ; i++)
    {
        if(fork() == 0)
          printf("Level %d:  Process id: %d, Parent id: %d \n",i,getpid(),getppid());
        else if(fork() == 0)
          printf("Level %d:  Process id: %d, Parent id: %d \n",i,getpid(),getppid());
        else
        {
          wait(NULL);
          i=n+1;
        }
    }
    
}
