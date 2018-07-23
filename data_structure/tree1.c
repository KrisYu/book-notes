/* 树的双亲表示法结点结构的定义 */
#define MAX_TREE_SIZE 100
typedef int TElemType;  /* 树节点的数据类型，目前暂定为整数 */
typedef struct PTNode /* 结点结构 */
{
  TElemType data;  /* 结点数据 */
  int parent;     /* 双亲位置 */
}PTNode;
typedef struct
{
  PTNode nodes[MAX_TREE_SIZE];  /* 结点数组 */
  int r, n;  /* 根的位置和结点数 */
} PTree;

/* 这个结构可以根据结点的parent很容易找到它的parent，但是如果要寻找孩子，则需要遍历 */
/* 我们当然可以根据需要重新调整存储结构，让它更适用于我们需要的场景 */

/*  结构 | data | parent | */
