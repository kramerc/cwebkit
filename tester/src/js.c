#include "js.h"

static JSValueRef tester_js_test(JSContextRef ctx, JSObjectRef func, JSObjectRef this, size_t argc, const JSValueRef argv[], JSValueRef *ex);

/*
 * Static functions of CWebKit
 */
static const JSStaticFunction tester_static_funcs[] = {
	{ "test", tester_js_test, kJSPropertyAttributeReadOnly },
	{ NULL, NULL, 0 }
};

/*
 * Tester class defenition
 */
static const JSClassDefinition tester_def = {
	0,
	kJSClassAttributeNone,
	"TesterClass",
	NULL,
	NULL,
	tester_static_funcs,
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

static JSValueRef tester_js_test(JSContextRef ctx, JSObjectRef func, JSObjectRef this, size_t argc, const JSValueRef argv[], JSValueRef *ex) {
	JSStringRef str = JSStringCreateWithUTF8CString("Test!");
	return JSValueMakeString(ctx, str);
}

/*
 * Adds Tester class to a context
 */
void add_tester_js_class() {
	cwebkit_add_js_class_to_list(tester_def, JSStringCreateWithUTF8CString("tester"));
}