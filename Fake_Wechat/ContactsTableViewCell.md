```
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath{
  static NSString* identifier = @"contactsCellIdentifier";
  ContactsTableViewCell* cell = [tableView dequeueReusableCellWithIdentifier:identifier];

  if (cell == nil) {
    cell = [[ContactsTableViewCell alloc] init];
    [cell setRestorationIdentifier:identifier];

    cell.preservesSuperviewLayoutMargins = false;
    cell.layoutMargins = UIEdgeInsetsZero;
    cell.separatorInset = UIEdgeInsetsMake(0, 10, 0, 0);
  }
  return cell;
}
```

基本都是这样的，指定Identifier，检查Identifier是否存在，如果不存在，创造这样的cell，整个项目貌似都是这样的。


毫无疑问，那么设定的部分就被移去了别的地方， 我之前还没怎么见过这样写的呢，原本系统配备的函数是： `- (void)tableView:(UITableView *)tableView willDisplayCell:(UITableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath` 但是被改成了 ContactsTableViewCell, 除此之外，并没有别的更改，这样酷酷的也是可以的哦。


```
- (void)tableView:(UITableView *)tableView willDisplayCell:(ContactsTableViewCell *)cell forRowAtIndexPath:(NSIndexPath *)indexPath{
  if (indexPath.section == 0) {
    cell.avatar = [UIImage imageNamed:self.firstSectionData[indexPath.row][0]];
    cell.name =self.firstSectionData[indexPath.row][1];
  } else {
    cell.avatar = [UIImage randomImageInPath:@"Images/cell_icons"];
    cell.name = self.groupedContacts[indexPath.section - 1][indexPath.row];
    NSLog(@"%@", self.groupedContacts[indexPath.section-1][indexPath.row]);
  }
}

```


然后终于找到了给 Contacts 加右边字母的秘诀，调用这个系统函数：
`-(NSArray<NSString*>*)sectionIndexTitlesForTableView:(UITableView *)tableView
`
NSArray<NSString*>* 指的是首先因为NSString只能是引用类型，所以*，NSArray 也只能是引用类型，所以结合起来是`NSArray<NSString*>*`
