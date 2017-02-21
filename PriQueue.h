
struct PriQueue* createPriQueue(short sign);//sign determinte the type of the queue 
//1 means the bigger is the priorty,while 0 means the smaller
//maxLength is the max count of elements in the queue
void PushElementToPQ(struct PriQueue* pq,int value);
void PopElementFromPQ(struct PriQueue* pq);
int getHeadOfPQ(struct PriQueue* pq);
int getCountOfPQ(struct PriQueue* pq);
