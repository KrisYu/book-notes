typedef char VertexType;   /* 顶点类型应由用户定义 */
typedef int EdgeType;      /* 边上的权值类型应由用户定义 */
#define MAXVEX 100;        /* 最大顶点数，应由用户定义 */
#define INFINITY 65535;    /* 用65535来代表∞ */

typedef struct
{
  VertexType vexs[MAXVEX];       /* 顶点表 */
  EdgeType arc[MAXVEX][MAXVEX];  /* 邻接矩阵，可看做边表 */
  int numVertexes, numEdges;     /* 图中当前的顶点数和边数 */
} MGraph;

/* 建议无向网图的邻接矩阵表示 */
void CreateMGraph(MGraph *G)
{
  int i, j, k, w;
  printf("输入顶点数和边数：\n", );
  scanf("%d %d",&G->numVertexes, &G->numEdges);  /* 输入顶点数和边数 */
  for (i = 0; i < G->numVertexes; i++) /* 读入顶点信息，建立顶点表 */
    scanf(&G->vexs[i]);
  for (i = 0; i < G->numEdges; i++)
    for (j = 0; j < G->numEdges; j++)
      G->arc[i][j = INFINITY; /* 邻接矩阵初始化 */
  for (k = 0; k < G->numEdges; k++) /* 读入numEdges条边，建立邻接矩阵 */
  {
    printf("输入边(vi, vj)上的下标i, 下标j和权w: \n");
    scanf("%d,%d,%d",&i, &j, &w);
    G->arc[i][j] = w;
    G->arc[j][i] = G->arc[i][j];  /* 因为是无向图，邻接矩阵*/
  }
}