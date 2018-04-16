//
//  touchbar.h
//  OSXChangeAppIcon0
//
//  Created by Szasz, Pal on 4/4/18.
//  Copyright © 2018 Szasz, Pal. All rights reserved.
//

#ifndef touchbar_h
#define touchbar_h

typedef void (*TouchBarDrawCallback)(void * userdata, int x, int y, int w, int h);
extern "C" void ShowTouchBar(void * userdata, TouchBarDrawCallback draw_cb);

#endif /* touchbar_h */
