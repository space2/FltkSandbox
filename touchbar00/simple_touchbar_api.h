#pragma once

#if __APPLE__
#include "AvailabilityMacros.h"
#if MAC_OS_X_VERSION_MIN_REQUIRED >= 101202
#define HAS_SHOW_TOUCHBAR 1
#endif
#endif

#if HAS_SHOW_TOUCHBAR
extern "C" void ShowTouchBar(void * nswin, const char ** labels, void ** data, void (*cb)(void*, void*), void * userdata);
#else
static inline void ShowTouchBar(void * nswin, const char ** labels, void ** data, void (*cb)(void*, void*), void * userdata) {}
#endif
