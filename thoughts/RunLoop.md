RunLoop对象处理来自窗口系统，Port对象和NSConnection对象的源（如鼠标和键盘事件）的输入。 RunLoop对象也处理Timer事件。

您的应用程序既不创建也不显式管理RunLoop对象。每个Thread对象（包括应用程序的主线程）都会根据需要自动创建一个RunLoop对象。如果您需要访问当前线程的运行循环，则可以使用当前的类方法执行此操作。

请注意，从RunLoop的角度来看，Timer对象不是“输入” - 它们是一种特殊的类型，其中一个意思是它们在启动时不会导致运行循环返回。


⚠️ RunLoop类通常不被认为是线程安全的，只能在当前线程的上下文中调用它的方法。您不应该尝试调用在不同线程中运行的RunLoop对象的方法，否则可能会导致意外的结果。


[NSTimer not firing when runloop is blocked](https://stackoverflow.com/questions/1995825/nstimer-not-firing-when-runloop-is-blocked)


[How update a label periodically on iOS (every second)? [duplicate]](https://stackoverflow.com/questions/6229759/how-update-a-label-periodically-on-ios-every-second)


> The problem is that a scheduledTimer will not get called while the main thread is tracking touches. You need to schedule the timer in the main run loop.

> So instead of doing

```
[NSTimer scheduledTimerWithTimeInterval:1.0f target:self selector:@selector(updateLabel:) userInfo:nil repeats:YES];
```

use 

```
NSTimer* timer = [NSTimer timerWithTimeInterval:1.0f target:self selector:@selector(updateLabel:) userInfo:nil repeats:YES];
[[NSRunLoop mainRunLoop] addTimer:timer forMode:NSRunLoopCommonModes];
```
这是看到RunLoop的应用。