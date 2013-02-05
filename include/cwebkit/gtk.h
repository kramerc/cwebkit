#ifndef CWEBKIT_GTK_H
#define CWEBKIT_GTK_H

#include <gtk/gtk.h>
#include <webkit/webkit.h>
#include "cwebkit/defs.h"
#include "cwebkit/js.h"

typedef struct cwebkit_window {
	GtkWidget *window;
	WebKitWebView *web_view;
	WebKitWebSettings *web_settings;
} WebKitWindow;

void cwebkit_init_gtk(int *argc, char ***argv);
const WebKitWindow cwebkit_create_gtk_window(char *title, int width, int height);
void cwebkit_show_gtk_window(WebKitWindow webkit, char *url);

#endif
