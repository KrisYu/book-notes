```
enum {
   UIViewAutoresizingNone                 = 0,
   UIViewAutoresizingFlexibleLeftMargin   = 1 << 0,
   UIViewAutoresizingFlexibleWidth        = 1 << 1,
   UIViewAutoresizingFlexibleRightMargin  = 1 << 2,
   UIViewAutoresizingFlexibleTopMargin    = 1 << 3,
   UIViewAutoresizingFlexibleHeight       = 1 << 4,
   UIViewAutoresizingFlexibleBottomMargin = 1 << 5
};
typedef NSUInteger UIViewAutoresizing;

```

Apple 本身就很喜欢用enum（在合适的场合），而且这里的enum很有意思，廷尉它用了这种二进制计算，所以当我们用或的时候就可以方便计算。

同时作者建议如果用了 switch enum 最好就不要default了，注意OC的switch还是需要break的，跟Swift不太一样：

> switch case is completed, without requiring an explicit break statement.


EOC之五：用枚举表示状态、选项、状态码

