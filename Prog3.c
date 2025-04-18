#include<stdio.h> 
#define INF 9999  
struct rtable
{
    int dist[20],nextnode[20];
} table[20];

int cost[10][10],n;

void distvector()
{
      int i,j,k,count=0;
  
      for(i=0; i<n; i++)
      {
          for(j=0; j<n; j++)
          {
              table[i].dist[j]=cost[i][j];
              table[i].nextnode[j]=j;
          }
      }
  
  do {
      count = 0;
      for(i = 0; i < n; i++) {
          for(j = 0; j < n; j++) {
              for(k = 0; k < n; k++) {
                  // 1) Skip non‑neighbors
                  if (cost[i][k] == INF) 
                      continue;
  
                  // 2) Also skip if neighbor k doesn’t have a route to j
                  if (table[k].dist[j] == INF)
                      continue;
  
                  // 3) Relax via k
                  int via_k = cost[i][k] + table[k].dist[j];
                  if (table[i].dist[j] > via_k) {
                      table[i].dist[j]     = via_k;
                      table[i].nextnode[j] = k;
                      count++;
                  }
              }
          }
      }
  } while (count != 0);

}

int main()
{
    int i,j;
    printf("\nenter the no of vertices:\t");
    scanf("%d",&n);
    printf("\nenter the cost matrix\n");

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            scanf("%d",&cost[i][j]);

    distvector();

    for(i=0; i<n; i++)
    {
        printf("\nstate value for router %c \n",i+65);
        printf("\ndestnode\tnextnode\tdistance\n");
        for(j=0; j<n; j++)
        {
            if(table[i].dist[j]==9999)
                printf("%c\t\t-\t\tinfinite\n",j+65);
            else
                printf("%c\t\t%c\t\t%d\n",j+65,table[i].nextnode[j]+65,table[i].dist[j]);
        }
    }
    return 0;
}
