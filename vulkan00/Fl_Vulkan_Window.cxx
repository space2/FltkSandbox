#include "Fl_Vulkan_Window.H"
#include "fl_vulkan.H"

#include <stdio.h>

#define VERBOSE 2 // 0=silent 1=errors 2=verbose
#define USE_VALIDATION_LAYER 1

static VkInstance vk_instance = 0;
static int vk_instance_ref_count = 0;

static const char * kLayers[] = {
#if USE_VALIDATION_LAYER
    "VK_LAYER_LUNARG_standard_validation"
#endif
};
static const int kLayerCount = sizeof(kLayers)/sizeof(kLayers[0]);

static const char * kExtensions[] = {
    "VK_EXT_debug_report",
    "VK_KHR_surface",
#if __APPLE__
    "VK_MVK_macos_surface",
#endif
};
static const int kExtensionCount = sizeof(kExtensions)/sizeof(kExtensions[0]);


static void release_vk_instance()
{
    if (0 == --vk_instance_ref_count) {
        vkDestroyInstance(vk_instance, nullptr);
        vk_instance = 0;
    }
}

static VkInstance alloc_vk_instance()
{
    if (!vk_instance) {
        if (VERBOSE > 1) printf("alloc_vk_instance...\n");

        VkApplicationInfo appInfo = {};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "FLTK";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "FLTK";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo createInfo = {};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = kExtensionCount;
        createInfo.ppEnabledExtensionNames = kExtensions;
        createInfo.enabledLayerCount = kLayerCount;
        createInfo.ppEnabledLayerNames = kLayers;
        VkResult result = vkCreateInstance(&createInfo, nullptr, &vk_instance);
        if (result != VK_SUCCESS) {
            if (VERBOSE) fprintf(stderr, "vkCreateInstance failed: %d\n", result);
        }
        vk_instance_ref_count = 0;
    }
    vk_instance_ref_count++;
    return vk_instance;
}

Fl_Vulkan_Window::Fl_Vulkan_Window(int x, int y, int w, int h, const char * l)
    : Fl_Window(x, y, w, h, l), _vk_instance(0), _vk_surface(0), _vk_instance_owned(0)
{
    end();
}

Fl_Vulkan_Window::Fl_Vulkan_Window(int w, int h, const char * l)
    : Fl_Window(w, h, l), _vk_instance(0), _vk_surface(0), _vk_instance_owned(0)
{
    end();
}

Fl_Vulkan_Window::~Fl_Vulkan_Window()
{
    if (_vk_surface) {
        vkDestroySurfaceKHR(_vk_instance, _vk_surface, nullptr);
    }
    if (_vk_instance_owned) {
        release_vk_instance();
    }
}

VkInstance Fl_Vulkan_Window::create_vulkan_instance()
{
    _vk_instance_owned = true;
    return alloc_vk_instance();
}

void Fl_Vulkan_Window::show()
{
    Fl_Window::show();
    if (!_vk_instance) {
        _vk_instance = create_vulkan_instance();
    }
    if (!_vk_surface) {
        VkResult result = CreateFlWindowSurface(_vk_instance, this, &_vk_surface);
        if (result != VK_SUCCESS) {
            if (VERBOSE) fprintf(stderr, "CreateFlWindowSurface failed: %d\n", result);
        }
        set_visible();
        redraw();
    }
}

void Fl_Vulkan_Window::draw()
{
    if (VERBOSE > 1) printf("Fl_Vulkan_Window::draw\n");
    Fl_Window::draw();
}

void Fl_Vulkan_Window::flush()
{
    if (VERBOSE > 1) printf("Fl_Vulkan_Window::flush\n");
    Fl_Window::flush();
}

int Fl_Vulkan_Window::handle(int event)
{
    int ret = Fl_Window::handle(event);
    if (VERBOSE > 1) if (event != 11) printf("Fl_Vulkan_Window::handle(%d)=%d\n", event, ret);
    if (event == FL_FOCUS) ret = 1;
    return ret;
}
