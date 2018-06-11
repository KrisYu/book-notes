#import <Foundation/Foundation.h>

int main(){
  id array = [[NSMutableArray alloc] init];
  
  void (^blk)(void) = ^{ 
    array = [[NSMutableArray alloc] init];
  };

  blk();

  return 0;
}
