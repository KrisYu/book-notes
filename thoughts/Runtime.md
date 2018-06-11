## Runtime

<del>终于写下了Runtime这几个字，感觉心情是沉重的.</del>

### objc_msgSend


按照作者的思路把 main.c 转化为 cpp文件之后，我们可以看到一大堆 struct 以及 #define，因为OC来自于C，所以我们都用struct以及struct pointer.


而main 函数长这样：

```
int main(int argc, char * argv[]) {
    A *aObjcet = ((A *(*)(id, SEL))(void *)objc_msgSend)((id)((A *(*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("A"), sel_registerName("alloc")), sel_registerName("init"));

    ((void (*)(id, SEL))(void *)objc_msgSend)((id)aObjcet, sel_registerName("b"));

    ((void (*)(id, SEL))(void *)objc_msgSend)((id)objc_getClass("A"), sel_registerName("c"));
}

```


A这个类本质上是 `typedef struct objc_object A;`, 是一个`objc_object`，在这个cpp文件中搜索可以发现，基本上所有的东西： NSURL，NSDictionary，NSNULL都是它。

sel_registerName 顾名思义就是选择器selector注册的名字，返回应该就是函数名。也是SEL类型。


#### 实例方法：

```
objc_msgSend(aObject, sel_registerName("b"));
```

#### 类方法：

```
objc_msgSend(objc_getClass("A"), sel_registerName("c"));
```

objc_getClass 返回struct objc_class 指路：`struct objc_class *objc_getClass(const char *)`


### objc_object 和 objc_class

按照作者的指引：

#### objc_object

```
// objc.h
typedef struct objc_class *Class;

/// Represents an instance of a class.
struct objc_object {
    Class isa  OBJC_ISA_AVAILABILITY;
};
```

可以看出来，首先 Class 是一个 struct objc_class 的指针，至于OBJC_ISA_AVAILABILITY，是C的某种样式（？等待探究

```
//objc-api.h
/* OBJC_ISA_AVAILABILITY: `isa` will be deprecated or unavailable 
 * in the future */
#if !defined(OBJC_ISA_AVAILABILITY)
#   if __OBJC2__
#       define OBJC_ISA_AVAILABILITY  __attribute__((deprecated))
#   else
#       define OBJC_ISA_AVAILABILITY  /* still available */
#   endif
#endif
```

> 动态类型id其实就是一个objc_object

这个也跟上面全篇到处都是objc_object对上了。

#### objc_class

```
struct objc_class {
    Class isa  OBJC_ISA_AVAILABILITY;

#if !__OBJC2__
    Class super_class                                        OBJC2_UNAVAILABLE;
    const char *name                                         OBJC2_UNAVAILABLE;
    long version                                             OBJC2_UNAVAILABLE;
    long info                                                OBJC2_UNAVAILABLE;
    long instance_size                                       OBJC2_UNAVAILABLE;
    struct objc_ivar_list *ivars                             OBJC2_UNAVAILABLE;
    struct objc_method_list **methodLists                    OBJC2_UNAVAILABLE;
    struct objc_cache *cache                                 OBJC2_UNAVAILABLE;
    struct objc_protocol_list *protocols                     OBJC2_UNAVAILABLE;
#endif

} OBJC2_UNAVAILABLE;
/* Use `Class` instead of `struct objc_class *` */
```

看来后面的常量部分就是一个指引，if endif 中的，就按照字面意思来理解。

这里有点不理解，如果按照这个来理解，那么就是如果不是objc2，我们就直接把它理解成isa， 否则再加上别的?

不管了，先按照作者来裂解，关注 isa，指向objc_class(也就是本身），super_class, objc_method_list.


### objc_method、SEL和IMP

其实 objc_method_list 顾名思义，就是这个class可以用的方法列表， objc_method长这样：

```
struct objc_method {
    SEL method_name                                          OBJC2_UNAVAILABLE;
    char *method_types                                       OBJC2_UNAVAILABLE;
    IMP method_imp                                           OBJC2_UNAVAILABLE;
}                                                            OBJC2_UNAVAILABLE;
```


#### SEL

> SEL is the Objective-C “type” for a selector

也可以跟着作者思路来理解.

#### IMP

imp 其实就是implement pointer。

> IMP是一个函数指针，指向objc_method对应方法的实现部分。


### objc_msgSend

#### 工作原理


```
/ 首先看一下objc_msgSend的方法实现的伪代码
id objc_msgSend(id self, SEL op, ...) {
   if (!self) return nil;
   // 关键代码（a）
   IMP imp = class_getMethodImplementation(self->isa, SEL op);
   imp(self, op, ...); // 调用这个函数，伪代码...
}
// 查找IMP
IMP class_getMethodImplementation(Class cls, SEL sel) {
    if (!cls || !sel) return nil;
    IMP imp = lookUpImpOrNil(cls, sel);
    if (!imp) {
      ... // 执行动态绑定
    }
    IMP imp = lookUpImpOrNil(cls, sel);
    if (!imp) return _objc_msgForward; // 这个是用于消息转发的
    return imp;
}
// 遍历继承链，查找IMP
IMP lookUpImpOrNil(Class cls, SEL sel) {
    if (!cls->initialize()) {
        _class_initialize(cls);
    }
    Class curClass = cls;
    IMP imp = nil;
    do { // 先查缓存,缓存没有时重建,仍旧没有则向父类查询
        if (!curClass) break;
        if (!curClass->cache) fill_cache(cls, curClass);
        imp = cache_getImp(curClass, sel);
        if (imp) break;
    } while (curClass = curClass->superclass); // 关键代码（b）
    return imp;
}

```

> 1、将一个objc_object结构体的isa指针（即其对应的objc_class结构体）和一个方法名SEL传入class_getMethodImplementation。
> 
> 2、在class_getMethodImplementation方法中，使用lookUpImpOrNil遍历继承链，若返回nil，则消息转发（消息转发下一章在讲）。
> 
> 3、在lookUpImpOrNil遍历继承链，即先在当前objc_class的cache中查找SEL，若没有，则在methodLists中查找，若存在，则将其放入该objc_class的cache中，然后返回IMP。若不存在，则通过super_class指针找到该class的父class，继续该步骤直到NSObject停止（NSObject的super_class指向nil）。
> 
> 4、执行得到的IMP。


### 类方法和实例方法


继续跟着作者走，发现实例方法，↓这样也可以运行成功。

```
IMP bIMP = class_getMethodImplementation([A class], @selector(b));
// 执行IMP
bIMP();
```

但是类方法则不行。

> objc_class的methodLists中只存有实例方法

类方法则需要这样才可以运行成功：

```
// 获取A类对应的metaClass
Class aMeta = objc_getMetaClass(class_getName([A class]));
// 在metaClass中找类方法d
IMP dIMP = class_getMethodImplementation(aMeta, @selector(d));
dIMP();
```


参考文章：[runtime进行曲，objc_msgSend的前世今生（一）](https://www.jianshu.com/p/c0157110caa5)


