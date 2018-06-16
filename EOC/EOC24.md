Swift中更容易实现这个，通过Extension来拆分更好的整理文件。

在OC中我们也可以通过Category实现：

```

@interface EOCPerson: NSObject

@property (nonatomic, copy, readonly) NSString *firstName;
@property (nonatomic, copy, readonly) NSString *lastName;
@property (nonatomic, copy, readonly) NSString *friends;

-(id) initWithFirstName: (NSString *)firstName
            andLastName: (NSString *)lastName;


/* Friends methods */
- (void) addFried: (EOCPerson *)person;
- (void) removeFriend: (EOCPerson *)person;
- (BOOL) isFriendsWith: (EOCPerson *)person;


/* Work methods */
- (void) performDaysWork;
- (void) takeVacationFromWork;

/* Play methods */
- (void) goToTheCinema;
- (void) goToSportsGame;

@end
```


分文件：

除了main ： EOCPerson 以外，继续分：

- EOCPerson + Friendship(.h/.m)
- EOCPerson + Work(.h/.m)
- EOCPerson + Play(.h/.m)


这样就可以

EOCPerson + Friendship.h

```
// EOCPerson + Friendship.h
#import "EOCPerson.h"

@interface EOCPerson: (Friendship)
- (void) addFried: (EOCPerson *)person;
- (void) removeFriend: (EOCPerson *)person;
- (BOOL) isFriendsWith: (EOCPerson *)person;

@end
```

EOCPerson + Friendship.m

```
//EOCPerson + Friendship.m
#import "EOCPerson + Friendship.h"

@implementation EOCPerson: (Friendship)
- (void) addFried: (EOCPerson *)person {

}

- (void) removeFriend: (EOCPerson *)person{

}

- (BOOL) isFriendsWith: (EOCPerson *)person{

}
```

‘私有’方法可以放入Private 类。
