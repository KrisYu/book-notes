- NSManagedObjectModel: database schema
- NSPersistentStore ：存储
- NSPersistentStoreCoordinator： object model 和 persistent store的桥梁
- NSManagedObjectContext： 最重要的


全部合起来： NSPersistentStoreContainer

所以我们用了一个 CoreDataStack class，这个class里面公开的部分有 managedContext 和 saveContext 方法。

除此之外我们并没有像第一章和第二章一样需要在AppDelegate中写别的方法。