```
- (UITableViewCell*)tableView:(UITableView*)tableView
        cellForRowAtIndexPath:(NSIndexPath*)indexPath
{
  static NSString* identifier = @"searchResultCell";
  ContactsTableViewCell* cell =
    [tableView dequeueReusableCellWithIdentifier:identifier];

  if (cell == nil)
    cell =
      [[ContactsTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault
                                   reuseIdentifier:identifier];

  return cell;
}
```

基本都是这样的，指定Identifier，检查Identifier是否存在，如果不存在，创造这样的cell，整个项目都是这样的。
