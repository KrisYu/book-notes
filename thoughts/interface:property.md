参考文章： [iOS，objective_C中用@interface和 @property 方式声明变量的区别](http://www.cnblogs.com/letmefly/archive/2012/07/20/2601338.html)


@interface / @property 定义变量

- 最常看到是用 @property 定义变量（属性），至于它所做的事已经在另一篇中写到了。
- 其次是@interface中，但是这样需要自己写 @synthesize/ setter/ getter，这二个iOS programming中见到过
- 还有两种混用的


发现两种混用的用了 synthesize， 但是并没有写getter 和 setter。这样写真是让人迷惑啊||||

```
// .h
@interface Character: NSObject {
  NSString *characterName;
  NSInteger ownedClowCards;
}

@property (nonatomic, copy) NSString *characterName;
@property NSInteger ownedClowCards;

@end

//  .m
@synthesize characterName;
@synthesize ownedClowCards;
```

事实证明：这样也是对的

至少这样的代码能run出来。

```
// kvc.m
#import <Foundation/Foundation.h>

@interface Character: NSObject {
  NSString *characterName;
  NSInteger ownedClowCards;
}

@property (nonatomic, copy) NSString *characterName;
@property NSInteger ownedClowCards;

- (void) hasLostClowCard;
- (void) hasGainedClowCard;

@end

@implementation Character
@synthesize characterName;
@synthesize ownedClowCards;

- (void)hasLostClowCard{

}

- (void)hasGainedClowCard{

}
@end


int main() {
  Character *sakura;
  Character *shaoran;

  // Create and give the properties some values with KVC
  sakura = [[Character alloc] init];
  [sakura setValue:@"Sakura Kinomoto" forKey:@"characterName"];
  [sakura setValue:@20 forKey:@"ownedClowCards"];

  shaoran = [[Character alloc] init];
  [shaoran setValue:@"Li Shaoran" forKey:@"characterName"];
  [shaoran setValue:@21 forKey:@"ownedClowCards"];

  // Done! Now we are going to fetch the values using KVC.
  NSString *mainCharacter = [sakura valueForKey:@"characterName"];
  NSNumber *mainCharCards = [sakura valueForKey:@"ownedClowCards"];

  NSString *rival = [shaoran valueForKey:@"characterName"];
  NSNumber *rivalCards = [shaoran valueForKey:@"ownedClowCards"];

  NSLog(@"%@ has %d Clow Cards", mainCharacter, mainCharCards.intValue);
  NSLog(@"%@ has %d Clow Cards", rival, rivalCards.intValue);

  NSLog(@"%@ has %ld Clow Cards", sakura.characterName, sakura.ownedClowCards);
  NSLog(@"%@ has %ld Clow Cards", shaoran.characterName, shaoran.ownedClowCards);
}
```
 