//: Playground - noun: a place where people can play

import UIKit

/// OOP

typealias Distance = Double

struct Position {
    var x: Double
    var y: Double
}


extension Position{
    
    func minus(_ p: Position) -> Position {
        return Position(x: x - p.x, y: y - p.y)
    }
    
    var length: Double {
        return sqrt(x * x + y * y)
    }
}


struct Ship {
    var position: Position
    var firingRange: Distance
    var unsafeRange: Distance
}

extension Ship {    
    func canSafelyEngage2(ship target: Ship, friendly: Ship) -> Bool {
        let targetDistance = target.position.minus(position).length
        let friendlyDistance = friendly.position.minus(position).length
        
        return targetDistance <= firingRange && targetDistance > unsafeRange && (friendlyDistance > unsafeRange)
    }
}

/// functional Swift
/// Region : a function type, takes in Position, return Bool

typealias Region = (Position) -> Bool

/// return a closure
/// closure structure: Parameter in returnType

func circle(radius: Distance) -> Region{
    return { point in point.length <= radius }
}

///  shifed circle

func circle2(radius: Distance, center: Position) -> Region {
    return { point in point.minus(center).length <= radius}
}

/// region is function name
/// region is a function, we can use circle, rectangle, square, etc...

func shift(_ region: @escaping Region, by offset: Position) -> Region {
    return { point in region(point.minus(offset)) }
    
}

/// shifted is a function 

let shifted = shift(circle(radius: 10), by: Position(x: 5, y: 5))

/// true
print(shifted(Position(x: 5,y : 5)))

/// false
print(shifted(Position(x: 30, y: 3)))


func invert(_ region: @escaping Region) -> Region {
    return { point in !region(point) }
}

/// usage
let outsideCircle = invert(shifted)

/// true
outsideCircle(Position(x: 30, y: 3))


func intersect(_ region: @escaping Region, with other: @escaping Region) -> Region{
    return { point in region(point) && other(point) }
}

func union(_ region: @escaping Region, with other: @escaping Region) -> Region {
    return { point in region(point) || other(point) }
}

func subtract(_ region: @escaping Region, from original: @escaping Region) -> Region {
    return intersect(original, with: invert(original))
}


/// Read the picture and everything make sense
extension Ship {
    
    func canSafelyEngage(ship target: Ship, friendly: Ship) -> Bool {
        let rangeRegion = subtract(circle(radius: unsafeRange), from: circle(radius: firingRange))
        let firingRegion = shift(rangeRegion, by: position)
        let friendlyRegion = shift(circle(radius: unsafeRange), by: friendly.position)
        let resultRegion = subtract(friendlyRegion, from: firingRegion)
        return resultRegion(target.position)
    }
}
