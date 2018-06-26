## 简单工厂模式


### OC

简单工厂模式体现继承和松耦合

OC的实现是定义协议，协议需要有两个变量 numberA 和 numberB，还有一个计算结果数。然后每个运算继承自协议，实现协议需要的方法，用了

```
typedef NS_ENUM(NSInteger, CalculateType){
    calcuteTypeAdd = 0,
    calcuteTypeMinus,
    calcuteTypdeMultipy,
    calcuteTypeDivide
};
```

来定义运算符号，然后到工厂方法中去 switch实现运算的效果。

### Swift

Swift 的实现异常优雅，同样用了协议，但是用了tuple来设定运算数，用了optional value来表示运算结果（避免除0等错误），同样用了 enum 和 switch 来实现运算。并且因为Swift的特性用了struct来实现工厂方法。

