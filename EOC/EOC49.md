无缝桥接（toll-free bridging）并非一个新名词啊，原来OC和C之间就有这样的关系。（想到了Swift和OC）

Foundation 和 CoreFoundation， 类与数据结构就可以相互转换。 NSArray -> CFArray, CFArray就需要配合指针来使用：


```
  NSArray * anNSArray = @[@1, @2, @3, @4, @5];
  CFArrayRef aCFArray = (__bridge CFArrayRef)anNSArray;
  NSLog(@"Size of array = %li", CFArrayGetCount(aCFArray));
  // Size of array = 5
```

- __bridge 无缝桥接，ARC依旧具有对象的所有权
- __bridge_retained, ARC交出对象的所有权，然后需要CFRelease（aCFArray）来释放
- __bridge_transfer, 反向实现


然后感慨应该感谢Foundation，至少Foundation中的collection比CoreFoundation中的简单很多

