#include "fl_vulkan.H"

#import <Foundation/Foundation.h>
#import <Cocoa/Cocoa.h>

#include <stdio.h>

VkResult CreateFlWindowSurface(VkInstance instance, Fl_Window * win, VkSurfaceKHR * surface)
{
    NSWindow * nswin = (NSWindow *)fl_xid(win);
    printf("nswin=%p\n", nswin);
    NSView * nsview = [nswin contentView];
    printf("view=%p\n", nsview);

    PFN_vkCreateMacOSSurfaceMVK vkCreateMacOSSurfaceMVK;
    vkCreateMacOSSurfaceMVK = (PFN_vkCreateMacOSSurfaceMVK) vkGetInstanceProcAddr(instance, "vkCreateMacOSSurfaceMVK");
    if (!vkCreateMacOSSurfaceMVK) {
        printf("vkCreateMacOSSurfaceMVK not found!\n");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    // HACK: Dynamically load Core Animation to avoid adding an extra
    //       dependency for the majority who don't use MoltenVK
    NSBundle* bundle = [NSBundle bundleWithPath:@"/System/Library/Frameworks/QuartzCore.framework"];
    if (!bundle) {
        printf("Cocoa: Failed to find QuartzCore.framework\n");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }

    // NOTE: Create the layer here as makeBackingLayer should not return nil
    nsview.layer = [[bundle classNamed:@"CAMetalLayer"] layer];
    if (!nsview.layer) {
        printf("Cocoa: Failed to create layer for view\n");
        return VK_ERROR_EXTENSION_NOT_PRESENT;
    }
    [nsview setWantsLayer:YES];

    VkMacOSSurfaceCreateInfoMVK create_info = {};
    create_info.sType = VK_STRUCTURE_TYPE_MACOS_SURFACE_CREATE_INFO_MVK;
    create_info.pView = (void *)nsview;

    return vkCreateMacOSSurfaceMVK(instance, &create_info, nullptr, surface);
}
