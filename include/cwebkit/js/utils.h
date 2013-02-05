#ifndef CWEBKIT_JS_UTILS_H
#define CWEBKIT_JS_UTILS_H

#include <JavaScriptCore/JavaScript.h>
#include "cwebkit/js/list.h"

void cwebkit_add_js_classes(JSGlobalContextRef ctx);
void cwebkit_add_js_class_to_list(JSClassDefinition def, JSStringRef name);
void jschr_to_chr(JSStringRef str, char *chr);

#endif