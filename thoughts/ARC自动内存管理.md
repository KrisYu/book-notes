### ARC自动内存管理的原则

自己生成的对象，自己持有
非自己生成的对象，自己可以持有
自己持有的对象不再需要时，需要对其进行释放
非自己持有的对象无法释放

### MRC年代

#### alloc/new/copy/mutableCopy 生成并持有对象

#### 上述方法以外的方法，自己不是该对象的持有者

```
id obj = [NSMutableArray array];

```

obj 并不持有对象


```
id obj = [NSMutableArray array];

[obj retain];
```

obj持有对象

查看SO：<https://stackoverflow.com/questions/5423211/difference-between-nsmutablearray-array-vs-nsmutablearray-alloc-init>

> The array class method by itself produces an autoreleased array, meaning you don't have to (and should not) release it manually.


实际上在现在的 Xcode 项目中写上如上代码`[obj retain];`会报错: 

> ARC forbids explicit message send of 'retain'
> 'retain' is unavailable: not available in automatic reference counting mode


写这样的代码一样会报错：

```
id obj = [[NSObject alloc] init];
    
[obj release];
```

错误跟上面的类似。

#### autorelease： 取得的对象存在，但自己并不持有对象。autorelase：使对象再超出指定的生存范围时能够自动并正确的释放（调用release方法）。

autorelase 类似C语言中的自动变量（局部变量）的特性。

```
{
	int a;
}
/*
 *  超出变量的作用域，
 *  自动变量 'int a' 被废弃，不可再访问
 */
```


autorelease的使用方法：

1. 生成并持有NSAutorelasePool对象
2. 调用已分配对象的autorelase实例方法
3. 废弃NSAutorelasePool对象


```
NSAutorelasePool *pool = [[NSAutorelasePool alloc]init];
    
id obj = [[NSObject alloc] init];
    
[obj autorelease];
    
[pool drain]; // = [obj release]

```

注意避免避免没有废弃NSAutorelasePool对象而导致内存不足的状况发生。


### ARC

`NSObject * -> 对象类型` ： 指针

`id -> void *`： id隐藏对象类型的类名部分

#### Strong 引起的 retain memory cycle

__strong 修饰符：“强引用”，变量obj在超出其变量作用域时，在该变量被废弃时，会是放弃被赋予的对象。


- 生成
- 持有
- 释放
- 废弃


注意 释放 ≠ 废弃


虽然部分释放了，但是reference count ≠ 0， 所以并未被废弃，而形成memory cycle，内存泄露。

对象之间强强引用，声明其中一个为weak解决循环问题。


#### Weak


__weak 修饰符： 弱引用，不持有对象（reference count 不加1？），所以在超出其变量作用域时，对象即被释放。 在持有某对象的弱引用时，若该对象被废弃，则此弱引用将自动失效且处于nil被赋值的状态（空弱引用）。

使用weak可能出现被提早释放，所以用一个strong的cache来记录它。



#### `__unsafe_unretained`

iOS 5 以及 OS X Lion 以上用 `__weak` 修饰，iOS 4以及 OS X Snow Leopard用`__unsafe_unretained`, `__unsafe_unretained`不属于内编译器的内存管理对象，赋值给附有 `__unsafe_unretained`修饰符变量的对象在通过该变量使用时，首先要确保其存在。


#### `__autoreleasing`




#### copy

copy是针对比如NSString，NSSMutableString也可以被声明为NSString，并且改变，所以我们声明copy，就会不受其影响，


#### atomic vs nonatomic

"不写的话默认就是atomic。

atomic 和 nonatomic 的区别在于，系统自动生成的 getter/setter 方法不一样。如果你自己写 getter/setter，那 atomic/nonatomic/retain/assign/copy 这些关键字只起提示作用，写不写都一样。

对于atomic的属性，系统生成的 getter/setter 会保证 get、set 操作的完整性，不受其他线程影响。比如，线程 A 的 getter 方法运行到一半，线程 B 调用了 setter：那么线程 A 的 getter 还是能得到一个完好无损的对象。

而nonatomic就没有这个保证了。所以，nonatomic的速度要比atomic快。

不过atomic可并不能保证线程安全。如果线程 A 调了 getter，与此同时线程 B 、线程 C 都调了 setter——那最后线程 A get 到的值，3种都有可能：可能是 B、C set 之前原始的值，也可能是 B set 的值，也可能是 C set 的值。同时，最终这个属性的值，可能是 B set 的值，也有可能是 C set 的值。

保证数据完整性——这个多线程编程的最大挑战之一——往往还需要借助其他手段。"

以上 atomic vs nonatomic 部分from：

作者：戴仓薯

链接：https://www.jianshu.com/p/7288eacbb1a2

來源：简书

著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。



默认是atomic

Effective Objective-C 建议多写nonatomic

