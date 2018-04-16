//
//  fl_vulkan.h
//  TestFltkWithVulkan
//
//  Created by Szasz, Pal on 4/10/18.
//  Copyright © 2018 Szasz, Pal. All rights reserved.
//

#ifndef fl_vulkan_h
#define fl_vulkan_h

#include <FL/x.H>
#include <FL/Fl_Window.H>

#define VK_USE_PLATFORM_MACOS_MVK
#include <vulkan/vulkan.h>

extern "C" VkResult CreateFlWindowSurface(VkInstance instance, Fl_Window * win, VkSurfaceKHR * surface);

#endif /* fl_vulkan_h */
