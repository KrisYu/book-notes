/*
 *  Define the struct SqList
 *  typedef 可以某种程序来替代别的语言中的泛型
 */
#define MAXSIZE 20
typedef int ElementType;
typedef struct {
  ElementType data[MAXSIZE];
  int length;
} SqList;


/*
 * 查找
 */
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
typedef int Status;
/* Status 是函数的类型，其值是函数结构状态代码，如OK等 */
/* 初始条件： 顺序线性表L已存在，  1 <= i <= ListLength(L) */
/* 操作结果： 用e返回L中地i个数据元素的值 */

/*
 * 有时候我们会返回角标和-1，这里用e，ElementType* 是e的指针类型，用它来装e。
 */
Status GetElem(SqList L, int i, ElementType* e){
  if (L.length == 0 || i < 1 || i > L.length)
    return ERROR;
  *e = L.data[i-1];
  return OK;
}


/* 初始条件： 顺序线性表L已存在，  1 <= i <= ListLength(L) */
/* 操作结果： 在L中第i个位置之前插入新的数据元素e，L的长度增加1 */

/*
 * 注意这里用的是 SqList 的指针，如果我们需要改变 linear list的话，那么我们需要使用指针。
 */
Status ListInsert(SqList *L, int i , ElementType e) {
  int k;
  if (L->length == MAXSIZE)
    return ERROR;
  if (i < 1 || i > L->length + 1)
    return ERROR;
  if (i <= L->length ) {
    for (k = L->length - 1 ; k >= i-1 ; k--)
      L->data[k+1] = L->data[k];
  }

  L->data[i-1] = e;
  L->length++;
  return OK;
}


/* 初始条件： 顺序线性表L已存在，  1 <= i <= ListLength(L) */
/* 操作结果： 删除L的第i个数据元素，并用e返回其值，L的长度建1 */

/*
 * 注意这里用的是 SqList 的指针，如果我们需要改变 linear list的话，那么我们需要使用指针。
 */
Status ListDelete(SqList *L, int i , ElementType e) {
  int k;
  if (L->length == MAXSIZE)
    return ERROR;
  if (i < 1 || i > L->length + 1)
    return ERROR;
  if (i < L->length ) {
    for (k = i ; k < L->length ; k++)
      L->data[k-1] = L->data[k];
  }
  L->data[i-1] = e;
  L->length--;
  return OK;
}
