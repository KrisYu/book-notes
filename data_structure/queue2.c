typedef int QElemType; /* QElemType类型根据实际情况而定，这里假设为int */

typedef struct QNode{
  QElemType data;
  struct QNode *next;
} QNode, *QueuePtr;

typedef struct{
  QueuePtr front, rear; /*front指向头节点。rear指向终端结点 */
} LinkQueue;

/* 插入元素e为Q的队尾元素 */
Status EnQueue(LinkQueue *Q, QElemType e){
  QueuePtr s = (QueuePtr) malloc(sizeof(QNode));
  if (!s) /* 存储分配失败 */
    exit(OVERFLOW);
  s->data = e;
  s->next = NULL;
  Q->rear->next = s;  /* 把拥有元素e的新节点s赋值给原队尾结点的后继 */

  Q->rear = s; /*把当前的s设置为队尾节点，rear指向s。*/
  return OK;
}

/* 弱队列不空，则删除Q中队头元素，用e返回其值，并返回OK，否则返回ERROR*/
Staus DeQueue(LinkQueue *Q, QElemType *e){
  QueuePtr p;
  if(Q->front == Q->rear)
    return ERROR;
  p = Q->front->next; /* 将欲删除的队投节点暂存给p */
  *e = p->data;  /*将欲删除的队头节点的值赋给e */
  Q->front->next = p->next; /*将原队头节点后继p->next赋值给头结点后继.*/
  if (Q->rear == p) /*若队头是队尾，则删除后将rear指向头结点*/
    Q->rear = Q->front;
  free(p);
  return OK;
}
