import UIKit

let cities = ["Pairs": 2241, "Madrid": 3165, "Amsterdam": 827, "Berlin": 3562]

let madridPopulation: Int = cities["Madrid"]
// error: value of optional type 'Int?' not unwrapped; did you mean to use '!' or '?'?


let madridPopulation: Int? = cities["Madrid"]

// forced unwrapping
if madridPopulation != nil {
    print("The population of Madrid is \(madridPopulation! * 1000)")
} else {
    print("Unknown city: Madrid")
}

// optional binding
if let madridPopulation = cities["Madrid"] {
    print("The population of Madrid is \(madridPopulation * 1000)")
} else {
    print("Unknown city: Madrid")
}

infix operator ??

func ??<T>(optional: T?, defaultValue: T) -> T {
    if let x = optional {
        return x
    } else {
        return defaultValue
    }
}


// 问题可能出现： defaultValue 是一个耗时的操作

let cache = ["test.swift": 1000]
let defaultValue = 2000
cache["hello.swift"] ?? defaultValue


infix operator ??

func ??<T>(optional: T?, defaultValue:() -> T) -> T {
    if let x = optional {
        return x
    } else {
        return defaultValue()
    }
}


infix operator ??
func ??<T>(optional: T?, defaultValue:@autoclosure () throws -> T) rethrows -> T {
    if let x = optional {
        return x
    } else {
        return try defaultValue()
    }
}

/// Optional Chaining

struct Order{
    let orderNumber: Int
    let person: Person?
}

struct Person{
    let name: String
    let address: Address?
}

struct Address{
    let streetName: String
    let city: String
    let state: String?
}


let order = Order(orderNumber: 42, person: nil)

order.person!.address!.state!
// Fatal error: Unexpectedly found nil while unwrapping an Optional value


if let person = order.person {
    if let address = person.address {
        if let state = address.state {
            print("Got a state: \(state)")
        }
    }
}


if let myState = order.person?.address?.state {
    print("This order will be shipped to \(myState)")
} else {
    print("Unknown person, address, or state")
}


/// 


switch madridPopulation{
case 0? : print("Nobody in Madrid")
case (1..<1000)?: print("Less than a million in Madrid")
case let x?: print("\(x) people in Madrid")
case nil: print("We don't know about Madrid")
}

func populationDescription(for city: String) -> String? {
    guard let population = cities[city] else { return nil }
    return "The population of Madrid is \(population)"
}

populationDescription(for: "Madrid")
// Optional("The population of Madrid is 3165")


func increment(optional: Int?) -> Int? {
    guard let x = optional else { return nil }
    return x + 1
}


let a : Int? = 3
increment(optional: a)
// 4

let a: Int? = nil
increment(optional: a)
// nil

extension Optional {
    func map<U>(_ transform: (Wrapped) -> U ) -> U? {
        guard let x = self else { return nil }
        return transform(x)
    }
}

func increment(optional: Int?) -> Int? {
    return optional.map{$0 + 1}
}


let x: Int? = 3
let y: Int? = nil
let z: Int? = x + y
// error: binary operator '+' cannot be applied to two 'Int?' operands


func add(_ optionalX: Int?, _ optionalY: Int?) -> Int? {
    if let x = optionalX {
        if let y = optionalY {
            return x + y
        }
    }
    return nil
}



func add2(_ optionalX: Int?, _ optionalY: Int?) -> Int?{
    if let x = optionalX, let y = optionalY {
        return x + y
    }
    return nil
}


func add3(_ optionalX: Int?, _ optionalY: Int?) -> Int?{
    guard let x = optionalX, let y = optionalY else { return nil }
    return x + y 
}


let capticals = [
    "France": "Pairs",
    "Spain" : "Madrid",
    "The Netherlands": "Amsterdam",
    "Belgium": "Brussels"
]



func populationOfCaptical(county: String) -> Int? {
    guard let captical = capticals[county], let population = cities[captical] else { return nil }
    return population * 1000
}

/// flatMap 居然是optional
/// 我一直以为flatMap是展平nested array
/// 什么，flatMap存在于几处： 
/// LazySequenceProtocol: https://developer.apple.com/documentation/swift/lazysequenceprotocol/2905213-flatmap
/// https://developer.apple.com/documentation/swift/optional/1540500-flatmap



extension Optional {
    func flatMap<U>(_ transform: (Wrapped) -> U? ) -> U? {
        guard let x = self else { return nil }
        return transform(x)
    }
}


func add4(_ optionalX: Int?, _ optionalY: Int?) -> Int?{
    return optionalX.flatMap{ x in
        optionalY.flatMap{ y in
            return x + y
        }
    }
}

func populationOfCaptical2(county: String) -> Int? {
    return capticals[county].flatMap{ captical in
        cities[captical].flatMap{ population in
            population * 1000
        }
    }
}


func populationOfCaptical3(county: String) -> Int? {
    return capticals[county].flatMap{ captical in
        cities[captical]
        }.flatMap{ population in
            population * 1000
    }
}

