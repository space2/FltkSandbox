#ifndef change_app_icon_h
#define change_app_icon_h

extern "C" {
    void ChangeAppIcon(const void * data, int bytes);
    void * BeginChangeAppIcon(int w, int h);
    void FinishChangeAppIcon();
}

#endif /* change_app_icon_h */
