看例子：

```
// EOCNetworkFetcher.h
#import <Foundation/Foundation.h>

typedef void(^EOCNetworkFetcherCompletionHandler) (NSData *data) ;

@interface EOCNetworkFetcher : NSObject

@property (nonatomic, strong, readonly) NSURL *url;
-(instancetype)initWithURL: (NSURL *)url;
-(void)startWithCompletionHandler: (EOCNetworkFetcherCompletionHandler) completion;

@end

```

然后：

```
//  EOCNetworkFetcher.m
#import "EOCNetworkFetcher.h"

@interface EOCNetworkFetcher()
@property (nonatomic, strong, readwrite) NSURL *url;
@property (nonatomic, copy) EOCNetworkFetcherCompletionHandler completionHandler;
@property (nonatomic, strong) NSData *downloadedData;
@end

@implementation EOCNetworkFetcher

-(instancetype) initWithURL:(NSURL *)url{
    if ((self = [super init])) {
        _url = url;
    }
    return self;
}

-(void)startWithCompletionHandler:(EOCNetworkFetcherCompletionHandler)completion {
    self.completionHandler = completion;
    // Start the request
    // Request sets downloadedData property
    // When request is finished, p_requestCompleted is called
}

-(void) p_requestCompleted{
    if (_completionHandler) {
        _completionHandler(_downloadedData);
    }
}
@end
```


最后在使用它的类中：

```
@implementation EOCClass{
    EOCNetworkFetcher *_networkFetcher;
    NSData *_fetchedData;
}

- (void)downloadData {
    NSURL *url = [[NSURL alloc]initWithString: @"http://www.example.com/foo.dat"];
    _networkFetcher = [[EOCNetworkFetcher alloc] initWithURL: url];
    [_networkFetcher startWithCompletionHandler: ^(NSData *data){
                NSLog(@"Request URL with %@ finished",_networkFetcher.url);
        _fetchedData = data;
    }];
}
@end

```

这里我还能看出来环的，_networkFetcher 是为这个EOCClass的实例所有，然后它因为要补货其实例变量_fetchedData， 也捕获了EOCClass这个实例。 打破方式就是

```
    [_networkFetcher startWithCompletionHandler: ^(NSData *data){
                NSLog(@"Request URL with %@ finished",_networkFetcher.url);
        _fetchedData = data;
        _networkFetcher = nil;
        }
```

另外一种方法就是在这个里面改：

```
-(void) p_requestCompleted{
    if (_completionHandler) {
        _completionHandler(_downloadedData);
    }
    self.completion = nil;
}
```

或者是不是我经常看到weak 和 unowned 的地方。
