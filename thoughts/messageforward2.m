#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface B: NSObject
+ (void) b;
@end

@implementation B
+ (void) b {
  NSLog(@"b");
}

- (void)doesNotRecognizeSelector:(SEL)aSelector{
  [super doesNotRecognizeSelector: aSelector];
}

@end

@interface A: NSObject
@end

@implementation A

+ (NSMethodSignature *)methodSignatureForSelector: (SEL)aSelector{
  NSMethodSignature* signature = [super methodSignatureForSelector: aSelector];
  if (!signature) {
    Class bMeta = objc_getMetaClass(class_getName([B class])); 
    signature = [[bMeta class] instanceMethodSignatureForSelector:aSelector];
  }
  return signature;
}

+ (void)forwardInvocation:(NSInvocation *)anInvocation{
  [anInvocation invokeWithTarget: [B class]];
}

- (void)doesNotRecognizeSelector:(SEL)aSelector {
    [super doesNotRecognizeSelector:aSelector];
}
@end

int main(int argc, char* argv[]) {
  [[A class] performSelector:@selector(b)];
}

