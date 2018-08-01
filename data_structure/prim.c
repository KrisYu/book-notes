/*
1. Initialize a tree with a single vertex, chosen arbitrarily from the graph.
2. Grow the tree by one edge: of the edges that connect the tree to vertices not yet in the tree, find the minimum-weight edge, and transfer it to the tree.
3. Repeat step 2 (until all vertices are in the tree).
*/

/* Prim算法生成最小生成树 */
void MiniSpanTree_Prim(MGraph G)
{
  int min, i, j, k;
  int adjvex[MAXVEX];  /* 保存相关顶点下标 */
  int lowcost[MAXVEX]; /* 保存相关顶点间边的权值 */
  lowcost[0] = 0;      /* 初始化第一个权值为0，即v0加入生成树 */
                       /* lowcost的值为0，在这里就是此下标的顶点已经加入生成树 */
  adjvex[0] = 0;       /* 初始化第一个顶点下标为0 */
  for (i = 1; i < G.numVertexes; i++)  /* 循环除下标为0外的全部顶点 */
  {
    lowcost[i] = G.arc[0][i]; /* 将v0顶点与之有关的权值存入数组 */
    adjvex[i] = 0;            /* 初始化都为v0的下标 */
  }

  for (i = 0; i < G.numVertexes; i++)
  {
    min = INFINITY; /* 初始化最小值为无穷， 通常设置为不可能的大数值如32767、65535等 */
    j = 1; k = 0;
    while ( j < G.numVertexes)
    {
      if (lowcost[j] != 0 && lowcost[j] < min)
      { /* 如果权值不为0且权值小鱼min */
        min = lowcost[j];  /* 则让当前权值成为最小值 */
        k = j;             /* 将当前最小值的下标存入k */
      }
      j++;
    }

    printf("(%d, %d)", adjvex[k], k); /* 打印当前顶点边中权值最小边 */
    lowcost[k] = 0 ; /* 将当前顶点的权值设置为0，表示此顶点已经完成任务 */
    for (j = 1; j < G.numVertexes; j++)
    {
      if (lowcost[j] != 0 && G.arc[k][j] < lowcost[j])
      {
        /* 若下标为k顶点各边权值小于此前这些顶点未被加入生成树权值 */
        lowcost[j] = G.arc[k][j] ; /* 将较小权值存入lowcost */
        adjvex[j] = k; /* 将下标为k的顶点存入adjvex */
      }
    }
  }
}
