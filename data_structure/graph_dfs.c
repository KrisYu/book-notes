typedef int Boolean; /* Boolean是布尔类型，其值是TRUE或FALSE  */
Boolean visited[MAX]; /* 访问标志的数组 */

/* 邻接矩阵的深度优先递归算法 */
void DFS(MGraph G, int i)
{
  int j;
  visited[i] = TRUE;
  printf("%c ",G.vexs[i]); /* 打印顶点，也可以其它操作 */
  for (j = 0; j < G.numVertexes; j++)
    if (G.arc[i][j] == 1 && !visited[j] )
      DFS(G, j);  /* 对未访问的邻接顶点递归调用 */
}

/* 邻接矩阵的深度遍历操作 */
void DFSTraverse(MGraph G)
{
  int i;
  for (i = 0; i < G.numVertexes; i++)
    visited[i] = FALSE; /* 初始化所有顶点状态都是未访问过状态 */
  for (i = 0; i < G.numVertexes; i++)
    if (!visited[i])  /* 对未访问过的顶点调用DFS，若是连通图，只会执行一次 */
      DFS(G, i);
}


/* 邻接表的深度优先递归算法 */
void DFS(GraphAdjList GL, int i)
{
  EdgeNode *p;
  visited[i] = TRUE;
  printf("%c ",GL->adjList[i].data); /* 打印顶点，也可以其它操作 */
  p = GL->adjList[i].firstedge;
  while (p)
  {
    if (!visited[p->adjvex])
      DFS(GL, p->adjvex); /* 对未访问的邻接顶点递归调用 */
    p = p->next;
  }
}

/* 邻接表的深度遍历操作 */
void DFSTraverse(GraphAdjList GL)
{
  int i;
  for (i = 0; i < GL->numVertexes; i++)
    visited[i] = FALSE; /* 初始化所有顶点状态都是未访问过状态 */
  for (i = 0; i < GL->numVertexes; i++)
    if (!visited[i])  /* 对未访问过的顶点调用DFS，若是连通图，只会执行一次 */
      DFS(GL, i);
}
