看例子：



```
@protocol EOCNetworkFetcherDelegate <NSObject>
- (void) networkFetcher: (EOCNetworkFetcher *) networkFetcher  didFinishWithData:(NSData *)data;
@end

@interface EOCNetworkFetcher: NSObject
@property (nonatomic, weak) id <EOCNetworkFetcherDelegate> delegate;
- (id) initWithURL: (NSURL *)url;
- (void) start;
@end
```


调用的时候，另一个类会这样：

```
- (void)fetchFooData {
    NSURL *url = [[NSURL alloc]initWithString: @"http://www.example.com/foo.dat"];
    EOCNetworkFetcher *fetcher = [[EOCNetworkFetcher alloc] initWithURL: url];
    fetcher.delegate = self;
    [fetcher start];
}

//...

- (void) networkFetcher: (EOCNetworkFetcher *) networkFetcher  didFinishWithData:(NSData *)data{
    _fetchedFooData = data;
}
```


不过更推荐用块来写：

```
typedef void(^EOCNetworkFetcherCompletionHandler) (NSData *data) ;


@interface EOCNetworkFetcher: NSObject
- (id) initWithURL: (NSURL *)url;
- (void)startWithCompletionHandler: (EOCNetworkFetcherCompletionHandler)handler;
@end

// 调用
- (void)fetchFooData {
    NSURL *url = [[NSURL alloc]initWithString: @"http://www.example.com/foo.dat"];
    EOCNetworkFetcher *fetcher = [[EOCNetworkFetcher alloc] initWithURL: url];
    [fetcher startWithCompletionHandler: ^(NSData *data){
        _fetchedFooData = data;
    }];
}
```



实际上URLSession的API 比如： `func downloadTask(with request: URLRequest, 
completionHandler: @escaping (URL?, URLResponse?, Error?) -> Void) -> URLSessionDownloadTask` 就跟这个思路是类似的


同时使用handler我们还可以决定比如把handler放在哪个queue上。