### Category

任何一个类都可以声明一个类别，即使你不知道它实际代码是如何实现的（比如标准Cocoa或CocoaTouch类）。你在类别中声明的任何方法都可以在它原来类的实例对象和原来类的子类的实例对象中使用。在运行过程中，类别中声明和实现的方法和原来的类中声明的方法没有任何区别。

类似 Swift 的Extension.注意避免重名的状况。

语法长这样：

XYZPerson+XYZPersonNameDisplayAdditions.h

```
#import "XYZPerson.h"

@interface XYZPerson (XYZPersonNameDisplayAdditions)

- (NSString *)lastNameFirstNameString;

@end
```

XYZPerson+XYZPersonNameDisplayAdditions.m

```
#import "XYZPerson+XYZPersonNameDisplayAdditions.h"

@implementation XYZPerson (XYZPersonNameDisplayAdditions)

- (NSString *)lastNameFirstNameString {

    return [NSString stringWithFormat:@"%@, %@", self.lastName, self.firstName];

}

@end
```



### Category添加属性

虽然 Apple 官方文档 - [定制已有的类](https://github.com/L1l1thLY/Programming-with-Objective-C-in-Chinese/blob/dev/5.定制已有的类Customizing-Existing-Classes.md)

> 实例方法和类方法都可以在类别中声明，但是一般不在类别中声明一个新的属性。尽管你能在类别中声明一个额外属性，但你却不能声明一个相应的实例变量。这意味着编译器既不会自动生成类别中新增加的属性对应的实例变量，也不会自动生成这些属性的存取方法。你可以在分类中实现自己的存取方法，但你写的存取方法只能读取原来类保存的属性。

> 为一个已有类添加新的属性的唯一方法就是使用类的延伸(class extension),这将在接下来的章节介绍。


但实际上我们可以在category中定义属性，感谢**关联对象、objc_msgSend、消息转发**，我们能够可以做到：

看so这个回答：

[Objective-C: Property / instance variable in category](https://stackoverflow.com/questions/8733104/objective-c-property-instance-variable-in-category)

Tested only with iOS 9 Example: Adding an UIView property to UINavigationBar (Category)

```
UINavigationBar+Helper.h

#import <UIKit/UIKit.h>

@interface UINavigationBar (Helper)
@property (nonatomic, strong) UIView *tkLogoView;
@end
```

```
UINavigationBar+Helper.m



#import "UINavigationBar+Helper.h"
#import <objc/runtime.h>

#define kTKLogoViewKey @"tkLogoView"

@implementation UINavigationBar (Helper)

- (void)setTkLogoView:(UIView *)tkLogoView {
    objc_setAssociatedObject(self, kTKLogoViewKey, tkLogoView, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}

- (UIView *)tkLogoView {
    return objc_getAssociatedObject(self, kTKLogoViewKey);
}

@end
```

看一下里面提到的函数：

- void objc_setAssociatedObject(id object, void *key, id value, objc_AssociationPolicy policy)
- id objc_getAssociatedObject(id object, void *key)



objc_AssociationPolicy | @property
------------- | -------------
OBJC_ASSOCIATION_ASSIGN | assign
OBJC_ASSOCIATION_RETAIN_NONATOMIC  | nonatomic, retain
OBJC_ASSOCIATION_COPY_NONATOMIC  | nonatomic, copy
OBJC_ASSOCIATION_RETAIN  | retain
OBJC_ASSOCIATION_COPY | copy


看到网易的iOS笔试题中出现过：

给类NSObject扩展一个类别 NSObject+ CategoryA，并且在该类别中添加一个名为aString的NSString类型的属性。

```
@interface NSObject （CategoryA）
@property (nonatomic, copy) NSString *aString;
@end


static const void * kAStringKey = & kAStringKey;
@implementation NSObject (CategoryA)

- (NSString *)aString {
  return objc_getAssociatedObject(self, kAStringKey);
}

- (void)setAString:(NSString *)aString{
  objc_setAssociatedObject(self, kAStringKey, aString, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}
@end
```


感觉这个地方应该用 OBJC_ASSOCIATION_COPY_NONATOMIC



