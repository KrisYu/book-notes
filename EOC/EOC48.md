遍历 collection 有4种方式：

- for
- NSEnumerator 类似java
- for in
- enumerateObjectsUsingBlock

感觉swift此时就很爽了， forEach, filter, map, reduce

然而比如想要实现OC的map用的也就是第四个方法：

```
NSMutableArray *newArray = [NSMutableArray array];
[array enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
     [newArray addObject:[obj name]];
}];
```