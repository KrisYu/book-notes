其实CoreData 是不是有点像画画？

### 存数据

- 获得上下文环境
 
```
     guard let appDelegate = UIApplication.shared.delegate as? AppDelegate else {
      return
    }
    
    let managedContext = appDelegate.persistentContainer.viewContext
```

- 创建新的托管对象并将其插入托管对象上下文中

```
    let entity = NSEntityDescription.entity(forEntityName: "Person", in: managedContext)!
    
    let person = NSManagedObject(entity: entity, insertInto: managedContext)
```

- 用KVC设定要存储的值

```
    person.setValue(name, forKeyPath: "name")

```


- 存储

```
    
    do {
      try managedContext.save()
      people.append(person)
    } catch let error as NSError {
      print("Could not save. \(error), \(error.userInfo)")
    }
```

### 取数据

- 获得上下文

```
    guard let appDelegate = UIApplication.shared.delegate as? AppDelegate else { return }
    
    let managedContext = appDelegate.persistentContainer.viewContext
```


- 告知取回标准

```
    let fetchRequest = NSFetchRequest<NSManagedObject>(entityName:"Person")
```

- 取回操作

```
    do {
      people = try managedContext.fetch(fetchRequest)
    } catch let error as NSError {
      print("Could not save. \(error), \(error.userInfo)")
    }
```