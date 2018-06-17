这里也提到了我们要把块的变量名放在类型之中。



作为变量

```
typedef int(^EOCSomeBlock) {BOOL flag, int value};
    
EOCSomeBlock block = ^(BOOL flag, int value){
    // implementation
}
```



作为属性

```
- (void)startWithCompletionHandler: ((void ^)(NSData *data, NSError * error)) completion;

```

简化


```
typedef void(^EOCCompletionHandler) (NSData *data, NSError *error);
- (void)startWithCompletionHandler: (EOCCompletionHandler) completion;
```

这样我们如果需要修改block类型也很简单。
