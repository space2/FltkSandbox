#include "touchbar.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <FL/x.H>

static NSString *touchBarItemId = @"com.something.item_id";

@interface MyTouchBarView : NSView
{
    void * userdata;
    TouchBarDrawCallback draw_cb;
}
@property void * userdata;
@property TouchBarDrawCallback draw_cb;
- (void)drawRect:(NSRect)dirtyRect;
@end

@interface MyTouchBarDelegate : NSObject <NSTouchBarDelegate>
{
    void * userdata;
    TouchBarDrawCallback draw_cb;
}
- (void)setCallbacks:(void*)userdata draw_cb:(TouchBarDrawCallback)draw_cb;
- (NSTouchBar *)makeTouchBar;
- (NSTouchBarItem *)touchBar:(NSTouchBar *)touchBar makeItemForIdentifier:(NSTouchBarItemIdentifier)identifier;
@end

@implementation MyTouchBarView
@synthesize userdata, draw_cb;
- (void)drawRect:(NSRect)dirtyRect
{
    printf("drawRect %f,%f+%f,%f\n", dirtyRect.origin.x, dirtyRect.origin.y, dirtyRect.size.width, dirtyRect.size.height);
    CGContextRef ctx = (CGContextRef)[NSGraphicsContext currentContext].graphicsPort;
    fl_begin_offscreen((Fl_Offscreen)ctx);
    draw_cb(userdata, dirtyRect.origin.x, dirtyRect.origin.y, dirtyRect.size.width, dirtyRect.size.height);
    fl_end_offscreen();
}
@end

@implementation MyTouchBarDelegate

- (void)setCallbacks:(void*)userdata draw_cb:(TouchBarDrawCallback)draw_cb
{
    self->userdata = userdata;
    self->draw_cb = draw_cb;
}

- (NSTouchBar *)makeTouchBar
{
    printf("makeTouchBar\n");
    NSTouchBar *touchBar = [[NSTouchBar alloc] init];
    touchBar.delegate = self;
    touchBar.defaultItemIdentifiers = @[ touchBarItemId ];
    return touchBar;
}

- (NSTouchBarItem *)touchBar:(NSTouchBar *)touchBar makeItemForIdentifier:(NSTouchBarItemIdentifier)identifier
{
    printf("makeItemForIdentifier id=%s\n", [identifier UTF8String]);

    if (![identifier isEqualToString:touchBarItemId]) return nil;

    printf("makeItemForIdentifier\n");
    NSRect frame = { };
    MyTouchBarView * view = [[MyTouchBarView alloc] initWithFrame:frame];
    view.userdata = userdata;
    view.draw_cb = draw_cb;
    NSCustomTouchBarItem * touchbaritem = [[NSCustomTouchBarItem alloc] initWithIdentifier:identifier];
    touchbaritem.view = view;
    return touchbaritem;
}

@end

static MyTouchBarDelegate * touchbar = NULL;

void ShowTouchBar(void * userdata, TouchBarDrawCallback draw_cb)
{
    if (!touchbar) {
        touchbar = [[MyTouchBarDelegate alloc] init];
        [NSApplication sharedApplication].automaticCustomizeTouchBarMenuItemEnabled = YES;
    }
    NSTouchBar* touchBar = [touchbar makeTouchBar];
    [touchbar setCallbacks:userdata draw_cb:draw_cb];
    [NSApplication sharedApplication].touchBar = touchBar;
}

