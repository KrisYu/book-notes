/* 第二种List的格式
 * Node structure
 */

typedef struct Node {
  ElementType Node;
  struct Node *next;
} Node;
typedef struct Node *LinkList;
/ * 这里需要理解的是Node是数据类型， LinkList是把 struct Node * 定义成了新类型 LinkList。这个类型是一个结构体的指针。*/

/* Status 是函数的类型，其值是函数结构状态代码，如OK等 */
/* 初始条件： 顺序线性表L已存在，  1 <= i <= ListLength(L) */
/* 操作结果： 用e返回L中地i个数据元素的值 */
Status GetElem(LinkList L, int i, ElementType *e){
  int j;
  /* p是LinkList指针，也就是struct Node*. */
  LinkList p;
  p = L->next;
  j = 1;
  while (p && j < i) {
    p = p->next;
    ++j;
  }

  if (!p || j > i)
    return ERROR;
  *e = p->data;
  return OK;
}


/* 初始条件： 顺序线性表L已存在，  1 <= i <= ListLength(L) */
/* 操作结果： 在L中第i个位置之前插入新的数据元素e，L的长度增加1 */

/* 这里传入的是LinkList的指针L，也就是指针的指针 */
Status ListInsert(LinkList *L, int i, ElementType e){
  int j;
  LinkList p,s;
  /* p是struct Node*指针类型(LinkList)，L是指向LinkList的指针，所以赋值的时候需要这样来赋值 p = *L. */
  p = *L;
  j = 1;
  while (p && j < i) {
    p = p->next;
    ++j;
  }
  if (!p || j > i)
    return ERROR;
  s = (LinkList)malloc(sizeof(Node));
  s->data = e;
  s->next = p->next;
  p->next = s;
  return OK;
}


/* 初始条件： 顺序线性表L已存在，  1 <= i <= ListLength(L) */
/* 操作结果： 删除L的第i个数据元素，并用e返回其值，L的长度建1 */

Status ListDelete(LinkList *L, int i , ElementType *e){
  int j;
  LinkList p,q;
  p = *L;
  j = 1;
  while (p && j < i) {
    p = p->next;
    ++j;
  }
  if (!(p->next) || j > i)
    return ERROR;
  q = p->next;
  p->next = q->next;
  *e = q->data;
  free(q);
  return OK;
}

/* 随机产生n个元素的值，建立带镖头结点的单链线性表L（头插法）*/
/* p/*L 是LinkList类型， */
void CreateListHead(LinkList *L, int n){
  LinkList p;
  int i;
  srand(time(0));
  *L = (LinkList)malloc(sizeof(Node));
  (*L)->next = NULL;
  for (i = 0; i < n; i++) {
    p = (LinkList)malloc(sizeof(Node));
    p->data = rand() % 100 + 1;
    p->next = (*L)->next;
    (*L)->next = p;
  }
}

/* 要理解L与r的关系，L是指整个单链表，而r是指向尾结点的变量。r会随着循环不断地变化结点，而L则是随着循环增长为一个多结点的链表。*/
void CreateListTail(LinkList *L, int n){
  LinkList p,r;
  int i;
  srand(time(0));
  *L = (LinkList)malloc(sizeof(Node));
  r = (*L);

  for(i = 0; i < n; i++) {
    p = (Node *)malloc(sizeof(Node));
    p->data = rand() % 100 + 1;
    r->next = p;
    r = p;
  }
  r->next = NULL;
}

/* 初始条件： 顺序线性表L已存在，操作结果：将L重置为空表.*/
Status ClearList(LinkList *L){
  LinkList p,q;
  p = (*L)->next;
  while (p) {
    q = p->next;
    free(p);
    p = q;
  }
  (*L)->next = NULL;
  return OK;
}
