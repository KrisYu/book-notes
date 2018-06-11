#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface A: NSObject
@end

@implementation A
void b(id self, SEL _cmd){
  NSLog(@"b");
}

+ (BOOL)resolveClassMethod:(SEL)sel {
  class_addMethod([self class], @selector(b), (IMP)b, "v@:");
  return YES;
}

@end

int main(int argc, char* argv[]){
  [[A class] performSelector: @selector(b)];
}
