[Is it possible to allow didSet to be called during initialization in Swift?](https://stackoverflow.com/questions/25230780/is-it-possible-to-allow-didset-to-be-called-during-initialization-in-swift)


> willSet and didSet observers are not called when a property is first initialized. They are only called when the property’s value is set outside of an initialization context.


```
class SomeClass {
    var someProperty: AnyObject! {
        didSet {
            //do some Stuff
        }
    }

    init(someProperty: AnyObject) {
        setSomeProperty(someProperty)
    }

    func setSomeProperty(newValue:AnyObject) {
        self.someProperty = newValue
    }
}
```