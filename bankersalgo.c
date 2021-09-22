#include <stdio.h>
int main()
{
	// P0, P1, P2, P3, P4 are the Process names here

	int n, m, i, j, k;
	int count = 0;
	
	printf("Enter the number of processes :  ");
	scanf("%d",&n);
	printf("Enter the number of resources :  ");
	scanf("%d",&m);
	int alloc[n][m],max[n][m],avail[m];
	
	for(int i=0;i<n;i++)
	{
	   printf("Allocated resources for P%d : ",i);
	   for(int j=0;j<m;j++)
	   {
               scanf("%d",&alloc[i][j]);
           }
        }
       
       for(int i=0;i<n;i++)
	{
	   printf("Maximum resources needed for P%d : ",i);
	   for(int j=0;j<m;j++)
	   {
               scanf("%d",&max[i][j]);
           }
       }
       
       printf("Available resources : ");
       for(int j=0;j<m;j++)
       {
           scanf("%d",&avail[j]);
              
       }
         
       int f[n], ans[n], ind = 0;
	
	for (k = 0; k < n; k++) 
	{
		f[k] = 0;
	}
	
	int need[n][m];
	printf("\n\tNEED MATRIX\n");
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < m; j++)
			need[i][j] = max[i][j] - alloc[i][j];
		printf("Process %d\t ",i);	
	        for (j = 0; j < m; j++)
			printf(" %d ",need[i][j]);
		printf("\n");
	}
	
	int y = 0;
	
	while(1) 
	{
	        int flag_outer = 0;
		for (i = 0; i < n; i++) 
		{
			if (f[i] == 0) 
			{
                               int flag = 0;
				for (j = 0; j < m; j++) 
				{
					if (need[i][j] > avail[j])
					{
						flag = 1;
						break;
					}
				}

				if (flag == 0) 
				{
					ans[ind++] = i;
					for (y = 0; y < m; y++)
						avail[y] += alloc[i][y];
					f[i] = 1;
					flag_outer = 1;
				}
			}
		}
		
		if(flag_outer == 0)
		      break;
	}
	
	for (i = 0; i <= n - 1; i++)
	{
	  if(f[i]==0)
	  {
	    printf(" P%d can't be allocated\n", i);
	    count++;
	  }
	}

	printf("\n\nSAFE SEQUENCE : ");
	
	for (i = 0; i < n - count - 1; i++)
		printf(" P%d ->", ans[i]);
		
	printf(" P%d \n", ans[n - count - 1]);

	return (0);

}

