#include<stdio.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

struct mem
{
  int buffer[10];
  int mutex;
  int i;
};
 
void wait(struct mem* ptr)
{
 if(ptr->mutex==0)
 {
   printf("Please wait.Consumer is consuming...\n");
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
      struct mem node;
      struct mem* ptr = &node;
      int n;
      key_t key = ftok("shmfile",65);  // ftok to generate unique key
      int shmid = shmget(key,1024,0666|IPC_CREAT);  // shmget returns an identifier to shmid
      ptr = (struct mem*) shmat(shmid,(void*)0,0);  // shmat to attach to shared memory
      ptr->mutex=1;
      ptr->i=0;
      while(1)
      {
        printf("\n1.Produce\n2.Exit\nChoose your option:");
        scanf("%d",&n);
        if(n==1)
        {
          if(ptr->i==10)
            printf("Buffer is full!!\n");
          else
          {
            ptr->buffer[ptr->i]=rand()%1000;;
            wait(ptr);
            printf("Please wait.Producer is producing %d...\n",ptr->buffer[ptr->i]);
            sleep(1.5);
            printf("Producer produced : %d\n",ptr->buffer[ptr->i]);
            signal(ptr);
            sleep(2.5); 
            ptr->i++;
          }
        }
        else
         break;
      }
      shmdt(ptr);  //detach from shared memory
}

