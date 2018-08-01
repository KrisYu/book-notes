/* 结构  | data | firstedge| -> | adjvex | weight | next | */

typedef char VertexType;   /* 顶点类型应由用户定义 */
typedef int EdgeType;      /* 边上的权值类型应由用户定义 */

typedef struct EdgeNode    /* 边表结点 */
{
  int adjvex;              /* 邻接点域，存储该顶点对应的下标 */
  EdgeType weight;         /* 用于存储权值，对于非网图可以不需要 */
  struct EdgeNode *next;   /* 链域，指向下一邻接点 */
} EdgeNode;


typedef struct VertexNode  /* 顶点表结点 */
{
  VertexType data;         /* 顶点域，存储顶点信息 */
  EdgeNode *firstedge;     /* 边表头指针 */
} VertexNode, AdjList[MAXVEX];

typedef struct
{
  AdjList adjList;   /* 感觉这里的AdjList就是 AdjList[MAXVEX]? */
  int numVertexes, numEdges; /* 图中当前顶点数和边数 */
} GraphAdjList;

/* 建立图的邻接表结构 */
void CreateALGraph(GraphAdjList *G)
{
  int i,j,k;
  EdgeNode *e;
  printf("输入顶点数和边数：\n", );
  scanf("%d,%d",&G->numVertexes, &G->numEdges);  /* 输入顶点数和边数 */
  for (i = 0; i < G->numVertexes; i++)  /* 读入顶点信息，建立顶点表 */
  {
    scanf(&G->adjList[i].data);          /* 输入顶点信息 */
    G->adjList[i].firstEdge = NULL;      /* 将边表置为空表 */
  }
  for (k = 0; k < G->numEdges; k++) /* 建立边表 */
  {
    printf("输入边(vi, vj)上的顶点序号: \n");
    scanf("%d,%d" ,&i, &j); /* 输入边(vi, vj)上的顶点序号 */
    e = (EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间, 生成边表结点 */

    e->adjvex = j;    /* 邻接序号为j */
    e->next = G->adjList[i].firstEdge; /* 将e指针指向当前顶点指向的结点 */
    G->adjList[i].firstedge = e; /* 将当前顶点的指针指向e */

    e = (EdgeNode *)malloc(sizeof(EdgeNode)); /* 向内存申请空间, 生成边表结点 */
    e->adjvex = i;  /* 邻接序号为i */
    e->next = G->adjList[j].firstedge; /* 将e指针指向当前顶点指向的结点 */
    G->adjList[j].firstedge = e; /* 将当前顶点的指针指向e */
  }
}

/* 这里是无向图，然后我们使用了单链表的头插法 */
