#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct process
{
    int id, at, bt;
    int wt, tat, ct;
} temp;
void calc(struct process *array, int len)
{
    float averagetat = 0;
    float averagewt = 0;
    struct process *sjf, *final;
    sjf = (struct process *)malloc(sizeof(struct process) * len);
    final = (struct process *)malloc(sizeof(struct process) * len);
    //make a new sorted array based on burst time
    for (int i = 0; i < len; i++)
    {
        sjf[i] = array[i];
    }
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (sjf[j].bt > sjf[j + 1].bt)
            {
                temp = sjf[j + 1];
                sjf[j + 1] = sjf[j];
                sjf[j] = temp;
            }
        }
    }
    int timer = 0;
    int value = 0;
    int k = 0;
    int i = 0;
    while (i < len)
    {
        int flag = 0;
        int j = 0;
        if (array[i].at <= timer)
        {
            while (j < len)
            {
                if (sjf[j].ct == 0 && array[i].bt >= sjf[j].bt && sjf[j].at <= timer)
                {
                    sjf[j].ct = 1;
                    final[k].id = sjf[j].id;
                    final[k].at = sjf[j].at;
                    final[k].bt = sjf[j].bt;
                    if (k == 0)
                        final[k].ct = sjf[j].bt + sjf[j].at;
                    else
                        final[k].ct = sjf[j].bt + final[k - 1].ct;
                    final[k].tat = final[k].ct - sjf[j].at + value;
                    final[k].wt = final[k].tat - sjf[j].bt;
                    timer += sjf[j].bt;
                    k++;
                }
                j++;
            }
            i++;
        }
        else
        {
            timer++;
            value++;
        }
    }
    printf("========================================================================\n");
    printf("Process \tArrival Time \tBurst Time \tT.A.T \tW.T\n");
    for (int i = 0; i < len; i++)
    {
        averagetat += final[i].tat;
        averagewt += final[i].wt;
        printf("Process %d       \t%d \t\t%d\t  %d \t %d\n", final[i].id, final[i].at, final[i].bt, final[i].tat, final[i].wt);
    }
    printf("========================================================================\n");
    printf("Average Turn Around Time = %f\n", averagetat / len);
    printf("Average Waiting Time = %f\n", averagewt / len);
}
int main()
{
    int n;
    printf("Enter number of operations : ");
    scanf("%d", &n);
    struct process *start;
    start = (struct process *)malloc(sizeof(struct process) * n);
    for (int i = 0; i < n; i++)
    {
        start[i].ct = 0;
        start[i].id= i+1;
        printf("Enter arrival time,burst time of process[%d]: ", i);
        scanf("%d %d",&start[i].at, &start[i].bt);
    }
    printf("========================================\n");
    printf("Process \tArrival Time  Burst Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("Process %d \t     %d \t         %d \n", start[i].id, start[i].at, start[i].bt);
    }
    printf("========================================\n");
    for (int i = 0; i < n; i++)
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
    calc(start, n);
    return 0;
}
