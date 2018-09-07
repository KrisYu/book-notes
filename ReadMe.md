  iOS - Roadtrip


### iOS related books

- [x] iOS编程（第4版）: [Exerice Projects](https://github.com/KrisYu/iOS-Programming-The-Big-Nerd-Ranch-Guide)
- [x] Objective-C高级编程 ： iOS与OS X多线程和内存管理
- [x] Effective Objective-C 2.0 : [笔记](EOC/EOCNotes.md)
- [ ] 函数式 Swift [代码笔记](objccn-functional-swift)
- [ ] Core Data by Tutorials: [Code](https://github.com/KrisYu/Core-Data-by-Tutorials)  [Notes](Core_Data_by_Tutorials)
- [ ] 各类文档：http://idup.club/library

### 设计模式

- [ ] 大话设计模式: [笔记](Design_Pattern/Design_Pattern_notes.md)  [Design-Pattern-For-iOS](https://github.com/huang303513/Design-Pattern-For-iOS) [Swift-X-Design-Patterns](https://github.com/kingcos/Swift-X-Design-Patterns)

### 方法论

- [x] 程序员修炼之道 The pragmatic Programmer: [笔记](The_pragmatic_programmer/The_pragmatic_programmer.md)

### 数据结构与算法

- [x] 大话数据结构 : [笔记](data_structure/data_structre.md)
- [ ] 数据结构&算法补充 : [笔记](data_structure/data_structre_supply.md)

### C相关

- [x] Head First C : [笔记](Head_First_C/head_first_c_notes.txt)
	- [x] [线程](Head_First_C/线程.md)
- [ ] 笨办法学C语言 : [笔记](lcthw/lcthw.md)

### OS

- [x] semaphore: [semaphore](OS/semaphore.txt) 


### ebooks resources

- [x] [Programming with Objective C](https://github.com/L1l1thLY/Programming-with-Objective-C-in-Chinese)
- [x] [跟我一起写Makefile (PDF重制版)](https://github.com/seisman/how-to-write-makefile)


### other could easily googled books

- [x] C 语言常见问题集
- [x] Little Book of Semaphores
- [x] Think-OS 


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
- [x] 打印结构体: NSStringFromCGSize...
- [x] 打印函数:   NSLog(@"%@", NSStringFromSelector(_cmd));


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
- [x] UIScrollView: [解答](thoughts/UIScrollView.md)

