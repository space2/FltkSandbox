#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

@interface MyTouchBarButton : NSButton
{
    void * userdata;
}
@property void * userdata;
@end

@interface MyTouchBarDelegate : NSObject <NSTouchBarDelegate>
{
    const char ** labels;
    void ** data;
    void (*cb)(void*, void*);
    void * userdata;
}
- (void)InitButtons:(const char **)labels data:(void **)data cb:(void (*)(void*, void*))cb userdata:(void*)userdata;
- (NSTouchBar *)makeTouchBar;
- (NSTouchBarItem *)touchBar:(NSTouchBar *)touchBar makeItemForIdentifier:(NSTouchBarItemIdentifier)identifier;
- (void)TBButtonAction:(id)sender;
@end

@implementation MyTouchBarButton
@synthesize userdata;
@end

@implementation MyTouchBarDelegate

- (void)InitButtons:(const char **)labels data:(void **)data cb:(void (*)(void*, void*))cb userdata:(void*)userdata
{
    self->labels = labels;
    self->data = data;
    self->cb = cb;
    self->userdata = userdata;
}

- (NSTouchBar *)makeTouchBar
{
    NSTouchBar *touchBar = [[NSTouchBar alloc] init];
    touchBar.delegate = self;
    NSMutableArray * ids = [[NSMutableArray alloc] init];
    for (int i = 0; self->labels[i]; i++) {
        [ids addObject:[NSString stringWithUTF8String:self->labels[i]]];
    }
    touchBar.defaultItemIdentifiers = ids;
    return touchBar;
}

- (NSTouchBarItem *)touchBar:(NSTouchBar *)touchBar makeItemForIdentifier:(NSTouchBarItemIdentifier)identifier
{
    const char * c_id = [identifier UTF8String];
    for (int i = 0; self->labels[i]; i++) {
        if (0 == strcmp(c_id, self->labels[i])) {
            NSString * label = [[NSString alloc] initWithUTF8String:self->labels[i]];
            MyTouchBarButton *button = [MyTouchBarButton buttonWithTitle:label target:self action:@selector(TBButtonAction:)];
            button.userdata = self->data[i];
            NSCustomTouchBarItem* touchbaritem = [[NSCustomTouchBarItem alloc] initWithIdentifier:identifier];
            touchbaritem.view = button;
            return touchbaritem;
        }
    }

    return nil;
}

- (void)TBButtonAction:(id)sender
{
    MyTouchBarButton * btn = sender;
    self->cb(self->userdata, btn.userdata);
}
@end

static MyTouchBarDelegate * touchbar = nullptr;

extern "C" void ShowTouchBar(NSWindow * nswin, const char ** labels, void ** data, void (*cb)(void*, void*), void * userdata)
{
    if (!touchbar) {
        touchbar = [[MyTouchBarDelegate alloc] init];
        [NSApplication sharedApplication].automaticCustomizeTouchBarMenuItemEnabled = YES;
    }

    [touchbar InitButtons:labels data:data cb:cb userdata:userdata];
    NSTouchBar* touchBar = [touchbar makeTouchBar];
    [NSApplication sharedApplication].touchBar = touchBar;
}
