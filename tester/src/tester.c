#include <cwebkit/cwebkit.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "js.h"

int main(int argc, char *argv[]) {
	printf("CWebKit Tester\n");

	// Init the window
	cwebkit_init(&argc, &argv);

	// Add the Tester JavaScript class
	add_tester_js_class();

	// Create a webkit window
	const WebKitWindow webkit = cwebkit_create_window("Tester", 800, 600);

	// Show the webkit window with the default page
	cwebkit_show_window(webkit, CWEBKIT_DEFAULT);

	return 0;
}