#include "junk.h"
#include "change_app_icon.h"

#include <FL/x.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Button.H>
#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include <stdio.h>

static void CBSetIconFromPNG(Fl_Widget *, void *)
{
    ChangeAppIcon(kJunkPNG, kJunkPNG_len);
}

static void CBSetIconFromCode(Fl_Widget *, void *)
{
	Fl_Offscreen ctx = fl_create_offscreen(128, 128);
    fl_begin_offscreen((Fl_Offscreen)ctx);
    fl_rectf(0, 0, 128, 128, FL_DARK_RED);
    fl_rectf(8, 8, 112, 112, FL_RED);
    fl_end_offscreen();
	ChangeAppIconFromCG(ctx);
}

static void CBSetIconWithFLTK(Fl_Widget * w, void *)
{
    Fl_RGB_Image * img = new Fl_PNG_Image("junk", kJunkPNG, kJunkPNG_len);
    printf("img: w=%d h=%d d=%d\n", img->w(), img->h(), img->d());
    w->window()->icon(img);
}

int main(int argc, const char * argv[])
{
    Fl_Window win(400, 100, "Testing");
    Fl_Button btn(10, 20, 180, 20, "Set icon from PNG!");
    btn.callback(CBSetIconFromPNG);
    Fl_Button btn2(210, 20, 180, 20, "Set icon from code!");
    btn2.callback(CBSetIconFromCode);
    Fl_Button btn3(10, 60, 180, 20, "Set icon with FLTK!");
    btn3.callback(CBSetIconWithFLTK);
    win.end();
    CBSetIconWithFLTK(&btn3, nullptr); // Hack: docs said we should do this before show just in case
    win.show();
    return Fl::run();
}

