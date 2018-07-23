/* 树的孩子表示法结构定义 */
#define MAX_TREE_SIZE 100
typedef struct CTNode  /* 孩子结点 */
{
  int child;
  struct CTNode *next;
} *ChildPtr;

typedef struct /* 表头结构 */
{
  TElemType data;
  ChildPtr firstchild;
} CTBox;

typedef struct  /* 树结构 */
{
  CTBox nodes[MAX_TREE_SIZE];
  int r, n;
} CTree;

/* 这种存储方式很有意思 */
/* 把每个结点的孩子结点排列起来，以单链表作为存储结构, 则n个结点有n个孩子链表，如果是叶子结点则此单链表为空。
   然后n个头指针又组成一个线性表，采用顺序存储结构，存放进一个一位数组 */

/*  结构 - 孩子结点 | child | next |
        - 表头结点 | data | firstchild | */
