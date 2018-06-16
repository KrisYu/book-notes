### 通过Terminal 来run oc file


compile： `gcc main.m -o main -framework Foundation`

run: `./main`


几个文件一起来： 

compile: `clang -fobjc-arc main.m XYZShootingPerson.m XYZPerson.m -o main`

run: `./main`



### OC代码转成cpp

首先我们去文件夹：

`/Applications/Xcode.app/Contents/Developer/Platforms/iPhoneSimulator.platform/Developer/SDKs` 中查看当前 Xcode支持的 iOS SDK

或者可以用命令行： `xcodebuild -sdk -version`

能看到：

```
iPhoneOS11.2.sdk - iOS 11.2 (iphoneos11.2)
SDKVersion: 11.2
Path: /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform/Developer/SDKs/iPhoneOS11.2.sdk
PlatformVersion: 11.2
PlatformPath: /Applications/Xcode.app/Contents/Developer/Platforms/iPhoneOS.platform
BuildID: A2F004BA-C5E0-11E7-8D31-58780B8BCBF5
ProductBuildVersion: 15C107
ProductCopyright: 1983-2017 Apple Inc.
ProductName: iPhone OS
ProductVersion: 11.2
```

然后用`xcrun -sdk iphonesimulator11.2 clang -rewrite-objc main.m` 可以将文件转成编译后的伪代码，即运行时执行的代码的伪代码， 运行之后可以看到[main.m](main.m)是 [main.cpp](main.cpp)，很有意思

> clang -rewrite-objc的作用是把oc代码转写成c/c++代码，我们常用它来窥探OC的一些秘密。 


参考文章： [runtime进行曲，objc_msgSend的前世今生（一)](https://www.jianshu.com/p/c0157110caa5)