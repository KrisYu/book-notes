#import <Foundation/Foundation.h>

@interface Character: NSObject {
    NSString *characterName;
    NSInteger ownedClowCards;
}

@property (nonatomic, copy) NSString *characterName;
@property NSInteger ownedClowCards;

- (void) hasLostClowCard;
- (void) hasGainedClowCard;
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context;

@end

@implementation Character
@synthesize characterName;
@synthesize ownedClowCards;

- (void)hasLostClowCard{
    NSLog(@"%@ has lost a card! Cards now: %ld", characterName, ownedClowCards);
}

- (void)hasGainedClowCard{
    NSLog(@"%@ has earned a card! Cards now: %ld", characterName, ownedClowCards);
}

- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context{
    if ([keyPath isEqualToString:@"ownedClowCards"]) {
        NSInteger newC = [change objectForKey:NSKeyValueChangeNewKey];
        NSInteger oldC = [change objectForKey:NSKeyValueChangeOldKey];

        if (oldC < newC) {
            [self hasGainedClowCard];
        } else if (oldC > newC) {
            [self hasLostClowCard];
        } else {
            NSLog(@"Nothing has changed");
        }
    }
}





@end


int main() {
    Character *sakura;
    Character *shaoran;

    // Create and give the properties some values with KVC
    sakura = [[Character alloc] init];
    [sakura setValue:@"Sakura Kinomoto" forKey:@"characterName"];
    [sakura setValue:@20 forKey:@"ownedClowCards"];

    [sakura addObserver:sakura forKeyPath:@"ownedClowCards"
                options:NSKeyValueObservingOptionNew | NSKeyValueObservingOptionOld
                context:nil];


    shaoran = [[Character alloc] init];
    [shaoran setValue:@"Li Shaoran" forKey:@"characterName"];
    [shaoran setValue:@21 forKey:@"ownedClowCards"];

    // Done! Now we are going to fetch the values using KVC.
    NSString *mainCharacter = [sakura valueForKey:@"characterName"];
    NSNumber *mainCharCards = [sakura valueForKey:@"ownedClowCards"];

    NSString *rival = [shaoran valueForKey:@"characterName"];
    NSNumber *rivalCards = [shaoran valueForKey:@"ownedClowCards"];

    NSLog(@"%@ has %d Clow Cards", mainCharacter, mainCharCards.intValue);
    NSLog(@"%@ has %d Clow Cards", rival, rivalCards.intValue);

    sakura.ownedClowCards = 21;

    [sakura setValue:@21 forKey:@"ownedClowCards"];

    [sakura removeObserver:sakura
                forKeyPath:@"ownedClowCards"];
}
