
#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
int* getList(int n,char a[])
{
 int *list = (int*) malloc(sizeof(int)*n);
 for (int i=0;i<n; i++)
 {
  if(a=="partition")
         printf("Enter size of Memory Partition M%d (in KB): ",i);
  else if(a=="process")
         printf("Enter the memory required by process P%d: ",i);
  scanf("%d",list + i);
 }
 return list;
}


void printMemParts(int* list, int n)
{
 char top[] = "|----------";
 char end[] = "|----------|";
 for(int i=0;i<n; i++)
 {
   if(i< n-1)
         printf("%s",top);
   else
         printf("%s",end);
 }
 printf("\n|");
 for (int i=0; i<n; i++)
 {
   printf("%8dKB|",list[i]);
 }
 printf("\n");
 for(int i=0;i<n-1; i++)
 {
   printf("%s",top);
 }
 printf("%s",end);
 printf("\n");
}


void showAlloc(int* memList, int mnum, int* procList, int pnum, int*alloc_list)
{
 char start[] = "|--------------";
 char end[] = "|--------------|";
 char str[30];
 int not_fit[pnum];
 int k=0;
 int total=0;
 int used=0;
 for(int i=0;i<mnum-1; i++)
 {
   printf("%s",start);
 }
 printf("%s",end);
 printf("\n");

 printf("|");
 for (int i=0;i<mnum; i++)
 {
   sprintf(str,"%dKB",memList[i]);
   printf("%14s|",str);
 }
 printf("\n");
 for(int i=0;i<mnum-1; i++)
 {
   printf("%s",start);
 }
 printf("%s",end);
 printf("\n|");
 for (int i=0; i<mnum; i++)
 {
   if(alloc_list[i] != -1)
   {
         sprintf(str,"%s%d(%dKB)","P",alloc_list[i],procList[alloc_list[i]]);
         printf("%14s|",str);
        used += procList[alloc_list[i]];
   }
   else
   {
          printf("%14s|","NULL");
   }
 total += memList[i];
 }
 printf("\n");
 for(int i=0;i<mnum-1; i++)
 {
   printf("%s",start);
 }
 printf("%s",end);
 printf("\n");
 for (int i=0; i<pnum; i++)
 {
   int j = 0;
   for (;j<mnum;j++)
   {
         if(alloc_list[j] == i)
              break;
  }
  if (j==mnum)
  {
   not_fit[k] = i;
   k++;
  }
 }
 printf("\nProcess not allocated: ");
 for(int i=0;i<k-1;i++)
 {
  printf("P%d(%dKB), ",not_fit[i],procList[not_fit[i]]);
 }
 if (k!=0)
      printf("P%d(%dKB)\n",not_fit[k-1],procList[not_fit[k-1]]);
 else
       printf("NIL\n");
 printf("\n---- Algorithm Stats -----");
 printf("\nTotal memory space: %dKB\n",total);
 printf("Memory space used: %dKB\n",used);
 printf("Memory space free: %dKB\n",total-used);
 float precent_free = (float)(total-used) / total * 100.0;
 printf("Precentage free: %.2f%%\n",precent_free);
}

int* firstFit(int* procList, int pnum, int* memList, int mnum)
{
 int i,j;
 int* alloc_list = (int*)malloc(sizeof(int)*mnum);

 for (i=0;i<mnum;i++)
 {
  alloc_list[i] = -1;
 }
 
 for (i = 0; i< pnum ; i++)
 {
   for (j =0; j< mnum ; j++)
   {
        if (alloc_list[j] == -1 && memList[j] >= procList[i])
            {
               alloc_list[j] = i;
               break;
           }
   }
 }
 return alloc_list;
}

int* bestFit(int* procList,int pnum, int*memList, int mnum)
{
 int i,j;
 int* alloc_list = (int*)malloc(sizeof(int)*mnum);
 for (i=0;i<mnum;i++)
 {
   alloc_list[i] = -1;
 }
 int space;
 int pos;
 for(i=0;i<pnum;i++)
 {
   space =INT_MAX;
   pos = -1;
   for(j=0;j<mnum; j++)
   {
       int diff = memList[j] - procList[i];
        if(diff>=0 && diff < space && alloc_list[j]==-1)  
        {
             space = diff;
             pos = j;
        }
   }
   if (pos != -1)
   {
         alloc_list[pos] = i;
   }
 }
 return alloc_list;
}


int* worstFit(int* procList,int pnum, int*memList, int mnum)
{
 int i,j;
 int* alloc_list = (int*)malloc(sizeof(int)*mnum);
 for (i=0;i<mnum;i++)
 {
  alloc_list[i] = -1;
 }
 int greatest;
 int pos;
 for(i=0;i<pnum;i++)
 {
  greatest = -1;
  pos = -1;
  for (j=0;j<mnum ; j++)
  {
   if (memList[j]>=procList[i] && greatest < memList[j] && alloc_list[j] == -1)
     {
         greatest = memList[j];
         pos = j;
    }
  }

  if (pos != -1)
	alloc_list[pos] = i;
 }
 return alloc_list;
}

int main()
{
 int n,p;
 printf("Enter the number of Memory Partitions: ");
 scanf("%d",&n);
 int *mem_blocks = getList(n,"partition");
 printf("Enter the number of Processes: ");
 scanf("%d",&p);
 int *proc_list = getList(p,"process");
 int *alloc_list;
 printf("\n\nThe Memory Locations received are:\n");
 printMemParts(mem_blocks, n);
 printf("\n\n====================== FIRST FIT ======================\n");
 alloc_list = firstFit(proc_list,p,mem_blocks,n);
 showAlloc(mem_blocks, n, proc_list, p, alloc_list);
 free(alloc_list);
 printf("\n\n====================== BEST FIT ======================\n");
 alloc_list = bestFit(proc_list,p,mem_blocks,n);
 showAlloc(mem_blocks, n, proc_list, p, alloc_list);
 free(alloc_list);
 printf("\n\n====================== WORST FIT ======================\n");
 alloc_list = worstFit(proc_list,p,mem_blocks,n);
 showAlloc(mem_blocks, n, proc_list, p, alloc_list);
 free(alloc_list);
 free(mem_blocks);
 free(proc_list);
 return 0;
}
