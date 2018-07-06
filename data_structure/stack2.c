/* 两栈共享空间结构 */
typedef struct {
  SElementType data[MAXSIZE];
  int top1; /* 栈1栈顶指针 */
  int top2; /* 栈2栈顶指针 */
} SqDoubleStack;

/* 结构的重点是在于再数组的两端，向中间靠拢*/
/* 若top1 = -1. 则栈1为空； 若top2 = n， 则栈2为空.*/

/* 插入元素e为新的栈顶元素 */
Status Push(SqDoubleStack *S, SElementType e, int stackNumber){
  if (S->top1 + 1 == S->top2) /* 栈已满，不能再push了*/
    return ERROR;
  if (stackNumber == 1) /* 栈1有元素进栈 */
    S->data[++S->top1] = e; /* 若栈1则先top1+1后给数组元素赋值 */
  else if (stackNumber == 2) /*栈2有元素进栈*/
    S->data[--S->top2] = 2; /* 若栈2则先top2-1后给数组元素赋值 */
  return OK;
}

/* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
Status Pop(SqStack *S, SElementType *e, int stackNumber){
  if (stackNumber == 1){
    if (S->top1 == -1)
      return ERROR;
    *e = S->data[S->top1--];
  } else if (stackNumber == 2) {
    if (S->top2 == MAXSIZE)
      return ERROR;
    *e = S->data[S->top2++];
  }
  return OK;
}
