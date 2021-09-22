#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct process
{
    int num;
    int at;
    int bt;
    int ct, tat, wt;
} temp;

void tat(struct process *start_array, int len)
{
    int timer = 0;
    int i = 0;
    int value = 0;
    while (i < len)
    {
        if (start_array[i].at <= timer)
        {
            int j = i;
            start_array[i].tat = 0;
            while (j >= 0)
            {
                start_array[i].ct += start_array[j].bt;
                j--;
            }
            start_array[i].tat = start_array[i].ct - start_array[i].at + value;
            start_array[i].wt = start_array[i].tat - start_array[i].bt;
            timer += start_array[i].bt;
            i++;
        }
        else
        {
            timer++;
            value++;
        }
    }
}
int main()
{
    int n;
    float averagetat = 0;
    float averagewt = 0;
    printf("Enter number of processes : ");
    scanf("%d", &n);
    struct process *start = (struct process*)malloc(sizeof(struct process) * n);
    for (int i = 0; i < n; i++)
    {
        start[i].ct = 0;
        start[i].wt = 0;
        start[i].num= i+1;
        printf("Enter arrival time,burst time of process %d: ", i+1);
        scanf("%d %d",&start[i].at,&start[i].bt);
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (start[j].at > start[j + 1].at)
            {
                temp = start[j + 1];
                start[j + 1] = start[j];
                start[j] = temp;
            }
        }
    }
    printf("============================================\n");
    printf("Process     Arrival Time     Burst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d \t %d \t\t %d \n", start[i].num, start[i].at, start[i].bt);
    }
    printf("============================================\n");
    tat(start, n);
    printf("=================================================================\n");
    printf("Process\t   Arrival Time\t Burst Time\tT.A.T\t W.T\n");
    for (int i = 0; i < n; i++)
    {
        averagetat += start[i].tat;
        averagewt += start[i].wt;
        printf("Process %d \t %d \t    %d \t\t  %d \t  %d\n",start[i].num, start[i].at, start[i].bt, start[i].tat, start[i].wt);
    }
    printf("=================================================================\n");
    printf("Average Turn Around Time = %f\n", averagetat / n);
    printf("Average Waiting Time = %f\n\n", averagewt / n);
    return 0;
}
