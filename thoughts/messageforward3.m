#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface B: NSObject
+ (void) b;
@end

@implementation B
+ (void) b {
  NSLog(@"b");
}

@end

@interface A: NSObject
@end

@implementation A

+ (id)forwardingTargetForSelector: (SEL)aSelector{
  if (aSelector == @selector(b)) {
    return [B class];
  }
  return [super forwardingTargetForSelector: aSelector];
}

@end

int main(int argc, char* argv[]) {
  [[A class] performSelector:@selector(b)];
}
