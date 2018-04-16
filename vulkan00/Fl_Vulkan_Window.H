#ifndef Fl_Vulkan_Window_h
#define Fl_Vulkan_Window_h

#include <FL/Fl_Window.H>

#include <vulkan/vulkan.h>

class Fl_Vulkan_Window : public Fl_Window
{
public:
    Fl_Vulkan_Window(int x, int y, int w, int h, const char * l = 0);
    Fl_Vulkan_Window(int w, int h, const char * l = 0);

    virtual ~Fl_Vulkan_Window();

    /**
     * Show the window and create the vulkan surface
     */
    virtual void show();

    /** Return the vulkan instance used by this window */
    VkInstance vk_instance() { return _vk_instance; }
    /** Return the vulkan surface used by thus window */
    VkSurfaceKHR vk_surface() { return _vk_surface; }

protected:
    /**
     * Creates a vulkan instance.
     * The default implementation will simply create an instance with the bare minimum needed
     * to run vulkan applications.
     * Subclass could override this to simply return an already created instance.
     */
    virtual VkInstance create_vulkan_instance();

    virtual void draw();
    virtual void flush();
    virtual int handle(int event);

private:
    VkInstance _vk_instance;
    VkSurfaceKHR _vk_surface;
    bool _vk_instance_owned;
};

#endif /* Fl_Vulkan_Window_h */
