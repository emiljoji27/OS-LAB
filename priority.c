#include <stdio.h>
#include <stdlib.h>
struct process
{
    int id, priority, at, bt;
    int wt, ct, tat;
} temp;

void calc(struct process *list, int len)
{
    float averagetat = 0;
    float averagewt = 0;
    struct process *array;
    array = (struct process *)malloc(sizeof(struct process) * len);
    struct process *final;
    final = (struct process *)malloc(sizeof(struct process) * len);
    for (int i = 0; i < len; i++)
    {
        array[i] = list[i];
    }

    //sort based on A.T
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (list[j].at > list[j + 1].at)
            {
                temp = list[j + 1];
                list[j + 1] = list[j];
                list[j] = temp;
            }
        }
    }
    printf("=================================================\n");
    printf("sorted based on arrival time\n");
    printf("Process    Priority   Arrival Time   Burst Time\n");
    for (int i = 0; i < len; i++)
    {
        printf("process%d       %d  \t  %d \t\t  %d\n", list[i].id, list[i].priority, list[i].at, list[i].bt);
    }
    //sort based on priority
    for (int i = 0; i < len; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (array[j].priority > array[j + 1].priority)
            {
                temp = array[j + 1];
                array[j + 1] = array[j];
                array[j] = temp;
            }
        }
    }
    printf("=================================================\n");
    printf("sorted based on priority\n");
    printf("Process    Priority   Arrival Time   Burst Time\n");
    for (int i = 0; i < len; i++)
    {
        printf("process%d       %d  \t  %d \t\t  %d\n", array[i].id, array[i].priority, array[i].at, array[i].bt);
    }
    int timer = 0;
    int k = 0;
    int i = 0, value = 0;
    while (i < len)
    {
        int j = 0;
        if (list[i].at <= timer)
        {
            while (j < len)
            {
                if (array[j].ct == 0 && array[j].priority <= list[i].priority && array[j].at <= timer)
                {
                    array[j].ct = 1;
                    final[k].id = array[j].id;
                    final[k].at = array[j].at;
                    final[k].bt = array[j].bt;
                    if (k == 0)
                        final[k].ct = array[j].bt + array[j].at;
                    else
                        final[k].ct = array[j].bt + final[k - 1].ct;
                    final[k].tat = final[k].ct - array[j].at + value;
                    final[k].wt = final[k].tat - array[j].bt;
                    timer += array[j].bt;
                    i++;
                    k++;
                }
                j++;
            }
        }
        else
        {
            timer++;
            value++;
        }
    }
    printf("=================================================\n");
    printf("Process \tArrival Time \tBurst Time \tT.A.T \tW.T\n");
    for (int i = 0; i < len; i++)
    {
        averagetat += final[i].tat;
        averagewt += final[i].wt;
        printf("Process %d       \t%d \t\t%d\t  %d \t %d\n",final[i].id, final[i].at, final[i].bt, final[i].tat, final[i].wt);
    }
    printf("=================================================\n");
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
        start[i].id=i+1;
        printf("Enter priority of process %d: ",start[i].id);
        scanf("%d",&start[i].priority);
        printf("Enter arrival time and burst time: ");
        scanf("%d %d",&start[i].at, &start[i].bt);
        start[i].ct = 0;
    }
    calc(start, n);
    return 0;
}
