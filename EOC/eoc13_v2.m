#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface NSString (EOCMyAdditions)
- (NSString *)eoc_myLowercaseString;
@end

@implementation NSString (EOCMyAdditions)
- (NSString *)eoc_myLowercaseString {
  NSString *lowercase = [self eoc_myLowercaseString];
  NSLog(@"%@ => %@", self, lowercase);
  return lowercase;
}
@end

int main(int agrv, char * argv[]){
  
  Method originalMethod = class_getInstanceMethod([NSString class],@selector(lowercaseString));
  Method swappedMethod = class_getInstanceMethod([NSString class],@selector(eoc_myLowercaseString));

  method_exchangeImplementations(originalMethod, swappedMethod);

  NSString *string = @"ThIs iS tHe StRing";
  
  NSString *lowercaseString = [string lowercaseString];
 
  return 0;
}

