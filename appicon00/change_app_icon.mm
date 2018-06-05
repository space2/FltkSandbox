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

void ChangeAppIconFromCG(void * cgctxref)
{
	CGContextRef ctx = (CGContextRef)cgctxref;
	CGImageRef image = CGBitmapContextCreateImage(ctx);
    NSImage * img = [[NSImage alloc] initWithCGImage:image size:NSZeroSize];
    [NSApplication sharedApplication].applicationIconImage = img;
	CFRelease(image);
}
