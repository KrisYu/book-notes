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

+ (BOOL)respondsToSelector:(SEL)aSelector{
  if ( [super respondsToSelector:aSelector] )
     return YES;
  else {
      if ([[B class] respondsToSelector:@selector(b)])
      return YES;
  }
  return NO;
}

@end

int main(int argc, char* argv[]) {
  NSLog(@"%i", [[A class] respondsToSelector:@selector(b)]);
}

