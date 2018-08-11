/* 对顺序表L进行堆排序 */
void HeapSort(SqList *L)
{
  int i;
  for ( i = L->length/2; i > 0 ; i--)  /* 把L中的r构建成一个最大顶堆 */
    HeapAdjust(L, i, L->length);

  for ( i = L->length; i > 1 ; i--)
  {
    swap(L, 1, i); /* 将堆顶记录和当前未经排序子序列的最后一个记录交换 */
    HeapAdjust(L, 1, i - 1); /* 将L->r[1...i-1]重新调整为大顶堆 */
  }
}


/* 已知道L->r[s...m]中记录的关键字除L->r[s]之外均满足堆的定义 */
/* 本函数调整L->r[s]的关键字，使L->r[s...m]成为一个大顶堆 */
void HeapAdjust(SqList *L, int s, int m)
{
  int temp, j;
  temp = L->r[s];
  for ( j = 2 * s; j <= m; j *= 2) /* 沿关键字较大的孩子结点向下筛选 */
  {
    if (j < m && L->r[j] < L->r[j+1])
      ++j;   /* j为关键字中较大的记录的下标 */
    if (temp >= L->r[j])
      break; /* rc应插入在位置s上 */
    L->r[s] = L->r[j];
    s = j;
  }
  L->r[s] = temp;  /* 插入 */
}
