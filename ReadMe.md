  iOS - Roadtrip


  books

- [x] iOS编程（第4版）: [Exerice Projects](https://github.com/KrisYu/iOS-Programming-The-Big-Nerd-Ranch-Guide)
- [ ] 函数式 Swift [代码笔记](objccn-functional-swift)

- [x] Programming with Objective C : [中文版](https://github.com/L1l1thLY/Programming-with-Objective-C-in-Chinese)
- [ ] Core Data by Tutorials: [Code](https://github.com/KrisYu/Core-Data-by-Tutorials)  [Notes](Core_Data_by_Tutorials)


- [x] Objective-C高级编程 ： iOS与OS X多线程和内存管理
- [x] Effective Objective-C 2.0 : [笔记](EOCNotes.md)
- [ ] 大话设计模式: [笔记](Design_Pattern_notes.md)  [Design-Pattern-For-iOS](https://github.com/huang303513/Design-Pattern-For-iOS) [Swift-X-Design-Patterns](https://github.com/kingcos/Swift-X-Design-Patterns)

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
- [x] C语言中函数名加 __ 前缀一般是留给系统函数用的

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
- [x] 朋友圈: [解答](Fake_Wechat/pyq.txt)


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
