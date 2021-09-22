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
void tat(struct process *processArray, int len, int quantum)
{
    int timer = 0;
    int i = 0;
    int value = 0;
    float averagetat = 0;
    float averagewt = 0;
    float tempArray[len];
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        tempArray[i] = processArray[i].bt;
        sum += tempArray[i];
    }
    printf("sum is %d\n", sum);
    int flag = 0;
    while (flag != sum)
    {
        if (processArray[i].at <= timer)
        {
            if (tempArray[i] != 0)
            {
                if (tempArray[i] <= quantum)
                {
                    processArray[i].ct = timer + tempArray[i];
                    timer = timer + tempArray[i];
                    flag += tempArray[i];
                    tempArray[i] = 0;
                }
                else
                {
                    processArray[i].ct = timer + quantum;
                    tempArray[i] = tempArray[i] - quantum;
                    timer += quantum;
                    flag += quantum;
                }
            }
        }
        else
        {
            timer++;
            value++;
        }
        i++;
        if (i == len)
        {
            i = 0;
        }
    }
    printf("================================================================= \n");
    printf("Process \tArrival Time \tBurst Time \tT.A.T \tW.T\n");
    for (int i = 0; i < len; i++)
    {
        processArray[i].tat = processArray[i].ct - processArray[i].at + value;
        processArray[i].wt = processArray[i].tat - processArray[i].bt;
        printf("Process %d       \t%d \t\t%d\t  %d \t %d\n",processArray[i].num, processArray[i].at, processArray[i].bt, processArray[i].tat, processArray[i].wt);
        averagetat += processArray[i].tat;
        averagewt += processArray[i].wt;
    }
    printf("================================================================= \n");
    float floattat = averagetat / len;
    float floatwt = averagewt / len;
    printf("Average Turn Around Time = %f\n", floattat);
    printf("Average Waiting Time = %f\n", floatwt);
}
int main()
{
    int n, q;
    printf("Enter number of processes : ");
    scanf("%d", &n);
    printf("Enter time quantum : ");
    scanf("%d", &q);
    struct process *start = (struct process *)malloc(sizeof(struct process) * n);
    for (int i = 0; i < n; i++)
    {
        start[i].ct = 0;
        start[i].wt = 0;
        start[i].num= i+1;
        printf("Enter arrival time,burst time of process[%d]: ", i);
        scanf("%d %d",&start[i].at, &start[i].bt);
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
    printf("Process \tArrival Time  Burst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d \t     %d \t         %d \n", start[i].num, start[i].at, start[i].bt);
    }
    printf("============================================\n");
    tat(start, n, q);
    return 0;
}
