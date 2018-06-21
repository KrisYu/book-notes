
这么做：

```
@implementation XXClass

+ (id)sharedInstance {
    static XXClass *sharedInstance = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        sharedInstance = [[self alloc] init];
    });
    return sharedInstance;
}
```

App中例子：


```
+ (UIColor*)wechatFontColor
{
	static UIColor* color = nil;
	static dispatch_once_t onceToken;
	dispatch_once(
      &onceToken,
      ^{
		  color = [UIColor colorWithRed:(54 / 255.0) green:(71 / 255.0) blue:(121 / 255.0) alpha:1];
	  });
	return color;
}
```


**Swift中我们则是这样做**：

```
class MyManager  {
    static let sharedInstance = MyManager()
    private init() {}
}
```

使用的时候这么用:

```
let instance = MyClass.shared

// iOS 开发中常用的单例
UIApplication.shared
NSNotification.shared
NSUserDefaults.shared
```
