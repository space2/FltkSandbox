#include "simple_touchbar_api.h"

#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>

#include <stdio.h>

static void TouchBarCallback(void * userdata, void * itemdata)
{
    printf("TouchBarCallback: userdata=%p itemdata=%p\n", userdata, itemdata);
}

int main(int argc, const char * argv[])
{
    Fl_Window win(400, 200, "Testing");
    Fl_Button btn(100, 90, 200, 20, "Hello World!");
    win.end();
    win.show();
    
    static const char * kTouchbarButtons[] = {
        "Main", "2D", "3D", nullptr,
    };
    static void * kTouchBarUserData[] = {
        (void*)(intptr_t)1, (void*)(intptr_t)42, (void*)(intptr_t)256, nullptr,
    };
    
    ShowTouchBar(fl_xid(&win), kTouchbarButtons, kTouchBarUserData, TouchBarCallback, &win);
    
    return Fl::run();
}
