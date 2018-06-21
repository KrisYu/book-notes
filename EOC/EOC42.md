performSelector 原型：
 
```
 -(id) performSelector:(SEL)selector;
 
[object performSelector: @selector(selectorName)];
[object selectorName];

```

以上方法等效。但是使用技巧包括：

```
SEL selector;
  
if (/* some condition */) {
selector = @selector(foo);
} else if (/* some other condition */){
selector = @selector(bar);
} else {
selector = @selector(baz);
}
  
[object performSelector: selector];

```


问题在于我们并不知道selector是什么，可能会有需要释放内存的状况我们不知道而导致内存泄露。

```
SEL selector;
  
// 需要释放 
if (/* some condition */) {
selector = @selector(newObject);
// 需要释放
} else if (/* some other condition */){
selector = @selector(copy);
// 不需要
} else {
selector = @selector(someProperty);
}
  
id rect = [object performSelector: selector];
```


performSelector 还有家族伙伴很多， 比如带 afterDelay， onThread 等的。

有时候我们可以选择用：

```
⚠️
 [self performSelector:@selector(doSomething)
            withObject:nil
            afterDelay:5.0];

```

但是prefer dispatch_after 

```
✅
dispatch_time_t time = dispatch_time(DISPATCH_TIME_NOW,
                                   (int64_t)(5.0 * NSEC_PER_SEC));
  
dispatch_after(time, dispatch_get_main_queue(), ^{
[self doSomething];
});
```


```
⚠️
[object performSelectorOnMainThread:@selector(doSomething)
                       withObject:nil
                    waitUntilDone:NO];
                    
✅                    
dispatch_async(dispatch_get_main_queue(), ^{
  [self doSomething];
});
```           

