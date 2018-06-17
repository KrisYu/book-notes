其实这里的匿名对象 id 是指的遵循协议的对象，遵循协议，我们并不关系它本身的类。


```
@property (nonatomic, weak) id <EOCDelegate> delegate;
```

像这样，这个对象类型是 id <EOCDelegate>， 实际上是哪一个类并不重，我们只需要这个对象实现EOCDelegate。


```
NSFetchedResultsController *controller = /* some controller */;
NSUInteger section = /* section index to query */;
    
NSArray *sections = controller.sections;
id <NSFetchedResultsSectionInfo> sectionInfo = sections[section];
NSUInteger numberOfObjects = sectionInfo.numberOfObjects;
```

像这个sectionInfo 一样，它只是遵循 NSFetchedResultsSectionInfo 协议的一个id.
