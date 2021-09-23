#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

void main()
  {
     key_t key = ftok("shmfile",65);  // ftok to generate unique key
     int shmid = shmget(key,1024,0666|IPC_CREAT);  // shmget returns an identifier to shmid
     char *str = (char*) shmat(shmid,(void*)0,0);  // shmat to attach to shared memory
     printf("Data read from memory: %s\n",str); 
     shmdt(str);  //detach from shared memory
     shmctl(shmid,IPC_RMID,NULL);  // destroy the shared memory
  }

