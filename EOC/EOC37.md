block 如果要修改变量，需要 __block修饰符

但是block如果定义在OC类的实例方法中，他可以访问/修改类的所有实例变量（无需__block修饰符），还可以使用self变量。

不过如果捕获了实例变量，那么它也会自动捕获self，因为实例变量总是与self所指代的实例关联在一起。


块的内部结构也很有意思：


类型  | 名字
------------- | -------------
void *| isa
int | flags
int | reserved
void (*)(void *,..) | invoke
struct *| descriptor


isa 是指向class对象的指针， invoke 指向快实现的代码。


block是存在于栈中。

然而我们可以copy它，把它变成heap block 堆块

```

void (^block)();
    
if (/* some condition */) {
    block = [[^{NSlog("Block A");}] copy];
} else {
    block = [[^{NSlog("Block B");}] copy];
}
    
block()
    
```

