### instancetype

在您的代码中，在适当的情况下，将id的出现次数替换为实例类型的返回值。 init方法和类工厂方法通常是这种情况。即使编译器自动转换以“alloc”，“init”或“new”开头的方法，并返回id类型以返回实例类型，但它不会转换其他方法。 Objective-C约定是为所有方法显式编写实例类型。

请注意，您应该将id替换为仅用于返回值的instancetype，而不是代码中的其他地方。与id不同，instancetype关键字只能用作方法声明中的结果类型。

例如：

```
@interface MyObject
- （id）myFactoryMethod;
@end
```

应该成为：

```
@interface MyObject
- （instancetype）myFactoryMethod;
@end
```

原因可以参考：[AdoptingModernObjective-C](https://developer.apple.com/library/archive/releasenotes/ObjectiveC/ModernizationObjC/AdoptingModernObjective-C/AdoptingModernObjective-C.html#//apple_ref/doc/uid/TP40014150-CH1-SW2)

最主要的instancetype做了类型检查。
