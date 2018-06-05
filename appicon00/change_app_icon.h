#ifndef change_app_icon_h
#define change_app_icon_h

extern "C" {
    void ChangeAppIcon(const void * data, int bytes);
	void ChangeAppIconFromCG(void * cgctxref);
}

#endif /* change_app_icon_h */
