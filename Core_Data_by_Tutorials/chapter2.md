Core Data 

@NSManaged 的 property 也是 runtime时期被确定的。

不同于chapter 1， 我们的context是整在 AppDelegate 中，然后通过把它变成 ViewController的一个property 提供的：

```
// AppDelegate.swift
    guard let vc = window?.rootViewController as? ViewController else { return true }
    
    vc.managedContext = persistentContainer.viewContext
```

针对一个类，生成两个文件：

- Bowtie+CoreDataClass.swift
- Bowtie+CoreDataProperties.swift

这两个文件很oc，充满了oc的影子，比如 @objc 不用多说，然后一般不选为Data，Date，而是NSData，NSDate

populate 函数可以理解为 updateUI 函数

比较疑惑的地方还包括：

```    
    let fetch: NSFetchRequest<Bowtie> = Bowtie.fetchRequest()
    fetch.predicate = NSPredicate(format: "searchKey != nil")
```

继续等着看讲解：

```
    let request = NSFetchRequest<Bowtie>(entityName: "Bowtie")
    request.predicate = NSPredicate(format: "%K = %@",
                                    argumentArray: [#keyPath(Bowtie.searchKey), selectedValue])
```                                    
                                    
                                    