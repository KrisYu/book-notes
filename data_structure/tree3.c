/* 树的孩子兄弟表示法结构定义 */
typedef struct CSNode
{
  TElemType data;
  struct CSNode *firstchild, *rightsib;
} CSNode, *CSTree;


/*  结构 - 结点 | data | firstchild | rightsib | */
