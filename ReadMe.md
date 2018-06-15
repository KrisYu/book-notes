  iOS - Roadtrip
  
  
  books

- [x] iOS编程（第4版）: [Exerice Projects](https://github.com/KrisYu/iOS-Programming-The-Big-Nerd-Ranch-Guide)
- [ ] 函数式 Swift [代码笔记](objccn-functional-swift)
- [ ] Objective-C高级编程 ： iOS与OS X多线程和内存管理
- [ ] Programming with Objective C : [中文版](https://github.com/L1l1thLY/Programming-with-Objective-C-in-Chinese)

Xcode skills make my life easier:

- gcc run oc file: `gcc main.m -o main -framework Foundation`
- clang run oc files: `clang -fobjc-arc main.m XYZShootingPerson.m XYZPerson.m -o main`
- Xcode快速添加documentation： command + option + /
- Xcode fold/unfold function: command+ shift+ ←\→




learn c the hard way

- [x] Makefile : [解答](lcthw/Makefile.txt)
- [x] 字符串就是字节数组： [解答](lcthw/字符串就是字节数组.txt)
- [x] 指向‘指向字符的指针’的指针: [解答](lcthw/指向‘指向字符的指针’的指针.txt)
- [x] 指针名词: [解答](lcthw/指针名词.txt)
- [x] 结构体: [解答](lcthw/结构体.txt)
- [x] 堆vs栈: [解答](lcthw/堆vs栈.txt)
- [x] 函数指针: [解答](lcthw/函数指针.txt)
- [x] OOP: [解答](lcthw/OOP.txt)
- [x] debug marco: [解答](lcthw/debug.txt)





随手记:

- [x] UIEdgeInsects: 插入间隔区域。正值表示间隔值，负值表示超出参照物的距离
- [x] setNeedsDisplay vs setNeedsLayout: [解答](thoughts/setNeedsLayout.md)
- [x] tag: tag可以link with view，有时候可以通过tag来target-action链接
- [x] bounds.width vs bounds.size.width: return一样的东西，但是bounds.width 是 get only
- [x] x? = x! + 1 这种写法是完全安全的，如果左侧被展开了，那么右侧一定就是non-optional
- [x] swift函数签名: 
- [x] view hierarchy:
- [x] addSubview vs insertSubview(_:aboveSubview:) ...
- [x] print pointer address for class: `String(describing: Unmanaged.passUnretained(self).toOpaque())`
 


thoughts:

- [x] 属性，实例变量以及synthesize: [解答](thoughts/属性.md)
- [x] Category中添加属性: [解答](thoughts/Category添加属性.md)
- [x] OC中类的扩展extension : [解答](thoughts/类的扩展.md)
- [x] 协议protocol： [解答](thoughts/协议.md)
- [x] 不开Xcode run oc代码 & oc转换为cpp：[解答](thoughts/通过Terminal 来run oc file.md)
- [x] ARC内存管理 strong/weak/copy: [解答](thoughts/ARC自动内存管理.md)
- [x] 方法，消息和选择器： [解答](thoughts/方法，消息和选择器.md)
- [x] id: [解答](thoughts/id.md)
- [x] instancetype: [解答](thoughts/instancetype.md)
- [x] blocks: [解答](thoughts/blocks.md)
- [x] KVC & KVO: [解答](thoughts/KVC & KVO.md)
- [x] [KVC & KVO on objio](https://objccn.io/issue-7-3/): [解答](thoughts/KVC & KVO2.md)
- [x] Runtime: [解答](thoughts/Runtime.md)



Effective Objective-C:

- [x] 'Calling a method' OR 'sending a message' in Objective C? : [解答](EOC/EOC1.md)
- [x] forward declaring: [解答](EOC/EOC2.md)
- [x] 字面量语法： [解答](EOC/EOC3.md)
- [x] 常型常量: [解答](EOC/EOC4.md)
- [x] 用枚举表示状态、选项、状态码： [解答](EOC/EOC5.md)
- [x] 理解“属性”这一概念 ： 参见上面的thoughts部分-> 属性以及ARC
- [x] 在对象内部尽量直接访问实例变量: 直接访问实例变量不会触发 KVO
- [x] 理解‘对象等同性’这一概念： 是指向同一对象 or 属性一样
- [x] 以‘类族模式’隐藏实现细节： 定义一个基类，然后继承实现
- [x] 在既有类中使用关联对象存放自定义数据：参照上面的thoughts部分 -> Category中添加属性用到了这个，但是谨慎使用
- [x] 理解objc-msgSend的作用： [解答](EOC/EOC11.md)
- [x] 理解消息转发机制： [解答](thoughts/消息转发.md)
- [x] 用“方法调配技术“调试”黑和方法“： [解答](thoughts/EOC13.md)
- [x] 理解‘类对象’的用意： 参见上面的Runtime部分
- [x] 用前缀避免命名空间冲突：[解答](EOC/EOC15.md)
- [x] 提供‘全能初始化方法’：[解答](EOC/EOC16.md)
- [x] 实现description方法：覆写description/debugDescription方法，方便debug
- [x] 尽量使用不可变对象： 声明 nonatomic, readonly, copy/assign
- [x] 使用清晰而协调的命名方式
- [x] 为私有方法名添加前缀：加上比如这样的前缀：p_
- [x] 理解Objective-C的错误模型： [解答](EOC/EOC21.md)
- [x] 理解NSCopying协议： [解答](EOC/EOC22.md)
- [x] 通过委托与数据源协议进行对象间通信
- [ ] 将类的实现代码分散到便于管理的数个分类之中
- [ ] 总是为第三方类的分类名称加前缀
- [ ] 勿在分类中声明属性
- [ ] 使用‘class-continuation分类’隐藏实现细节
- [ ] 通过协议提供匿名对象
- [x] 理解引用计数: 上面thoughts部分 -> ARC内存管理 strong/weak/copy [补充](EOC/EOC29.md)