#import <Foundation/Foundation.h>
#import <objc/runtime.h>

int main(int agrv, char * argv[]){
  
  Method originalMethod = class_getInstanceMethod([NSString class],@selector(lowercaseString));
  Method swappedMethod = class_getInstanceMethod([NSString class],@selector(uppercaseString));

  method_exchangeImplementations(originalMethod, swappedMethod);

  NSString *string = @"ThIs iS tHe StRing";
  
  NSString *lowercaseString = [string lowercaseString];
  NSLog(@"lowercaseString = %@", lowercaseString);
 
  NSString *uppercaseString = [string uppercaseString];
  NSLog(@"uppercaseString = %@", uppercaseString);

  return 0;
}
