 接着第24条，利用分类更好的整理类，你可能会做这样的事：
 
 
 EOCPerson + Friendship.h

```
// EOCPerson + Friendship.h
#import "EOCPerson.h"

@interface EOCPerson: (Friendship)
@property (nonatomic, strong) NSArray *friends;
- (BOOL) isFriendsWith: (EOCPerson *)person;

@end
```

如果硬要去实现分类中的属性的话：

```
@implementation EOCPerson (Friendship)

- (NSArray *)friends {
    return objc_getAssociatedObject(self, kFriendsPropertyKey);
}

- (void) setFriends{
    objc_setAssociatedObject(self,
                             kFriendsPropertyKey,
                             friends,
                             OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}


@end
```


也就是跟之上的一条 Category中添加属性: [解答](thoughts/Category添加属性.md)一样


并且不推荐做这种事



放只读属性好很多：


```

@interface NSCalendar (EOC_Addtions)
@property (nonatomic, strong, readonly) NSArray *eoc_allMonths;
@end

@implementation NSCalendar (EOC_Addtions)
- (NSArray *) eoc_allMonths {
    if ([self.calendarIdentifier isEqualToString: NSCalendarIdentifierGregorian]) {
        return @[@"January", @"February",
                 @"March", @"April",
                 @"May", @"June",
                 @"July", @"August",
                 @"September", @"October",
                 @"Novemeber", @"December"];
    } else if {
        /* return months for other calendars */
    }
}
```



但是推荐的是直接声明一个方法

```
@interface NSCalendar (EOC_Addtions)
- (NSArray *)eoc_allMonths;
@end

```


eoc26条：

- 把封装数据所用的全部属性都定义在主接口里。
- 在’class- continuation分类‘之外的其他分类中，可以定义存取方法，但是尽量不要定义属性。