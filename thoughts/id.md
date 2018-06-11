### id

它表示“指向未知/未指定对象类型的指针”。

id myObject;

实际上，所有对象指针（例如NSString *）在运行时都会像id一样对待。

但是在编译时，如果你输入NSString *而不是id，编译器可以帮助你。 它可以发现错误，并
提出适合发送给它的方法等。

如果你使用id键入某些东西，编译器不能提供帮助，因为它不太了解。 在运行时发送消息时确定要执行的代码称为“动态绑定”。

### 它安全吗？

在运行时将所有对象指针视为“指向未知类型的指针”似乎很危险，对吧？

什么阻止你发送消息到一个不明白的对象？

没有。 如果你这样做，你的程序崩溃。 实际上并不是的。

因为我们大多使用静态类型（例如NSString *），编译器非常聪明。


### IntroSpection

所有从NSObject继承的对象都知道这些方法...

- isKindOfClass：返回一个对象是否是那种类（包含继承）
- isMemberOfClass：返回一个对象是否是那种类（无继承）
- respondsToSelector：返回一个对象是否响应给定的方法

它会在运行时计算这些问题的答案（即在您发送它们的瞬间）。

这些方法的参数是一个棘手的类测试方法需要一个类

通过将类方法类发送到类（而不是实例方法类）来获得类。 

```
if（[obj isKindOfClass：[NSString class]]）{
        NSString * s = [（NSString *）obj stringByAppendingString：@“xyzzy”];
}
```


### 方法测试方法采用选择器（SEL）

特殊的@selector（）指令将方法的名称转换为选择器

```
if ([obj respondsToSelector:@selector(shoot)]) {
    [obj shoot];
} else if ([obj respondsToSelector:@selector(shootAt:)]) {
    [obj shootAt:target];
}
```

SEL is the Objective-C “type” for a selector

- SEL shootSelector = @selector(shoot);
- SEL shootAtSelector = @selector(shootAt:);
- SEL moveToSelector = @selector(moveTo:withPenColor:);

注意selector的名字，有没有‘：’不一样。


如果你有一个SEL，你也可以请求一个对象来执行它...


```
[obj performSelector:shootSelector];[obj performSelector:shootAtSelector withObject:coordinate];
```

在NSArray中使用makeObjectsPerformSelector：方法

```
[array makeObjectsPerformSelector：shootSelector]; 
[array makeObjectsPerformSelector：shootAtSelector withObject：target]; // target是一个id
```

看到以上的NSArray方法，莫名想到的OC的map也可以用它，so上果然有人是这么做的，更常见/通用的是用block（enumerateObjectsUsingBlock:）


在UIButton中，

```
(void）addTarget：（id）anObject action：（SEL）action ...;
[button addTarget：self action：@selector（digitPressed :) ...];
```