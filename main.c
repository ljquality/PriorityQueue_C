#include"stdio.h"
#include"PriQueue.h"

int main()
{
    
   struct PriQueue* pq=createPriQueue(0);
   int cinin;
   while(1)
   {
       
        scanf("%d",&cinin);
       if(cinin==0)
        break;
        PushElementToPQ(pq,cinin);
   }
   int num=getCountOfPQ(pq);
   for(int i=0;i<num;i++)
    {
        printf("%d\n",getHeadOfPQ(pq));
        PopElementFromPQ(pq);
    }
    return 0;
}