#include "change_app_icon.h"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

static NSImage * icon_canvas;

void ChangeAppIcon(const void * data, int bytes)
{
    NSData * nsdata = [NSData dataWithBytesNoCopy:(void*)data length:bytes freeWhenDone:false];
    NSImage * img = [[NSImage alloc] initWithData:nsdata];
    [NSApplication sharedApplication].applicationIconImage = img;
}

void * BeginChangeAppIcon(int w, int h)
{
    NSSize size = { (float)w, (float)h };
    icon_canvas = [[NSImage alloc] initWithSize:size];
    [icon_canvas lockFocus];
    CGContextRef ctx = (CGContextRef)[NSGraphicsContext currentContext].graphicsPort;
    return ctx;
}

void FinishChangeAppIcon()
{
    [icon_canvas unlockFocus];
    [NSApplication sharedApplication].applicationIconImage = icon_canvas;
}
