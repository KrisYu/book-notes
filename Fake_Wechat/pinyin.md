
```
- (NSString*)transformToPinyin
{
  NSMutableString* mutableString = [NSMutableString stringWithString:self];
  CFStringTransform((CFMutableStringRef)mutableString, NULL,
                    kCFStringTransformToLatin, false);
  CFStringTransform((CFMutableStringRef)mutableString, NULL,
                    kCFStringTransformStripDiacritics, false);
  return mutableString;
}
```

note：

- 可以用一个NSString的Category来完成
- 如果数据量很大，建议建dictionary，这样第一次全转，之后就去查字典了


```
//1.先从缓存中获得latin，然后再判断是否存在，再将非字符串转化成拉丁字母  
NSString* latin = [pinyinDic objectForKey:self.fullName];  
if (latin) {  
    self.latinString = latin;  
}  
else {  
    CFStringTransform((__bridge CFMutableStringRef)self.latinString, NULL, kCFStringTransformMandarinLatin, NO);  
    CFStringTransform((__bridge CFMutableStringRef)self.latinString, NULL, kCFStringTransformStripDiacritics, NO);  
    [pinyinDic setObject:self.latinString forKey:self.fullName];  
}  
```

根据：[使用CFStringTransform将汉字转成拼音，非常耗时！](https://blog.csdn.net/hherima/article/details/40187953)