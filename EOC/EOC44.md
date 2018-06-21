dispatch group可以将任务分组，执行等待/阻塞等操作。


```
dispatch_group_t dispatch_group_create();

//分组执行 可用方法一
void dispatch_group_async(dispatch_group_t group, 
							  dispatch_queue_t queue, 
							  dispatch_block_t block);
							  
							  

// 方法二
void dispatch_group_enter(dispatch_group_t group);
void dispatch_group_leave(dispatch_group_t group);


```


只记得在[Regift](https://github.com/matthewpalmer/Regift/blob/master/Regift/Regift.swift)这个库中，我们用 enter / leave 来控制，将异步操作变为同步。
