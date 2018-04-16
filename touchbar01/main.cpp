#include "touchbar.h"

#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <stdio.h>

static void CBDraw(void * userdata, int x, int y, int w, int h)
{
    printf("CBDraw[%p] %d,%d,%d,%d\n", userdata, x, y, w, h);
#if 1
    fl_draw_box(FL_UP_BOX, x, y, w, h, FL_BACKGROUND_COLOR);
    fl_color(FL_BLACK);
    fl_draw("Hello World!", x, y, w, h, FL_ALIGN_CENTER);
#else
    Fl_Button btn(x, y, w, h, "FooBar");
    btn.Fl_Widget::draw();
#endif
}

int main(int argc, const char * argv[])
{
    Fl_Window win(400, 100, "Testing");
    win.end();
    win.show();
    ShowTouchBar(nullptr, CBDraw);
    return Fl::run();
}

