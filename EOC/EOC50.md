#### NSCache
 
代码🌰

```
// Network fetcher class
#import <Foundation/Foundation.h>

typedef void(^EOCNetworkFetcherCompletionHandler) (NSData *data) ;

@interface EOCNetworkFetcher : NSObject

@property (nonatomic, strong, readonly) NSURL *url;
-(instancetype)initWithURL: (NSURL *)url;
-(void)startWithCompletionHandler: (EOCNetworkFetcherCompletionHandler) completion;

@end

```

用Cache的class


```

@interface EOCClass : NSObject

@end


#import "EOCClass.h"
#import "EOCNetworkFetcher.h"
@implementation EOCClass {
  NSCache *_cache;
}

-(instancetype) init{
  if ((self = [super init])) {
    _cache = [NSCache new];
    
    //Cache a maximum of 100 URLs
    _cache.countLimit = 100;
    
    /**
     * The size in bytes of data is used as the cost,
     * so this sets a cost limit of 5MB.
     */
    _cache.totalCostLimit = 5 * 1024 * 1024;
    
  }
  return self;
}


- (void) downloadDataForURL: (NSURL*) url {
  NSData *cachedData = [_cache objectForKey:url];
  if (cachedData) {
    // Cache hit
    [self useData: cachedData];
  } else {
    //Cache miss
    EOCNetworkFetcher *fetcher = [[EOCNetworkFetcher alloc] initWithURL:url];
    [fetcher startWithCompletionHandler:^(NSData *data) {
      [_cache setObject:data forKey:url cost:data.length];
      [self useData: cachedData];
    }];
  }
}

@end

```


#### NSPurgeableData

这个类很神奇，居然还有协议叫做 NSDiscardableContent，配合NSCache使用它可以实现自动清除。


```
- (void) downloadDataForURL: (NSURL*) url {
  NSPurgeableData *cachedData = [_cache objectForKey:url];
  if (cachedData) {
    // Stop the data being purged
    [cachedData beginContentAccess];
    
    // Use the cached data
    [self useData: cachedData];
    
    // Mark that the data may be purged again
    [cachedData endContentAccess];
  } else {
    //Cache miss
    EOCNetworkFetcher *fetcher = [[EOCNetworkFetcher alloc] initWithURL:url];
    [fetcher startWithCompletionHandler:^(NSData *data) {
      NSPurgeableData *purgeableData = [NSPurgeableData dataWithData:data];
      [_cache setObject:purgeableData forKey:url cost:purgeableData.length];
      // Don't need to beginContentAccess as it begins
      // with access already marked
      
      // Use the retrieved data
      [self useData: data];
      
      // Mark that the data may be purged now
      [purgeableData endContentAccess];
    }];
  }
}
```
