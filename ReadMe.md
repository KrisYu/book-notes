  iOS - Roadtrip


  books

- [x] iOS编程（第4版）: [Exerice Projects](https://github.com/KrisYu/iOS-Programming-The-Big-Nerd-Ranch-Guide)
- [ ] 函数式 Swift [代码笔记](objccn-functional-swift)
- [ ] Objective-C高级编程 ： iOS与OS X多线程和内存管理
- [x] Effective Objective-C 2.0
- [x] Programming with Objective C : [中文版](https://github.com/L1l1thLY/Programming-with-Objective-C-in-Chinese)
- [ ] Core Data by Tutorials: [Code](https://github.com/KrisYu/Core-Data-by-Tutorials)  [Notes](Core_Data_by_Tutorials)


skills make my life easier:

- gcc run oc file: `gcc main.m -o main -framework Foundation`
- clang run oc files: `clang -fobjc-arc main.m XYZShootingPerson.m XYZPerson.m -o main`
- Xcode快速添加documentation： command + option + /
- Xcode fold/unfold function: command+ shift+ ←\→
- 节约空间：  `~/Library/Developer/CoreSimulator/Devices` 可删
- 快速知道一个git repo的代码行数：  git ls-files | xargs wc -l
- 快速查文件夹代码行数： find . -name '*.*' -type f | xargs wc -l


随手记

- shell文件后缀 .sh, 如果要run它  sh file.sh
- vim 翻页： 整页翻页 ctrl-f ctrl-b
- vim 行数： ：set number




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
- [x] extern vs static: [解答](lcthw/extern_and_static.txt)
- [x] I/O函数: [解答](lcthw/iofunction.txt)





随手记:

- [x] UIEdgeInsects: 插入间隔区域。正值表示间隔值，负值表示超出参照物的距离
- [x] setNeedsDisplay vs setNeedsLayout: [解答](thoughts/setNeedsLayout.md)
- [x] tag: tag可以link with view，有时候可以通过tag来target-action链接
- [x] bounds.width vs bounds.size.width: return一样的东西，但是bounds.width 是 get only
- [x] x? = x! + 1 这种写法是完全安全的，如果左侧被展开了，那么右侧一定就是non-optional
- [x] swift函数签名:
- [x] view hierarchy:
- [x] addSubview vs insertSubview(_aboveSubview:)
- [x] print pointer address for class: `String(describing: Unmanaged.passUnretained(self).toOpaque())`
- [x] willSet 和 didSet 如何能初始化时被调用： [解答](thoughts/willset.md)
- [x] Swift introspection: type(of: application) 也有 isMemberOf

随手记Swift：


读一个OC项目[Wechat](https://github.com/Seanwong933/WeChat)：


- [x] pod file 格式：[解答](Fake_Wechat/podfile.txt)
- [x] 汉字转拼音：[解答](Fake_Wechat/pinyin.txt)
- [x] 画一个矩形的色块： [解答](Fake_Wechat/rectImage.txt)
- [x] dispatch_once实现单例模式： [解答](Fake_Wechat/singleton.txt)
- [x] tab bar highlight展示不同的图片: [解答](Fake_Wechat/TabbarHighlight.text)
- [x] 手写UITableView: [解答](Fake_Wechat/ContactsTableView.txt)
- [x] 不一样的 UITableViewCell设定方式: [解答](Fake_Wechat/ContactsTableViewCell.txt)
- [x] 介绍UISearchController: [解答](Fake_Wechat/介绍UISearchController.md)
- [x] App结构: [解答](Fake_Wechat/structure.txt)


thoughts:

- [x] 属性，实例变量以及synthesize: [解答](thoughts/属性.md)
- [x] Category中添加属性: [解答](thoughts/Category添加属性.md)
- [x] OC中类的扩展extension : [解答](thoughts/类的扩展.md)
- [x] 协议protocol： [解答](thoughts/协议.md)
- [x] 不开Xcode run oc代码 & oc转换为cpp：[解答](thoughts/Terminal_run_oc_file.md)
- [x] ARC内存管理 strong/weak/copy: [解答](thoughts/ARC自动内存管理.md)
- [x] 方法，消息和选择器： [解答](thoughts/方法，消息和选择器.md)
- [x] id: [解答](thoughts/id.md)
- [x] instancetype: [解答](thoughts/instancetype.md)
- [x] blocks: [解答](thoughts/blocks.md)
- [x] KVC & KVO: [解答](thoughts/KVC & KVO.md)
- [x] [KVC & KVO on objio](https://objccn.io/issue-7-3/): [解答](thoughts/KVC & KVO2.md)
- [x] Runtime: [解答](thoughts/Runtime.md)
- [x] 内存泄露检测？



Effective Objective-C:

- [x] 'Calling a method' OR 'sending a message' in Objective C? : [解答](EOC/EOC01.md)
- [x] forward declaring: [解答](EOC/EOC02.md)
- [x] 字面量语法： [解答](EOC/EOC03.md)
- [x] 常型常量: [解答](EOC/EOC04.md)
- [x] 用枚举表示状态、选项、状态码： [解答](EOC/EOC05.md)
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
- [x] 通过委托与数据源协议进行对象间通信: 参照上方protocol部分
- [x] 将类的实现代码分散到便于管理的数个分类之中: [解答](EOC/EOC24.md)
- [x] 总是为第三方类的分类名称加前缀: [解答](EOC/EOC25.md)
- [x] 勿在分类中声明属性: [解答](EOC/EOC26.md)
- [x] 使用‘class-continuation分类’隐藏实现细节: [解答](EOC/EOC27.md)
- [x] 通过协议提供匿名对象: [解答](EOC/EOC28.md)
- [x] 理解引用计数: 上面thoughts部分 -> ARC内存管理 strong/weak/copy [补充](EOC/EOC29.md)
- [x] 以ARC简化引用计数: [解答](EOC/EOC30.md)
- [x] 在dealloc方法中之释放引用并解除监听
- [x] 编写‘异常安全代码’时留意内存管理问题
- [x] 以弱引用避免保留环
- [x] 以‘自动释放池块’降低内存峰值
- [x] 用‘僵尸对象’调试内存管理问题
- [x] 不要使用retainCount
- [x] 理解‘块’这一概念： 参见blocks: [解答](thoughts/blocks.md) [补充](EOC/EOC37.md)
- [x] 为常用的块类型创建typedef: [解答](EOC/EOC38.md)
- [x] 用handler块降低代码分散程度: [解答](EOC/EOC39.md)
- [x] 用块引用其所属对象是不要出现保留环: [解答](EOC/EOC40.md)
- [x] 多用派发队列，少用同步锁
- [x] 多用GCD，少用performSelector系列方法: [解答](EOC/EOC42.md)
- [x] 掌握GCD几操作队列的使用时机: [解答](EOC/EOC43.md)
- [x] 通过Dispatch Group机制，根据系统资源状况来执行任务: [解答](EOC/EOC44.md)
- [x] 使用 dipatch_once 来执行只需运行一次的线程安全代码: 参见实现单例模式： [解答](oc/singleton.md)
- [x] 不要使用diapatch_get_current_queue
- [x] 熟悉系统框架
- [x] 多用块枚举，少用for循环: [解答](EOC/EOC48.md)
- [x] 对自定义其内存管理语义的 collection 使用无缝桥接: [解答](EOC/EOC49.md)
- [x] 构建缓存时选用 NSCache 而非 NSDictionary: [解答](EOC/EOC50.md)
- [x] 精简 initialize 与 load的实现代码
- [x] 别忘了NSTimer会保留其目标对象
