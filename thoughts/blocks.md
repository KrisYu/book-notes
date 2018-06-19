block 跟 closure 一样： 带有自动变量（局部变量）的匿名函数。

当然OC的block 就是 Swift的closure.


### 基本语法

Block语法与一般的C语言函数相比的不同：

1. 没有函数名
2. 带有 ^



^ 返回值类型 参数列表 表达式

^int (int count) { return count + 1; }


- 可以省略返回值类型

^  参数列表 表达式

^(int count) { return count + 1; }

- 如果没有参数，参数列表也可以省略

^ void (void){ printf("Blocks\n"); }

可以省略成：

^ { printf("Blocks\n"); }


直接就变成了： ^ 表达式


#### 可做变量

声明：

int (^blk)(int);

声明了一个返回为int， 接受参数为int，名字为 blk 的block.

> 与前面的使用函数指针的源代码对比可知，声明block类型变量仅仅是将声明函数指针类型变量的 '*' 变成 '^'. 

**这个变量也是第一公民，与其他变量区别不大。**


复习一下函数指针的编写方法：

- 编写函数: int callme(int a, int b)
- 指针语法包装: int (*callme)(int a, int b)
- 改成指针名字: int (*compare_cb)(int a, int b)

int (*tester)(int a, int b) = sorted_order;

tester(2, 3)的结果和sorted_order(2, 3)结果一样，调用sorted_order函数

即使一个函数返回的指针，那么它的编写方法依旧一致：

- 编写： char *make_coolness(int awesome_levels);
- 包装： char *( *make_coolness)(int awesome_levels)
- 重命名： char *( *coolness_cb)(int awesome_levels)

这里我们用这样的 typedef之后：

```
typedef int (*compare_cb)(int a, int b);

使用:
int *bubble_sort(int *numbers, int count, compare_cb cmp){
  ...
  ...if (cmp(target[j], target[j+1]) > 0)...
  
  ...
}
```

声明 + 赋值

int (^blk)(int) = ^int (int count) { return count + 1; }


block可做函数的参数

```
void func(int (^blk)(int)){

```

这里的参数是 block， 类型是 接受int，返回int， 这个block 名字是blk


返回值

```
int ((^func)(int)){
  return ^(int count) { return count + 1; }
}
```

这个样子有点古怪和难以理解：
如果是我，可能会写成

```
^int (int count) func {
	...
}
```

但是发现这个SO回答：

[Objective-C Block type as return value](https://stackoverflow.com/questions/3948173/objective-c-block-type-as-return-value)


这个写的都跟我想的不太一样

```
void (^f())(void) { 
  return ^{};
}
```

还有要么这么写：

```
typedef void(^MyAwesomeBlock)(void);

MyAwesomeBlock blockFunction()
{
    MyAwesomeBlock block = ^{
        //some code;
    };

    return block;
}
```
这个问题又牵扯到： [How do you read C declarations?](https://stackoverflow.com/questions/89056/how-do-you-read-c-declarations)

所以还是记住一般的typedef写法吧：

```
typedef int (^blk_t)(int)
```

typedef 生命了 blk_t 类型变量，这是一个closure， 接收int，返回int

然后写法更新为：

```
void func(blk_t blk)

blk_t func 
```


调用blk变量

```
int result = blk(10);
```


C vs OC 执行：

```
// c
int func(blk_t blk, int rate){
	return blk(rate);
}


//oc

- (int) methodUsingBlock: (blk_t)blk rate:(int)rate{
	return blk(rate);
}
```


Block 可以跟C语言的变量一起使用，所以甚至都可以创建指针。

```
typedef int (^blk_t)(int);

blk_t blk = ^(int count) { return count + 1; };

blk_t *blkptr = &blk;

(* blkptr)(10);
```


#### 截取变量


```
#include <stdio.h>

int main(){
  int dmy = 256;
  int val = 10;
  const char *fmt = "val = %d\n";
  void (^blk)(void) = ^{ printf(fmt, val); };

  val = 2;
  fmt = "These values were changed. val = %d\n";

  blk();

  return 0;
}
```

执行结果是 val = 10, block是执行其语法是获得的变量值。


block获取的是它拍照瞬间的值。

#### __block


```
#include <stdio.h>

int main(){
  int val = 0;
  void (^blk)(void) = ^{ val = 1; };

  blk();

  printf("val = %d\n", val);
  return 0;
}
```

报错：block2.m:5:30: error: variable is not assignable
      (missing __block type specifier)
      
所以如果我们再block中如果想改变block语法以外的变量值，需要给变量附件__block说明符。


```
// block3.m

#include <stdio.h>

int main(){
  __block  int val = 0;
  void (^blk)(void) = ^{ val = 1; };

  blk();

  printf("val = %d\n", val);
  return 0;
}

//gcc block3.m -o block3 -framework Foundation
// ./block3
// val = 1
```

改变成功。


#### 截获的自动变量

```
// block4.m 
#import <Foundation/Foundation.h>

int main(){
  id array = [[NSMutableArray alloc] init];

  void (^blk)(void) = ^{
    id obj = [[NSObject alloc] init];
    [array addObject:obj];
  };

  blk();

  return 0;
}
```

这样不会报错，但是如果我们直接对array赋值就会出错。跟上面的__block情况一样。


### block的实现


```
//  clang -rewrite-objc blocks0.m
//  blocks0.m
#include <stdio.h>

int main(){

  void (^blk)(void) = ^{ printf("Block\n"); };

  blk();

  return 0;
}
```

看blocks的实质

```
struct __block_impl {
  void *isa;
  int Flags;
  int Reserved;
  void *FuncPtr;
};
```

原来block真是这样的啊， void *isa, int flags, int reserved, void *FuncPtr, 这是定义的block

```
struct __main_block_impl_0 {
  struct __block_impl impl;
  struct __main_block_desc_0* Desc;
  __main_block_impl_0(void *fp, struct __main_block_desc_0 *desc, int flags=0) {
    impl.isa = &_NSConcreteStackBlock;
    impl.Flags = flags;
    impl.FuncPtr = fp;
    Desc = desc;
  }
};

static void __main_block_func_0(struct __main_block_impl_0 *__cself) {
 printf("Block\n"); }
 
 static struct __main_block_desc_0 {
  size_t reserved;
  size_t Block_size;
} __main_block_desc_0_DATA = { 0, sizeof(struct __main_block_impl_0)};

```


