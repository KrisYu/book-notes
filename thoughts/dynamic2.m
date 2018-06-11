#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface A: NSObject
@property (nonatomic, assign) NSInteger a;
@end

@implementation A
@dynamic a;
int a(id self, SEL _cmd){
  return 1;
}

+ (BOOL)resolveInstanceMethod:(SEL)sel {
  class_addMethod([self class], @selector(a), (IMP)a, "i@:");
  return YES;
}

@end

int main(int argc, char* argv[]){
  A *aObject = [[A alloc] init];
  NSLog(@"%ld", aObject.a);
}
