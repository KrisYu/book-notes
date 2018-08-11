/* 对顺序表L作简单选择排序 */
void SelectSort(SqList *q)
{
  int i, j, min;
  for (i = 1; i < L->length; i++)
  {
    min = i;  /* 将当前下标定义为最小值下标 */
    for ( j = i + 1; j <= L->length; j++)
    {
      if (L->r[min] > L->r[j]) /* 如果有小鱼当前最小值的关键字 */
        min = j; /* 将此关键字的下标赋值给min */
    }
    if ( i != min ) /* 若min不等于i，说明找到最小值，交换 */
      swap(L, i, min); /* 交换L->r[i]与L->r[min]的值 */
  }
}
