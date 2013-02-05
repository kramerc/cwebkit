/*
 * JavaScript utilities for CWebKit
 */ 

#include "cwebkit/js/utils.h"
 
static struct js_node *cwebkit_js_list = NULL;

/*
 * Adds a JavaScript class to a context
 */
static void cwebkit_add_js_class(JSGlobalContextRef ctx, JSClassDefinition class_def, JSStringRef name) {
	JSClassRef class_ref = JSClassCreate(&class_def);
	JSObjectRef class_obj = JSObjectMake(ctx, class_ref, ctx);
	JSObjectRef global_obj = JSContextGetGlobalObject(ctx);
	JSObjectSetProperty(ctx, global_obj, name, class_obj, kJSPropertyAttributeNone, NULL);
}

/*
 * Adds all JavaScript classes in the linked list to a context
 */
void cwebkit_add_js_classes(JSGlobalContextRef ctx) {
	struct js_node *cur = cwebkit_js_list;

	while (cur != NULL) {
		cwebkit_add_js_class(ctx, cur->def, cur->name);
		cur = cur->next;
	}
}

/*
 * Adds a JavaScript class in the linked list for adding to a context later
 */
void cwebkit_add_js_class_to_list(JSClassDefinition def, JSStringRef name) {
	cwebkit_js_list_add(&cwebkit_js_list, def, name);
}

/*
 * Converts a JSStringRef into a char array
 */
void jschr_to_chr(JSStringRef str, char *chr) {
	const JSChar *jschr = JSStringGetCharactersPtr(str); 
	int i;
	for (i = 0; i < JSStringGetLength(str); i++) {
		chr[i] = jschr[i];
	}
	chr[i] = '\0'; // Null-terminate
}