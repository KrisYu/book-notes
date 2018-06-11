不用 #define ~ , 用：


static const NSTimeInterval kAnimationDuration = 0.3 ;


const -> 防修改

static -> 本编译单元内


// In the header file

extern NSString *const EOCStringConstant;


// IN the implementation file

NSString *const EOCStringConstant = @"VALUE";



EOC第4条： 多用常型常量，少用#define预处理指令