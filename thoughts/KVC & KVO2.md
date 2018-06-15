### LabColor的例子

这个例子中很特别的是把KVO抽象出来成为一个单独的类

```
@property (nonatomic, strong) id colorObserveToken;
```

这个id实际上是：“KeyValueObserver” 辅助类


> KeyValueObserver 辅助类 封装了 -addObserver:forKeyPath:options:context:，-observeValueForKeyPath:ofObject:change:context:和-removeObserverForKeyPath: 的调用，让视图控制器远离杂乱的代码



这个类里面有很多转化和修饰符啊|||

#### KeyValueObserver.h 文件
暴露在外的 property 包括  id target(weak) 和 SEL selector。

暴露在外的方法是类方法：

```
+ (NSObject *)observeObject:(id)object keyPath:(NSString*)keyPath target:(id)target selector:(SEL)selector __attribute__((warn_unused_result));

/// Create a key-value-observer with the given KVO options
+ (NSObject *)observeObject:(id)object keyPath:(NSString*)keyPath target:(id)target selector:(SEL)selector options:(NSKeyValueObservingOptions)options __attribute__((warn_unused_result));
```

区别一个有options， 一个没有|||


要求selector对应方法

```
/// The @c selector should conform to
/// @code
/// - (void)nameDidChange:(NSDictionary *)change;
/// @endcode
```

#### KeyValueObserver.m文件

.m 文件中类的扩展，也就是‘私有属性’包含有：

```
@interface KeyValueObserver ()
@property (nonatomic, weak) id observedObject;
@property (nonatomic, copy) NSString* keyPath;
@end
```


然后有一个 init 方法，两个类方法都是搭建再这个init方法上的，区别也就是 options 是否设置为0.


dealloc 也很容易理解，因为总是要移除观察方法的。


```
- (void)observeValueForKeyPath:(NSString*)keyPath ofObject:(id)object change:(NSDictionary*)change context:(void*)context
{
    if (context == (__bridge void *)(self)) {
        [self didChange:change];
    }
}

- (void)didChange:(NSDictionary *)change;
{
    id strongTarget = self.target;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Warc-performSelector-leaks"
    [strongTarget performSelector:self.selector withObject:change];
#pragma clang diagnostic pop
}

```

这两个方法也是否说明为什么我们的 selector 需要对应 nameDidChange（？）

然后还可以注意的地方是： `id strongTarget = self.target;` 是为了防止突然变nil么？因为是weak？


#### ViewController.m 文件

在 .m 文件中，我们所做的事包括定义：

```
@property (nonatomic, strong) id colorObserveToken;

- (void)setLabColor:(LabColor *)labColor
{
    _labColor = labColor;
    self.colorObserveToken = [KeyValueObserver observeObject:labColor keyPath:@"color" target:self selector:@selector(colorDidChange:) options:NSKeyValueObservingOptionInitial];
    ...
}


- (void)colorDidChange:(NSDictionary *)change;
{
    self.colorView.backgroundColor = self.labColor.color;
}
```

这样就完成任务了


#### 原理

原理是通过调用` - (void)willChangeValueForKey:(NSString *)key` 和 `- (void)didChangeValueForKey:(NSString *)key` 来完成。



=======================

待读




