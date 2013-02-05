/*
 * JavaScript bindings for CWebKit
 */ 

#include "cwebkit/js.h"
#include <stdlib.h>

static JSValueRef cwebkit_js_exit(JSContextRef ctx, JSObjectRef func, JSObjectRef this, size_t argc, const JSValueRef argv[], JSValueRef *ex);

/*
 * Static functions of CWebKit
 */
static const JSStaticFunction cwebkit_static_funcs[] = {
	{ "exit", cwebkit_js_exit, kJSPropertyAttributeReadOnly },
	{ NULL, NULL, 0 }
};

/*
 * Tester class defenition
 */
static const JSClassDefinition cwebkit_def = {
	0,
	kJSClassAttributeNone,
	"CWebKitClass",
	NULL,
	NULL,
	cwebkit_static_funcs,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

/*
 * Exits the program along with a given exit code
 */
static JSValueRef cwebkit_js_exit(JSContextRef ctx, JSObjectRef func, JSObjectRef this, size_t argc, const JSValueRef argv[], JSValueRef *ex) {
	int exit_code;

	if (argc == 0) {
		exit_code = 0;
	} else {
		exit_code = (int) JSValueToNumber(ctx, argv[0], ex);
	}

	exit(exit_code);
}

/*
 * Adds CWebKit class to the class list
 */
void cwebkit_add_cwebkit_js_class() {
	cwebkit_add_js_class_to_list(cwebkit_def, JSStringCreateWithUTF8CString("cwebkit"));
}