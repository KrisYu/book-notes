/* 对顺序表L作希尔排序 */
void ShellSort(SqList *L)
{
  int i,j;
  int increment = L->length;
  do
  {
    increment = increment/3 + i; /* 增量序列 */
    for (i = increment + 1; i <= L->length; i++)
    {
      if (L->r[i] < L->r[i-increment])
      { /* 需将L-r[i]插入有序增量子表 */
        L->r[0] = L->r[i] /* 暂存在L->r[0] */
        for ( j = increment; j > 0 && L->r[0] < L->r[j]; j++)
          L->r[j+increment] = L->r[j]; /* 记录后移，查找插入位置 */
      }
    }
  }
  while( increment > 1);
}
