Custom fltk drawing into the touchbar area.

This solution gives a callback to draw the Touch Bar, so the FLTK
drawing functions can be used. Note however that:

* no events are received yet from the Touch Bar
* no redraw can be sent to the Touch Bar yet
* no widgets can be added to the Touch Bar.

Ideally we would attach an FLView to the touchbar’s NSWindow, however
the toucher’s NSWindow is not created by us, so we cannot use FLWindow,
hence FLView wouldn’t work as it is right now.