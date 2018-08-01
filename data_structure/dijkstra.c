#define MAXVEX 9
#define INFINITY 65535
typedef int Pathmatirx[MAXVEX]; /* 用于存储最短路径下标的数组 */
typedef int ShortPathTable[MAXVEX]; /* 用于存储到各点最短路径的权值和 */
/* Dijkstra 算法，求有向网G的v0顶点到其余顶点v最短路径P[v]及带权长度D[v] */
/* F[v]的值为前驱节点下表，D[v]表示v0到v的最短路径长度和 */
void ShortestPath_Dijkstra(MGraph G, int v0, Pathmatirx *P, ShortPathTable *D)
{
  int v,w,k,min;
  int final[MAXVEX]; /* final[w] = 1 表示求得顶点v0至vw的最短路径 */
  for (v = 0; v < G.numVertexes; v++)  /* 初始化数据 */
  {
    final[v] = 0; /* 全部顶点初始化为未知最短路径状态 */
    (*D)[v] = G.matrix[v0][v]; /* 将与v0点有连接的顶点加上权值 */
    (*P)[v] = 0; /*初始化路径数组P为0 */
  }

  (*D)[v0] = 0; /* v0至v0路径为0 */
  final[v0] = 1; /* v0至v0不需要求路径 */
  /* 开始主循环，每次求得v0到某个v顶点的最短路径 */
  for ( v = 1; v < G.numVertexes; v++)
  {
    min = INFINITY;  /* 当前所知离v0顶点的最近距离 */
    for ( w = 0; w < G.numVertexes; w++)  /* 寻找离v0最近的顶点 */
    {
      if (!final[w] && (*D)[w] < min)
      {
        k = w;
        min = (*D)[w]; /* w顶点离v0顶点更近 */
      }
    }
    final[k] = 1; /* 将目前找到的最近顶点置为1 */
    for ( w = 0; w < G.numVertexes; w++)
    {
      /* 如果经过v顶点的路径比现在这条路径的长度短的话 */
      if (!final[w] && (min + G.matrix[k][w] < (*D)[w]))
      {
        /* 说明找到了更短的路径，修改D[w]和P[w] */
        (*D)[w] = min + G.matrix[k][w]; /* 修改当前路径长度 */
        [*P][w] = k;
      }
    }
  }
}

/*
  Dijkstra算法并不是一下子就求出了v0到v8的最短路径，而是一步步求出它们之间顶点的最短路径
  过程中都是基于已经求出的最短路径的基础上，求得更远顶点的最短路径，最终得到你要的结果。

*/
