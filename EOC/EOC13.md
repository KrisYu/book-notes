因为method也是在运行时确定，所以我们可以重新映射方法。

IMP 定义： id (*IMP)(id, SEL, ...)


#### 交换方法一：

```
#import <Foundation/Foundation.h>
#import <objc/runtime.h>

int main(int agrv, char * argv[]){

  Method originalMethod = class_getInstanceMethod([NSString class],@selector(lowercaseString));
  Method swappedMethod = class_getInstanceMethod([NSString class],@selector(uppercaseString));

  method_exchangeImplementations(originalMethod, swappedMethod);

  NSString *string = @"ThIs iS tHe StRing";

  NSString *lowercaseString = [string lowercaseString];
  NSLog(@"lowercaseString = %@", lowercaseString);
  // lowercaseString = THIS IS THE STRING

  NSString *uppercaseString = [string uppercaseString];
  NSLog(@"uppercaseString = %@", uppercaseString);
  // uppercaseString = this is the string
  
  return 0;
}
```

#### 交换方法二：


```
#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface NSString (EOCMyAdditions)
- (NSString *)eoc_myLowercaseString;
@end

@implementation NSString (EOCMyAdditions)
- (NSString *)eoc_myLowercaseString {
  NSString *lowercase = [self eoc_myLowercaseString];
  NSLog(@"%@ => %@", self, lowercase);
  return lowercase;
}
@end

int main(int agrv, char * argv[]){

  Method originalMethod = class_getInstanceMethod([NSString class],@selector(lowercaseString));
  Method swappedMethod = class_getInstanceMethod([NSString class],@selector(eoc_myLowercaseString));

  method_exchangeImplementations(originalMethod, swappedMethod);

  NSString *string = @"ThIs iS tHe StRing";

  NSString *lowercaseString = [string lowercaseString];

  return 0;
}
```

感觉 method swizzling 是iOS逆向开发的一个基础，比如那些整 wechat 防消息撤回的之类。

