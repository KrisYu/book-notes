## 介绍UISearchController

如果你看看UISearchController文档，你会发现它很懒惰。 它根本没有做任何搜索工作。 这个类只是提供了一个用户期望从他们的iOS应用程序中获得的标准接口。

UISearchController与委托协议进行通信，让您的应用程序的其余部分知道用户正在做什么。 你必须为自己的字符串匹配编写所有的实际功能。

尽管起初看起来有点吓人，但编写自定义搜索函数可以让您严格控制结果在您的应用中的返回结果。 您的用户会喜欢智能且快速的搜索。

如果您曾经在过去搜索过iOS视图视图，那么您可能熟悉UISearchDisplayController 。 自从iOS 8开始，这个类已经被弃用，以支持UISearchController ，这简化了整个搜索过程。
不幸的是，在撰写本文时，Interface Builder不支持UISearchController ，因此您必须以编程方式创建UI。

```
    let searchController = UISearchController(searchResultsController: nil)
```

通过使用searchResultsController的nil值初始化UISearchController ，可以告诉搜索控制器您要使用您搜索的相同视图来显示结果。 如果你在这里指定了一个不同的视图控制器，它将被用来显示结果。

要允许MasterViewController响应搜索栏，它必须实现UISearchResultsUpdating 。 该协议定义了基于用户输入到搜索栏中的信息更新搜索结果的方法。

仍然在MasterViewController.swift中 ，在主MasterViewController类之外添加以下类扩展：

```
extension MasterViewController : UISearchResultsUpdating {
  // MARK: - UISearchResultsUpdating Delegate
  func updateSearchResults(for searchController: UISearchController) {
    // TODO
  }
}
```



接下来，您需要为您的searchController设置一些参数。 仍然在MasterViewController.swift中 ，在调用super.viewDidLoad()之后，将以下内容添加到viewDidLoad() super.viewDidLoad() ：

```
//Setup the Search Controller
searchController.searchResultsUpdater = self
searchController.obscuresBackgroundDuringPresentation = false
searchController.searchBar.placeholder = "Search Candies"
navigationItem.searchController = searchController
definesPresentationContext = true
    
```

以下是您刚刚添加的内容的简要说明：

- searchResultsUpdater 是 UISearchController 的一个属性，它实现了新的 UISearchResultsUpdating 协议。这个协议允许你自己的类接收 UISearchBar 的文本改变通知。
 
- 默认情况下， UISearchController将遮蔽它所呈现的视图。 如果您正在为searchResultsController使用另一个视图控制器，这非常有用。 在这种情况下，您已设置当前视图以显示结果，因此您不希望模糊您的视图。
- 将占位符设置为特定于此应用的内容
- iOS 11的新增功能是将searchBar添加到NavigationItem 。 这是必要的，因为Interface Builder与UISearchController不兼容。
- 最后，通过在您的视图控制器definesPresentationContext设置为true ，确保在UISearchController处于活动状态时用户导航到另一个视图控制器时，搜索栏不会保留在屏幕上。


### UISearchResultsUpdating 和过滤

创建好 search controller 之后，你必须写一些代码让它能够使用。首先，在 MasterViewController 顶部添加属性：

```
  var filteredCandies = [Candy]()

```

然后，在 MasterViewController 主类中添加助手方法：


```
  
  // MARK: - Private instance methods
  
  func searchBarIsEmpty() -> Bool {
    // Returns true if the text is empty or nil
    return searchController.searchBar.text?.isEmpty ?? true
  }
  func filterContentForSearchText(_ searchText: String, scope: String = "All") {
    filteredCandies = candies.filter({ (candy: Candy) -> Bool in
      return candy.name.lowercased().contains(searchText.lowercased())
    })
    tableView.reloadData()
  }
```

searchBarIsEmpty()是不言自明的。 filterContentForSearchText(_:scope:)基于filterContentForSearchText(_:scope:)过滤candies数组，并将结果放入刚才添加的filteredCandies数组中。 现在不要担心scope参数; 你会在本教程后面的章节中使用它。
filter()需要关闭类型(candy: Candy) -> Bool 。 然后它遍历数组的所有元素，并为每个元素调用闭包，传入当前元素。

您可以使用它来确定糖果是否应成为呈现给用户的搜索结果的一部分。 为此，如果当前的糖果要包含在过滤数组中，则需要返回true否则返回false 。

为了确定这一点，你使用contains(_:)来查看糖果的名称是否包含searchText 。 但在进行比较之前，可以使用lowercased()方法将这两个字符串转换为小写lowercased() 。

注意：大多数情况下，用户在进行搜索时不会打扰字母的大小写，只需比较小写字母与小写字母的名称即可轻松返回大小写不敏感比赛。 现在，你可以输入“巧克力”或“巧克力”，然后返回一个匹配的糖果。 这有多好？ ：]

还记得UISearchResultsUpdating吗？ 你在updateSearchResults(for:)留下了一个TODO updateSearchResults(for:) 。 那么，现在你已经写了一个方法，当我们想更新搜索结果时应该调用它。 瞧！

通过调用filterContentForSearchText(_:scope:)替换updateSearchResults(for:)的TODO：

```
filterContentForSearchText(searchController.searchBar.text!)
```

现在，当用户在 search bar 中删除或者输入每个字符时，UISearchController 都会通过回调 updateSearchResults(for:) 方法来通知 MasterViewController 类，同时会调用 filterContentForSearchText(_:scope:)。

Build & run，你会看到在b表格释放多出了一个 search bar。



但是，当你输入某些搜索关键字时，仍然没有获得搜索结果。为什么？因为你还没有添加代码，让 table view 知道什么时候使用这些搜索结果。

#### 刷新 Table View

回到 MasterViewController.swift，添加一个方法，判断当前是不是正在查找：

```
func isFiltering() -> Bool {
  return searchController.isActive && !searchBarIsEmpty()
}
```

然后，修改 tableView(_:numberOfRowsInSection:) 方法:

```
func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
  if isFiltering() {
    return filteredCandies.count
  }

  return candies.count
}
```

修改的地方不多，只是简单地检查用户是不是正在进行查找，并根据情况使用 filteredCandies 或者 candies 数组作为表格数据源。

然后，修改 tableView(_:cellForRowAt:) 方法为:

```
func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
  let cell = tableView.dequeueReusableCell(withIdentifier: "Cell", for: indexPath)
  let candy: Candy
  if isFiltering() {
    candy = filteredCandies[indexPath.row]
  } else {
    candy = candies[indexPath.row]
  }
  cell.textLabel!.text = candy.name
  cell.detailTextLabel!.text = candy.category
  return cell
}
```

两个方法都会调用 isFiltering()，这个方法会判断 searchController 的 active 属性来决定要显示哪个数组。

当用户点击 search bar 的搜索栏时，active 属性会被设置为 true。如果 search controller 的 active 属性为 true，同时用户输入的内容不为空，将使用 filteredCandies 数组中的数据。否则，使用完整的糖果数据。

再说一遍，search controller 会自动处理结果 Table view 的显示隐藏，因此你只需要根据 controller 的状态以及用户是否搜索到结果来提供正确的数据（过滤的数组或者完整的数组）就可以了。

Build & run。你已经拥有一个能够过滤表格行的 search bar 了。

用一下这个 app，看看怎么才能搜到各种糖果。还有几个地方有问题。当你从搜索结果中选中一行，你会看到详情页显示的是别的糖果！让我们来解决它。



文章来自：[UISearchController 教程-开始](https://blog.csdn.net/kmyhy/article/details/78538687)

这也是这篇教程中最core的部分，介绍了UISearchController的使用，当然这个是没有新建UISearchController，放在同一个UI中，这里fake-wechat的项目是新建了一个专门的页面来展示。