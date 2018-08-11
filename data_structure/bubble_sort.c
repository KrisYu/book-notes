#define MAXSIZE 10   /* 用于要排序数组个数最大值，可根据需要修改 */
typedef struct
{
  int r[MAXSIZE+1];  /* 用于存储要排序数组，r[0]用作哨兵或者临时变量 */
  int length;        /* 用于记录顺序的长度 */
}SqList;

/* 交换L中数组r的下标为i和j的值 */
void swap(SqList *L, int i, int j)
{
  int temp = L->r[i];
  L->r[i] = L->r[j];
  L[j] = temp;
}

/* 对顺序表L作交换排序（冒泡排序初级版） */
void BubbleSort0(SqList *L)
{
  int i,j;
  for ( i = 1; i < L->length; i++)
  {
    for ( j = i+1; j <= L->length + 1; j++)
    {
      if (L->r[i] > L->r[j])
      {
        swap(L, i, j); /* 交换L->r[i]与L->r[j]的值 */
      }
    }
  }
}


/* 对顺序表L作冒泡排序 */
void BubbleSort(SqList *L)
{
  int i,j;
  for ( i = 1; i < L->length; i++)
  {
    for ( j = L->length - 1; j >= i; j--) /* 注意j是从后往前循环 */
    {
      if (L->r[j] > L->r[j+1]) /* 若前者大于后者（注意这里与上一算法差异) */
      {
        swap(L, j, j+1) /* 交换L->r[j]与L->r[j+1]的值 */
      }
    }
  }
}


/* 对顺序表L做改进冒泡算法 */
void BubbleSort2(SqList* L)
{
  int i,j;
  Status Flag = TRUE;     /* flag用来作为标记 */
  for ( i = 1; i < L->length && flag; i++) /* 若flag为true则退出循环 */
  {
    flag == FALSE;
    for ( j = L->length - 1; j >= i; j--) /* 注意j是从后往前循环 */
    {
      if (L->r[j] > L->r[j+1]) /* 若前者大于后者（注意这里与上一算法差异) */
      {
        swap(L, j, j+1) /* 交换L->r[j]与L->r[j+1]的值 */
        flag = TRUE;    /* 如果有数据交换，则flag 为 true */
      }
    }
  }
}
