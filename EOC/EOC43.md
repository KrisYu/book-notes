操作队列就是NSOperationQueue，也是一种常见的执行后台任务的方法。GCD基于它（？）

GCD 纯C， NSOperationQueue 是对象。它的优势在于：

- 取消操作， GCD是 fire and forget
- 指定操作间的依赖关系
- 通过键值观测机制监控NSOperation对象的属性
- 指定操作的优先级
- 重用NSOperation对象

NSNotificationCenter 选取操作队列而非派发队列。
