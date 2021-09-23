#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct mem{
  int buffer[10];
  int mutex;
 };
 
void wait(struct mem* ptr)
{
 if(ptr->mutex==0)
 {
   printf("Please wait.Producer is producing...\n");
   while(1)
   {
     if(ptr->mutex==1)
       break;
   }
 }
 ptr->mutex--;
}

void signal(struct mem* ptr)
{
 ptr->mutex++;
}

void main()
{
      struct mem *ptr = (struct mem*)malloc(sizeof(struct mem));
      key_t key = ftok("shmfile",65);  // ftok to generate unique key
      int shmid = shmget(key,1024,0666|IPC_CREAT);  // shmget returns an identifier to shmid
      ptr = (struct mem*) shmat(shmid,(void*)0,0);  // shmat to attach to shared memory
      for(int i=0;i<10;i++)
      {
        wait(ptr);
        printf("Please wait.Consumer is consuming %d...\n",ptr->buffer[i]);
        sleep(1.5);
        printf("Consumer consumed : %d\n",ptr->buffer[i]);
        signal(ptr);
        sleep(2.5);
      }
      shmdt(ptr);  //detach from shared memory
      shmctl(shmid,IPC_RMID,NULL);
}

