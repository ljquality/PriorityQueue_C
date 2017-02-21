#include"PriQueue.h"
#include"stdio.h"

struct PQNode
{
    int value;
    struct PQNode* left;
    struct PQNode* right;
    int leftCount;
    int rightCount;
};
struct PriQueue
{
    struct PQNode* headNode;//the array of elements
    int count;//the num of elements
    int head;//the first element
    short sign;//determine the type of the pq
};
//define the size of pqnode and pq
int PQNodeSize=sizeof(struct PQNode);
int PQSize=sizeof(struct PriQueue);
//compare the value of two PQNode
short comparePQNode(struct PQNode* pqn1,struct PQNode* pqn2,short sign)
{
    short returnV=0;
    if(pqn1->value>pqn2->value)
        returnV=1;
    if(sign==0)
        returnV=1-returnV;//if the pq is smaller priory queue
    return returnV;
}
//swap value of two pqnode
void swapValue(struct PQNode* pqn1,struct PQNode* pqn2)
{
    int temp=pqn1->value;
    pqn1->value=pqn2->value;
    pqn2->value=temp;
}
//push
void pushDown(struct PQNode* cur,struct PQNode* insert,short sign)
{
    if(comparePQNode(insert,cur,sign))
    {
        int temp=cur->value;
        cur->value=insert->value;
        insert->value=temp;
    }
    if(cur->left==NULL)
    {
        cur->leftCount++;
        cur->left=insert;
    }
    else if(cur->right==NULL)
    {
        cur->rightCount++;
        cur->right=insert;
    }
    else if(cur->leftCount>cur->rightCount)
    {
        cur->rightCount++;
        pushDown(cur->right,insert,sign);
    }
    else
    {
        cur->leftCount++;
        pushDown(cur->left,insert,sign);
    }
}
void PushElementToPQ(struct PriQueue* pq,int value)
{
    struct PQNode* pqn=(struct PQNode*)malloc(PQNodeSize);
    pqn->value=value;
    pqn->left=NULL;
    pqn->right=NULL;
    pqn->leftCount=0;
    pqn->rightCount=0;
    if(pq->headNode==NULL)//when the pq is empty
        pq->headNode=pqn;
    else
        pushDown(pq->headNode,pqn,pq->sign);
    pq->head=pq->headNode->value;
    pq->count++;
}
//pop
//为了保持二叉树的平衡，删除一个节点是总是从维持平衡出发选择左子树还是右子树
//根节点pop后，自顶而下，不断将左右子节点中较大的值替代父亲节点值，如果较大节点所在子树节点较少，则与另一个节点交换
//swapDown是用来解调交换后的子树，譬如说交换后父亲节点值可能比子节点小
//较大节点指的是逻辑值大，即极大堆的值大为较大节点，极小堆值小的为较大节点
void swapDown(struct PQNode* pqn,short sign)
{
    if(pqn->left==NULL&&pqn->right==NULL)
        return;
    if(pqn->right!=NULL)
    {
        struct PQNode* bigTemp;
        if(comparePQNode(pqn->left,pqn->right,sign))
            bigTemp=pqn->left;
        else
            bigTemp=pqn->right;
        if(comparePQNode(pqn,bigTemp,sign))
            return;
        if(comparePQNode(pqn->left,pqn->right,sign))
        {
            swapValue(pqn,pqn->left);
            swapDown(pqn->left,sign);
        }
        else
        {
            swapValue(pqn,pqn->right);
            swapDown(pqn->right,sign);
        }
    }
    else
    {
        if(comparePQNode(pqn,pqn->left,sign))
            return;
        swapValue(pqn,pqn->left);
        swapDown(pqn->left,sign);
    }
}
void PopDown(struct PQNode* pq,short sign)
{
    if(pq->rightCount>0)
        if(comparePQNode(pq->left,pq->right,sign))
            pq->value=pq->left->value;
        else
            pq->value=pq->right->value;
    else
        pq->value=pq->left->value;
    //
    if(pq->rightCount==1&&pq->leftCount==1)
    {
        //如果左边值大于右边就把两者的值交换，然后调整左边的子树
        if(comparePQNode(pq->left,pq->right,sign))
        {
            swapValue(pq->left,pq->right);
            swapDown(pq->left,sign);
        }
        free(pq->right);
        pq->right=NULL;
        pq->rightCount--;
        
    }
    else if(pq->leftCount==1)
    {
        free(pq->left);
        pq->left=NULL;
        pq->leftCount--;
    }
    else if(pq->leftCount>pq->rightCount)
    {
        //如果右边值大于左边就把两者的值交换，然后调整右边的子树
        if(comparePQNode(pq->right,pq->left,sign))
        {
            swapValue(pq->left,pq->right);
            swapDown(pq->right,sign);
        }
        pq->leftCount--;
        PopDown(pq->left,sign);
    }
    else
    {
        //如果左边值大于右边就把两者的值交换，然后调整左边的子树
        if(comparePQNode(pq->left,pq->right,sign))
        {
            swapValue(pq->left,pq->right);
            swapDown(pq->left,sign);
        }
        pq->rightCount--;
        PopDown(pq->right,sign);
    }
}

void PopElementFromPQ(struct PriQueue* pq)
{
    if(pq->count==0)
        return;
    pq->count--;
    if(pq->count==0)
    {
        free(pq->headNode);
        pq->headNode=NULL;
        pq->head=-1;
        return;
    }
    struct PQNode* p=pq->headNode;
    PopDown(p,pq->sign);
    pq->head=pq->headNode->value;
}

//get head of a pq
int getHeadOfPQ(struct PriQueue* pq)
{
    return pq->head;
}

int getCountOfPQ(struct PriQueue* pq)
{
    return pq->count;
}

struct PriQueue* createPriQueue(short sign)
{   
    struct PQNode* h=NULL;
    struct PriQueue* pq=(struct PriQueue*)malloc(PQSize);
    pq->headNode=h;
    pq->count=0;
    pq->head=-1;
    pq->sign=sign;
    printf("create priqueue succeesfully!\n");
    return pq;
}