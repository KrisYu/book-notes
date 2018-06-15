### 关键值编码：它是什么以及为什么需要它？

KVC是一种编码形式，允许您间接访问对象的属性，使用字符串访问它们而不是属性的访问器，或者直接访问变量。

要启用这种机制，您的类必须遵守NSKeyValueCoding非正式协议。 幸运的是，NSObject遵守它，它也有它的方法的默认实现，所以大多数时候你不需要修改任何东西来使用KVC。
我们很快就会编写KVC代码。

### 为什么会有人想这样做？ 这如何应用？

这是一个非常重要的问题。 使用KVC访问属性时，只需使用访问器即可访问属性，这有什么意义？

首先，KVC允许您执行KVO：也就是说，**如果您正在观察变量，则只有在使用KVC进行更改时才会通知其变更。 如果直接使用其setter修改变量，则不会通知其变更。** 这听起来抽象吗？ 如果你还不明白这个段落，别担心。 一旦我们进入KVO部分，您将会了解更多信息。

其次，正如我在本教程开始时所说的，许多Apple的框架将其用于iOS和Mac OS X.例如，Core Data是Apple的最强大的框架之一，它可以使用KVC，更不用说了它在Mac OS X和iOS中均可用。 如果您使用的是NSManagedObject类而不是您自己的子类，则必须使用KVC通过该对象访问核心数据字段。

```
NSManagedObject *character; //Lets assume the core data object has been fetched.
 
//Giving the object some values to save later.
[character setValue:@"Sakura Kinomoto" forKey:@"characterName"];
[character setValue:38 forKey:@"ownedCards"];
 
//Fetching those values using KVC.
 
NSString *sakura = [character valueForKey:@"characterName"];
NSInteger numberOfClowCards = [character valueForKey:@"ownedCards"];
```

如果您使用NSManagedObject的子类，则可以避免在使用核心数据时使用KVC。 无论如何，重要的是要知道发生了什么。

我们来写一些KVC代码。 转到Xcode并创建一个新的Command-Line Tool（请注意我讨厌给我们这样的明确指示“启动Xcode，导航到文件，将出现一个新窗口，转到X部分并选择命令行工具”，因为 对于我的所有教程，我假设你熟悉你的工具，并且你应该知道如何在没有指示的情况下使用它们）。 我将我的项目命名为“CardCaptorChars”。

在我们继续这个例子之前，需要改变一些东西。 首先，将main.cpp重命名为main.m. 然后删除此文件中的所有代码，并只写出程序的基本框架。 不要忘记导入Foundation框架：

```
#import <Foundation/Foundation.h>
 
int main()
{
 
}
```

然后，用一些属性和方法创建一个Objective-C类（可以随便在同一个文件中完成）本教程的重点不在于说明如何分离文件等）。 这是我的：

```
@interface Character : NSObject
{
    NString *characterName;
    NSInteger ownedClowCards;
}
@property (nonatomic, copy) NSString *characterName;
@property NSInteger ownedClowCards;
-(void)hasLostClowCard;
-(void)hasGainedClowCard;
@end
```

如果你跟着我的例子，接下来是实现：

```
@implementation Character
@synthesize characterName;
@synthesize ownedClowCards;
 
-(void)hasLostClowCard
{
 
}
 
-(void)hasGainedClowCard
{
 
}
 
@end

```

方法将在KVO部分填写。
现在我们要创建一些对象并使用KVC设置和获取变量。 所以让我们实现main（）：


```
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

就是这样！使用KVC设置和获取变量确实非常直截了当。这是多一点工作，但在某些情况下是需要的。

### 关键价值观察

**您希望使用KVC的主要原因是在对象属性发生变化时观察它们。 KVO只是允许你这样做。任何对象都可以观察任何“关键路径(key path)”中的任何变量。**


但首先，有关关键路径。

什么是关键路径？名称“关键路径”听起来令人生畏。其实，当我第一次看到这个词时，我感到害怕。关键路径很简单，就是一个属性的“完整路线”。 “self.name”是self的name属性的完整键路径。如果你有一个具有给定小时的时钟的人，其关键路径将是“clock.time.hour”。

Sakura拥有20张Clow卡片，Shaoran拥有21张。知道他们何时失去或获得新的Clow卡片是不是很有趣？至少我们的计划可以告诉我们什么时候发生这种事情。

实现KVO就像为所需的关键路径添加观察者一样简单，并实现一个固定方法，只要观察者注意到观察变量发生变化，就会调用该方法。要将对象注册为观察者，请使用NSKeyCodingProtocol的addObserver：forKeyPath：options：context：方法。每当发生更改时，都会调用observeValueForKeyPath：ofObject：change：context：方法。

所以首先，你需要将这个方法添加到你的类中：


```
-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
 
}
```


这是值改变时被调用的基本方法。您也可以在关键路径上的值即将更改时收到通知，并且可以在发生更改后通知您，分别使用方法willChangeValueForKey和didChangeValueForKey。我们不打算实现这些方法，但它们的使用非常简单。

一旦你这样做，我们将注册Sakura来观察它自己的变化。当Sakura's Clow card发生变化时，您可以自然地要求Shaoran得到通知，反之亦然。在声明字符后添加这个。

```
[sakura addObserver:sakura forKeyPath:@"ownedClowCards" options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld context:nil];

```

我希望你特别注意选项。 NSKeyValueObservingOptionNew和NSKeyValueObservingOptionOld。有了这两个选项，我们指定了更改NSDictionary应包含新值和旧值。在我们的情况下，我们需要知道双方是否知道Clow卡数是增加还是减少。


注意：在程序结束时，请确保您将Sakura作为自己的观察员移除。否则，控制台会打印一个令人讨厌的消息。

```
[sakura removeObserver:sakura forKeyPath:@"ownedClowCards"];
```

我们现在要实现我们的两个空方法：

```
-(void)hasLostClowCard
{
    NSLog(@"%@ has lost a card! Cards now: %ld", characterName, ownedClowCards);
}
 
-(void)hasGainedClowCard
{
    NSLog(@"%@ has earned a card! Cards now: %ld", characterName, ownedClowCards);
}

```

非常简单，但为了示范，让它保持那样。

现在我们将实现observeValueForKeyPath：ofObject：change：context：以这种方式，当角色拥有的卡数少于之前时，hasLostClowCard被调用，并且当角色拥有更多的时候hasCainedClowCard。就像我之前告诉过你的，这些选项定义了变更字典中的内容，所以请确保在需要时使用Apple文档。

实现看起来像这样：

```
-(void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary *)change context:(void *)context
{
    if([keyPath isEqualToString:@"ownedClowCards"])
    {
        NSInteger oldC = [change objectForKey:NSKeyValueChangeOldKey];
        NSInteger newC = [change objectForKey:NSKeyValueChangeNewKey];
        if(oldC < newC)
        {
            [self hasGainedClowCard];
        }else
        {
            [self hasLostClowCard];
        }
    }
}

```

就这样。这很简单：首先我们确保我们正在观察的关键是被改变的关键。如果是这样，我们将旧的和新的值保存在变量中，并且我们比较它们以查看应该发送什么消息。

这真的很强大。即使控制了你的属性的变化也是一个非常强大的功能，我相信你会发现在你自己的项目中使用的好例子。

像往常一样，您可以在我的Pastebin中找到上述项目的源代码。当然，如果您有问题，请随时提问。

感谢谷歌翻译：

文章来自：

[Key-Value Coding, Key-Value Observing, and Cocoa Bindings: A Basic Tutorial.](https://www.andyibanez.com/key-value-coding-key-value-observing-cocoa-bindings-basic-tutorial/)


最终验证代码：

```
#import <Foundation/Foundation.h>

@interface Character: NSObject {
    NSString *characterName;
    NSInteger ownedClowCards;
}

@property (nonatomic, copy) NSString *characterName;
@property NSInteger ownedClowCards;

- (void) hasLostClowCard;
- (void) hasGainedClowCard;
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context;

@end

@implementation Character
@synthesize characterName;
@synthesize ownedClowCards;

- (void)hasLostClowCard{
    NSLog(@"%@ has lost a card! Cards now: %ld", characterName, ownedClowCards);
}

- (void)hasGainedClowCard{
    NSLog(@"%@ has earned a card! Cards now: %ld", characterName, ownedClowCards);
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context{
    if ([keyPath isEqualToString:@"ownedClowCards"]) {
        NSInteger newC = [change objectForKey:NSKeyValueChangeNewKey];
        NSInteger oldC = [change objectForKey:NSKeyValueChangeOldKey];
        
        if (oldC < newC) {
            [self hasGainedClowCard];
        } else if (oldC > newC) {
            [self hasLostClowCard];
        } else {
            NSLog(@"Nothing has changed");
        }
    }
}





@end


int main() {
    Character *sakura;
    Character *shaoran;
    
    // Create and give the properties some values with KVC
    sakura = [[Character alloc] init];
    [sakura setValue:@"Sakura Kinomoto" forKey:@"characterName"];
    [sakura setValue:@20 forKey:@"ownedClowCards"];
    
    [sakura addObserver:sakura forKeyPath:@"ownedClowCards"
                options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld
                context:nil];
    
    
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
    
    sakura.ownedClowCards = 21;
    [sakura setValue:@21 forKey:@"ownedClowCards"];

    [sakura removeObserver:sakura
                forKeyPath:@"ownedClowCards"];
}
```

事实证明，无论是setter 还是用kvc，都会被kvo观察到并打印出来。

