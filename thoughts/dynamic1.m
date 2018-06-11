#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface A : NSObject
@property (nonatomic, assign) NSInteger a;
@end

@implementation A
@dynamic a;
@end

int main(int argc, char * argv[]) {
    A *aObject = [[A alloc] init];
    NSLog(@"%ld", aObject.a);   // 崩于此行
}

