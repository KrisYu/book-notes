//: Playground - noun: a place where people can play

import CoreImage
import UIKit

typealias Filter = (CIImage) -> CIImage

func blur(radius: Double) -> Filter {
    return {image in
        let parameters: [String: Any] = [
            kCIInputRadiusKey: radius,
            kCIInputImageKey: image
        ]
        guard let filter = CIFilter(name: "CIGaussianBlur", withInputParameters: parameters)
            else { fatalError() }
        guard let outputImage = filter.outputImage
            else { fatalError() }
        return outputImage
    }
}


func generate(color: UIColor) -> Filter{
    return { image in
        let parameters = [kCIInputColorKey: CIColor(cgColor: color.cgColor)]
        guard let filter = CIFilter(name: "CIConstantColorGenerator",
                                    withInputParameters: parameters)
            else { fatalError() }
        guard let outputImage = filter.outputImage
            else { fatalError() }
        return outputImage.cropped(to: image.extent)
    }
}


func compositeSourceOver(overlay: CIImage) -> Filter {
    return { image in
        let parameters =
            [kCIInputBackgroundImageKey: image,
             kCIInputImageKey: overlay
        ]
        guard let filter = CIFilter(name: "CISourceOverCompositing",
                                    withInputParameters: parameters)
            else { fatalError() }
        guard let outputImage = filter.outputImage
            else { fatalError() }
        return outputImage.cropped(to: image.extent)
    }
}

func overlay(color: UIColor) -> Filter {
    return { image in
        let overlay = generate(color: color)(image).cropped(to: image.extent)
        return compositeSourceOver(overlay: overlay)(image)
    }
}

import PlaygroundSupport

let url = Bundle.main.url(forResource: "screen", withExtension: "png")!
let image = CIImage(contentsOf: url)!

print(image)


let radius = 5.0
let color = UIColor.red.withAlphaComponent(0.2)

// since blur(radius: ) returned a function, takes in ciimage, return ciimage
let blurredImage = blur(radius: 5.0)(image)

let overlaidImage = overlay(color: color)(blurredImage)

// write in one line
let result = overlay(color: color)(blur(radius: radius)(image))

// chapter 1 method, takes two functions as argument, returns function
func compose(filter filter1: @escaping Filter, with filter2: @escaping Filter) -> Filter{
    return { image in filter2(filter1(image))}
}

let blurAndOverlay = compose(filter: blur(radius: radius), with: overlay(color: color))
let result1 = blurAndOverlay(image)

// we create this operator to simplify 
infix operator >>>

func >>>(filter1: @escaping Filter, filter2: @escaping Filter) -> Filter{
    return { image in filter2(filter1(image))}
}

let blurAndOverlay2 = blur(radius: radius)>>>overlay(color: color)
let result2 = blurAndOverlay2(image)


/// Curying : will go back to this topic

func add1(_ x: Int, _ y: Int) -> Int{
    return x + y
}

// takes x, return a closure, then takes y
func add2(_ x: Int) -> ((Int) -> Int){
    return { y in x + y }
}

// right-associative arrow
func add3(_ x: Int) -> (Int) -> Int{
    return { y in x + y}
}

// different way to call it
add1(1,2)
add2(1)(2)

