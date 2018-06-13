Objective-C 的 Exception是致命的（fatal error），是终止程序，使之退出的exception。

所以对于不致命的error，OC的处理方式是：返回nil/0,或者NSError

NSError包括：

- Error domain
- Error code
- User info

NSError两种用法


- 代理方法会提示错误
- 一些方法通过参数传递错误


比如：

```
NSError *anyError;
    
BOOL success = [receivedData writeToURL:someLocalFileURL
                       error:&anyError];
    
if (!success) {
    NSLog("Write failed with error: %@", anyError);
}
```

如果对error不感兴趣，直接传递 NULL 给 error参数。


#### 你也可以自己创建error


```
NSString *domain = @"com.MyCompany.MyApplication.ErrorDomain";
NSString *desc = NSLocalizedString(@"Unable to…", @"");
NSDictionary *userInfo = @{ NSLocalizedDescriptionKey : desc };

NSError *error = [NSError errorWithDomain:domain
                                     code:-101
                                 userInfo:userInfo];
```


如果需要通过参数传回错误，方法签名长这样：

```
- (BOOL)doSomethingThatMayGenerateAnError:(NSError **)errorPtr;
```

指向error对象的指针


```
- (BOOL)doSomethingThatMayGenerateAnError:(NSError **)errorPtr {
    ...
    // error occurred
    if (errorPtr) {
        *errorPtr = [NSError errorWithDomain:...
                                        code:...
                                    userInfo:...];
    }
    return NO;
}
```

OC虽然有 try/catch，但是不推荐使用。总是先检查危险的操作（比如访问可能越界的数组下标），避免抛出异常。


