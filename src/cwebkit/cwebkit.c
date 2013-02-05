/*
 * Abstract CWebKit methods
 */ 

#include "cwebkit/cwebkit.h"

void cwebkit_init(int *argc, char ***argv) {
	cwebkit_add_cwebkit_js_class();
	cwebkit_init_gtk(argc, argv);
}

const WebKitWindow cwebkit_create_window(char *title, int width, int height) {
	return cwebkit_create_gtk_window(title, width, height);
}

void cwebkit_show_window(WebKitWindow webkit, char *url) {
	cwebkit_show_gtk_window(webkit, url);
}