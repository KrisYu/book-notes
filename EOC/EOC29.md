补充：

引用树回溯： 根对象 root object在 Mac OS X中是 NSApplication对象，在iOS中是 UIApplication对象。

悬挂指针： 指向无效对象的指针。


属性存取方法

```
- (void)setFoo: (id)foo {
	[foo retain];   // 保留新值
	[_foo release]; // 释放旧值
	_foo = foo;     // 指向新值
}
```


memory cycle 在垃圾收集环境中（garbage collection）会被认定为‘孤岛’，会被收走，但是reference count中就要使用weak reference的方法。