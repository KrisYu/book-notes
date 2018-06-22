5 different ways of fetch

```
// 1 
let fetchRequest1 = NSFetchRequest<Venue>()
let entity = NSEntityDescription.entity(forEntityName: "Venue", in: managedContext)!
fetchRequest1.entity = entity
  
// 2 一种简单的写法
let fetchRequest2 = NSFetchRequest<Venue>(entityName: "Venue")

// 3 这是从Venue+CoreDataProperties.swift中调用的方法
let fetchRequest3: NSFetchRequest<Venue> = Venue.fetchRequest()

// 4 需要configure venueFR
let fetchRequest4 = managedObjectModel.fetchRequestTemplate(forName: "venueFR")

// 5
let fetchRequest5 = managedObjectModel.fetchRequestTemplate(withName: "venueFR",
                                                          substitutionVariables:["NAME" : "Vivi Bubble Tea"])
 ```