
```
_tableView = ({
  UITableView* tableView = [[UITableView alloc]
                            initWithFrame:CGRectMake(0, 0, self.view.frame.size.width, self.view.frame.size.height)
                            style:UITableViewStylePlain];

  tableView.delegate = self;
  tableView.dataSource = self;

  tableView.separatorInset = UIEdgeInsetsMake(0, 0, 0, 0 );
  tableView.rowHeight = 50;

  tableView.tableFooterView = [self tableFooterView];
  tableView.tableHeaderView = [self tableHeaderView];

  // sectionIndex
  tableView.sectionIndexColor = [UIColor grayColor];
  tableView.sectionIndexBackgroundColor = [UIColor clearColor];

  tableView;
});
```

这种写法感觉在Swift中见过，理解但是还是觉得有点神奇，我们把一切需要设定的东西完成，然后通过 _tableView = ({ ... tableView}); 完毕。
