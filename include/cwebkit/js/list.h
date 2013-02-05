#ifndef CWEBKIT_cwebkit_js_list_H
#define CWEBKIT_cwebkit_js_list_H

#include <JavaScriptCore/JavaScript.h>

struct js_node {
	JSClassDefinition def;
	JSStringRef name;
	struct js_node *next;
};

void cwebkit_js_list_add(struct js_node **root, JSClassDefinition def, JSStringRef name);

#endif