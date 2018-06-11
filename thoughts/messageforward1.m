#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface B: NSObject
- (void) b;
@end

@implementation B
- (void) b {
  NSLog(@"b");
}

- (void)doesNotRecognizeSelector:(SEL)aSelector{
  [super doesNotRecognizeSelector: aSelector];
}

@end

@interface A: NSObject
@end

@implementation A

- (NSMethodSignature *)methodSignatureForSelector: (SEL)aSelector{
  NSMethodSignature* signature = [super methodSignatureForSelector: aSelector];
  if (!signature) {
    B *bObject = [[B alloc] init];
    signature = [bObject methodSignatureForSelector: aSelector];
  }
  return signature;
}

- (void)forwardInvocation:(NSInvocation *)anInvocation{
  B *bObject = [[B alloc] init];
  [anInvocation invokeWithTarget: bObject];
}

- (void)doesNotRecognizeSelector:(SEL)aSelector {
    [super doesNotRecognizeSelector:aSelector];
}
@end

int main(int argc, char* argv[]) {
  A *aObject = [[A alloc] init];
  [aObject performSelector:@selector(b)];
}
