/* 二叉树的二叉连表结点结构定义 */
typedef struct BiTNode             /* 结点结构 */
{
  int data;                        /* 结点数据 */
  struct BiTNode *lchild, *rchild; /* 左右孩子指针 */
} BiTNode, *BiTree;

/* 递归查找二叉排序树中T是否存在key */
/* 指针f指向T的双亲，其初始调用值为NULL */
/* 若查找成功，则指针p指向该数据元素结点，并返回TRUE */
/* 否则指针p指向查找路径上访问的最后一个结点并返回FALSE */
Status SearchBST(BiTree T, int key, BiTree f, BiTree *p)
{
  if (!T)   /* 查找不成功 */
  {
    *p = f;
    return FALSE;
  }
  else if (key == T->data) /* 查找成功*/
  {
    *p = T;
    return TRUE;
  }
  else if (key < T->data)
    return SearchBST(T->lchild, key, T, p); /* 在左子树继续查找 */
  else
    return SearchBST(T->rchild, key, T, p); /* 在右子树继续查找 */
}

/* 当二叉排序树T中不存在关键字等于key的数据元素时 */
/* 插入key并返回TRUE，否则返回FALSE */
Status InsertBST(BiTree *T, int key)
{
  BiTree p, s;
  if (!SearchBST(*T, key, NULL, &p)) /* 查找不成功 */
   {
    s = (BiTree) malloc (sizeof(BiTNode));
    s->data = key;
    s->lchild = s->rchild = NULL;
    if (!p)
      *T = s;  /* 插入s为新的根结点 */
    else if (key < p->data)
      p->lchild = s; /* 插入s为左孩子 */
    else
      p->rchild = s; /* 插入s为右孩子 */
    return TRUE;
  }
  else
    return FALSE;   /* 树种已有关键字相同的顶点，不再插入 */
}

/* insertion from wikipedia, c++ example */
Node* insert(Node* root, int key, int value) {
  if (!root)
    root = new Node(key, value);
  else if (key == root->key)
    root->value = value;
  else if (key < root->key)
    root->left = insert(root->left, key, value);
  else  // key > root->key
    root->right = insert(root->right, key, value);
  return root;
}


/* 若二叉排序树T中存在关键字等于key的数据元素时，则删除该数据元素结点,
   并返回TRUE，否则返回FALSE */
Status DeleteBST(BiTree *T, int key)
{
  if (!*T) /* 不存在关键字等于key的数据元素 */
    return FALSE;
  else
  {
    if (key == (*T)->data) /* 找到关键字等于key的数据元素 */
      return Delete(T);
    else if (key < (*T)->data)
      return DeleteBST(&(*T)->lchild, key);
    else
      return DeleteBST(&(*T)->rchild, key);
  }
}

/* 从二叉排序树中删除结点p，并重接它的左或者右子树 */
Status Delete(BiTree *p)
{
  BiTree q, s;
  if ((*p)->rchild == NULL) /* 右子树空则只需重接它的左子树*/
  {
    q = *p;
    (*p) = (*p)->lchild;
    free(q);
  }
  else if (((*p)->lchild == NULL)  /* 只需重接它的右子树 */
  {
    q = *p;
    (*p) = (*p)->rchild;
    free(q);
  }
  else /* 左右子树均不空 */
  {
    q = *p;
    s = (*p)->lchild;
    while (s->rchild) /* 转左，然后向右到尽头(找待删结点的前驱) */
    {
      q = s;
      s = s->rchild;
    }
    (*p)->data = s-> data;  /* s指向被删结点的直接前驱 */
    if (q != *p)
      q->rchild = s->lchild; /* 重接q的右子树 */
    else
      q->lchild = s->lchild; /* 重接q的左子树 */
    /* 以上的 if 和 else 对应两种可能：
    一种是直接前驱就是这个结点的左孩子
    另一种直接前驱是左孩子的右边某结点 */
    free(s)
  }
  return TRUE;
}
