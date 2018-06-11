//
//  main.m
//  oc_runtime
//
//  Created by Xue Yu on 6/5/18.
//  Copyright © 2018 XueYu. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <objc/runtime.h>

@interface A: NSObject

@property (nonatomic, assign) NSInteger a;

- (void) b;
+ (void) c;

@end

@implementation A

- (void) b {
    NSLog(@"b");
    NSLog(@"%s", @selector(b));

}

+ (void) c {
    NSLog(@"c");
}
@end


int main(int argc, char * argv[]) {
    A *aObjcet = [[A alloc] init];
    
    [aObjcet b];
    
    [A c];
}
