/* 对边集数组 Edge 结构的定义 */
typedef struct
{
   int begin;
   int end;
   int weight;
};

/* Kruskal算法生成最小生成树 */
void MiniSpanTree_Kruskal(MGraph G)
{
  int i, n, m;
  Edge edges[MAXEDGE];  /* 定义边集数组 */
  int parent[MAXVEX];   /* 定义一数组用来判断边与边是否形成环路 */
  /* 此处省略将邻接矩阵G转化为边集数组edges并按权由小到大排序的代码 */
  for (i = 0; i < G.numEdges; i++)
    parent[i] = 0; /* 初始化数组值为0 */
  for (i = 0; i < G.numEdges; i++) /* 循环每一条边 */
  {
    n = Find(parent, edges[i].begin);
    m = Find(parent, edges[i].end);
    if (n != m) /* 加入n与m不相等，说明此边没有与现有生成树形成环路 */
    {
      parent[n] = m; /* 将此边的结尾顶点方如下标为起点的parent中, 表示此顶点已经在生成树集合中 */
      printf("(%d, %d) %d", edges[i].begin, edges[i].end, edges[i].weight);
    }
  }
}


int Find(int *parent, int f) /* 查找连接顶点的尾部下标 */
{
  while (parent[f] > 0)
    f = parent[f];
  return f;
}

/*
   Kruskal算法是我们把森林连接成树
   每次找出最小的边，只要没有组成环，那么我们就可以用它，直到生成树。
   Prim是我们逐渐长成一棵树
   每次我们选出从当前的树生长出去最小的连接到外部的边。
*/
