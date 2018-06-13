#### 全能初始化方法

全能初始化方法其实是designated initializer 指定初始化方法，这条建议其实就是选一个方法作为designated initializer，其他的都调用它。


比如rectangle的例子：


```
#import <Foundation/Foundation.h>

@interface EOCRectangle: NSObject
@property (nonatomic, assign, readonly) float width;
@property (nonatomic, assign, readonly) float height;
- (instancetype) initWithWidth: (float)width andHeight:(float)height;
@end;

@implementation EOCRectangle

- (instancetype) initWithWidth: (float)width andHeight:(float)height {
    if ((self = [super init])) {
        _width = width;
        _height = height;
    }
    return self;
}

// USing default values
- (instancetype)init {
    return [self initWithWidth: 5.0f andHeight: 10.0f];
}

// Throwing an exception
- (instancetype)init {
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"Must use initWithWidth: andHeight: instead"
                                 userInfo:nil];
}

@end

```

还有一点值得注意的是虽然width和height都是readonly和assign，然后我们在deisgnated initializer 中直接调用它。

我们的deisgnated initializer 是 initWithWidth: andHeight:， 然后我们尽量用别的来调用它。

但是因为它是继承于 NSObject， 所以有免费赠送的 init method，我们不想让外部用户调用它，所以 throw exception ，

比如像这样调用：

```
EOCRectangle *r2 = [[EOCRectangle alloc] init];
```

我们就会得到报错：*** Terminating app due to uncaught exception 'NSInternalInconsistencyException', reason: 'Must use initWithWidth: andHeight: instead'


throw exception 可待考量，因为 exception 一般比较严重。


如果我们从长方形中集成一个正方形：

```
#import "EOCRectangle"

@interface EOCSquare: EOCRectangle
-(instancetype) initWithDimension: (float)dimension;
@end

@implementation EOCSquare

-(instancetype) initWithDimension: (float)dimension {
  return [super initWithWidth:dimension andHeight: dimension]
}

@end

```

除此之外，我们还应该考虑维系全能初始化方法的调用链。

```
- (instancetype) initWithWidth: (float)width andHeight:(float)height {
  float dimension = MAX(width, height);
  return [self initWithDimension: dimension];
}
```

当然我们也可以像上面一样给这个方法抛异常。


#### NSCoder

> The NSCoder class is used to archive/unarchive (marshal/unmarshal, serialize/deserialize) of objects.

> This is a method to write objects on streams (like files, sockets) and being able to retrieve them later or in a different place.


```
- (instancetype) initWithCoder: (NSCoder *)aDecoder {
    if ((self = [super init])) {
        _width = [aDecoder decodeFloatForKey:@"width"];
        _height = [aDecoder decodeFloatForKey:@"height"];
    }
    
    return self;
}
```

这个方法 initWithCoder 倒是被提起，在写VC的时候提醒一定要写这个，但是一般都是在里卖弄写的fatorError。

查了一下，是loadNibNamed:owner:方法会call initWithCoder，所以才基本没用到，甚至这个方法我们也要保持它的调用链。
