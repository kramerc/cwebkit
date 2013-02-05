/*
 * Linked list of JavaScript classes for CWebKit
 */ 

#include <stdlib.h>
#include "cwebkit/js/list.h"

static struct js_node *cwebkit_js_list_make_node(JSClassDefinition def, JSStringRef name) {
	struct js_node *node = NULL;
	node = (struct js_node *) malloc(sizeof(struct js_node));
	node->def = def;
	node->name = name;
	node->next = NULL;
	return node;
}

void cwebkit_js_list_add(struct js_node **root, JSClassDefinition def, JSStringRef name) {
	struct js_node *node = cwebkit_js_list_make_node(def, name);
	struct js_node *cur = *root;
	struct js_node *prev = NULL;

	if (*root == NULL) {
		// First node
		*root = node;
	} else {
		// Work our way to the end and add it there
		while (cur != NULL) {
			prev = cur;
			cur = cur->next;
		}

		prev->next = node;
	}
}
