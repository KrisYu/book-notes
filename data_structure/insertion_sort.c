/* 对顺序表L作直接插入排序 */
void InsertSort(SqList *L)
{
  int i,j;
  for (i = 2; i <= L->length; i++)
  {
    if (L->r[i] < L->r[i-1]) /* 需将L->r[i]插入有序子表 */
    {
      L->r[0] = L->r[i];  /* 设置哨兵 */
      for (j = i-1; L->r[j] > L->r[0]; j--)
        L->r[j+1] = L->r[j]; /* 记录后移 */
      L->r[j+1] = L->r[0];   /* 插入到正确位置 */
    }
  }
}
