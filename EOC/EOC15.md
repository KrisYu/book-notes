duplicate symbol 的错误来自于命名冲突 naming clash，比如如果两个代码都实现了同样的类名，那么我们就会犯这个错。

如果在runtime载入了重名的类，那么dynamic loader也会报错 duplicate symbol error.


所以OC的代码一般给类加前缀，并且是三位的（因为Apple保留了两位给自己）。

还举了一个例子说明重命名的隐蔽性（不是很明白⊙﹏⊙b汗）


eoc 15：

- 使用有意义的前缀
- 若开发的程序库中用了第三方库，则应为其中的名称加上前缀（所以开发库的人是有多累啊|||