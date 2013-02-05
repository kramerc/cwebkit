#ifndef CWEBKIT_H
#define CWEBKIT_H

#include "cwebkit/defs.h"
#include "cwebkit/gtk.h"
#include "cwebkit/js/utils.h"

void cwebkit_init(int *argc, char ***argv);
const WebKitWindow cwebkit_create_window(char *title, int width, int height);
void cwebkit_show_window(WebKitWindow webkit, char *url);

#endif