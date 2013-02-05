/*
 * GTK-specific CWebKit
 */ 

#include "cwebkit/gtk.h"
#include <string.h>

// Prototypes of static functions
static void cwebkit_gtk_quit_if_last();
static void cwebkit_window_destroy_cb(GtkWidget *widget, gpointer data);
static void cwebkit_window_close_web_view_cb(WebKitWebView *web_view, gpointer data);
static WebKitWebView *cwebkit_window_create_web_view_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, gpointer data);
static gboolean cwebkit_window_load_error_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, gchar *uri, GError *web_error, gpointer data);
static void cwebkit_window_object_cleared_cb(WebKitWebView *web_view, WebKitWebFrame *frame, gpointer context, gpointer arg3, gpointer data);
static void cwebkit_window_resource_request_starting_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, WebKitWebResource *web_resource, WebKitNetworkRequest *request, WebKitNetworkResponse *response, gpointer data);
static gboolean cwebkit_window_script_alert_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, gchar *message, gpointer data);
static void cwebkit_window_title_changed_cb(GObject *object, GParamSpec *pspec, gpointer data);

/*
 * Initializes the window system, GTK in this case
 */
void cwebkit_init_gtk(int *argc, char ***argv) {
	gtk_init(argc, argv);
}

/*
 * Creates a webkit window
 */
const WebKitWindow cwebkit_create_gtk_window(char *title, int width, int height) {
	GtkWidget *window;					// Main window
	GtkWidget *scrolled_window;			// Scrolled window that holds WebKit
	WebKitWebView *web_view;			// WebKit view	
	WebKitWebSettings *web_settings;	// WebKit settings
	WebKitWindow new_webkit;			// WebKit struct

	// Create the main window
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_title(GTK_WINDOW(window), title);
	gtk_window_set_default_size(GTK_WINDOW(window), width, height);

	// Create the scrolled window
	scrolled_window = gtk_scrolled_window_new(NULL, NULL);

	// Create the WebKit view
	web_view = WEBKIT_WEB_VIEW(webkit_web_view_new());
	gtk_container_add(GTK_CONTAINER(scrolled_window), GTK_WIDGET(web_view));

	// Set default settings
	web_settings = webkit_web_settings_new();
	g_object_set(G_OBJECT(web_settings), "auto-resize-window", TRUE, NULL);
	g_object_set(G_OBJECT(web_settings), "enable-default-context-menu", FALSE, NULL);
	g_object_set(G_OBJECT(web_settings), "javascript-can-open-windows-automatically", TRUE, NULL);
	webkit_web_view_set_settings(WEBKIT_WEB_VIEW(web_view), web_settings);

	// Add the scrolled window to the parent window
	gtk_container_add(GTK_CONTAINER(window), scrolled_window);

	// Connect a destroy signal to the parent window
	g_signal_connect_swapped(G_OBJECT(window), "destroy", G_CALLBACK(cwebkit_window_destroy_cb), NULL);

	// Connect signals to the web view
	g_signal_connect(G_OBJECT(web_view), "close-web-view", G_CALLBACK(cwebkit_window_close_web_view_cb), web_view);
	g_signal_connect(G_OBJECT(web_view), "create-web-view", G_CALLBACK(cwebkit_window_create_web_view_cb), web_view);
	g_signal_connect(G_OBJECT(web_view), "load-error", G_CALLBACK(cwebkit_window_load_error_cb), web_view);
	g_signal_connect(G_OBJECT(web_view), "resource-request-starting", G_CALLBACK(cwebkit_window_resource_request_starting_cb), web_view);
	g_signal_connect(G_OBJECT(web_view), "script-alert", G_CALLBACK(cwebkit_window_script_alert_cb), web_view);
	g_signal_connect(G_OBJECT(web_view), "window-object-cleared", G_CALLBACK(cwebkit_window_object_cleared_cb), web_view);
	g_object_connect(G_OBJECT(web_view), "signal::notify::title", G_CALLBACK(cwebkit_window_title_changed_cb), NULL);

	// Set the pointers in the struct
	new_webkit.window = window;
	new_webkit.web_view = web_view;
	new_webkit.web_settings = web_settings;

	// Return the struct
	return new_webkit;
}

/*
 * Shows a webkit window
 */
void cwebkit_show_gtk_window(WebKitWindow webkit, char *uri) {
	// Show the window
	gtk_widget_show_all(webkit.window);

	// Open the URI
	webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webkit.web_view), uri);

	// Pass to GTK's main
	gtk_main();
}

static void cwebkit_gtk_quit_if_last() {
	
}

static void cwebkit_window_destroy_cb(GtkWidget *widget, gpointer data) {
	// Check for remaining windows
	GList *windows = gtk_window_list_toplevels();
	int length;

	if (g_list_length(windows) < 4) {
		gtk_main_quit();
	}
}

/*
 * Handles close web view events
 */
static void cwebkit_window_close_web_view_cb(WebKitWebView *web_view, gpointer data) {
	gtk_widget_destroy(gtk_widget_get_toplevel(GTK_WIDGET(web_view)));
}

/*
 * Handles new web view events
 */
static WebKitWebView *cwebkit_window_create_web_view_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, gpointer data) {
	WebKitWindow new_webkit = cwebkit_create_gtk_window("New Window", 800, 600);
	gtk_widget_show_all(new_webkit.window);
	return new_webkit.web_view;
}

static void cwebkit_window_object_cleared_cb(WebKitWebView *web_view, WebKitWebFrame *frame, gpointer context, gpointer arg3, gpointer data) {
	JSGlobalContextRef js_context = webkit_web_frame_get_global_context(frame);
	cwebkit_add_js_classes(js_context);
}

static gboolean cwebkit_window_load_error_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, gchar *uri, GError *web_error, gpointer data) {
	// TODO: Implement friendlier error pages	
	return FALSE;
}

/*
 * Handles scheme overrides.
 */
static void cwebkit_window_resource_request_starting_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, WebKitWebResource *web_resource, WebKitNetworkRequest *request, WebKitNetworkResponse *response, gpointer data) {
	const gchar *request_uri = webkit_network_request_get_uri(request);
	
	// Handle app:// URIs
	if (strstr(request_uri, CWEBKIT_APP_SCHEME) != NULL) {
		char cwd[1024];
		char uri[1024];
		const char *path = &request_uri[strlen(CWEBKIT_APP_SCHEME)];
		
		// Get the current working directory
		getcwd(cwd, sizeof(cwd));

		// Convert to a file URI.
		strcpy(uri, "file://");
		strcat(uri, cwd);
		strcat(uri, "/");
		strcat(uri, CWEBKIT_WEB_FOLDER);
		strcat(uri, "/");

		if (strlen(path) < 1) {
			strcat(uri, "index.html");
		} else {
			strcat(uri, path);
		}

		webkit_network_request_set_uri(request, uri);
	}
}

/*
 * Handles scripted alert dialogs
 */
static gboolean cwebkit_window_script_alert_cb(WebKitWebView *web_view, WebKitWebFrame *web_frame, gchar *message, gpointer data) {
	GtkWidget *parent_window = gtk_widget_get_toplevel(GTK_WIDGET(web_view));
	GtkWidget *dialog = gtk_message_dialog_new(GTK_WINDOW(parent_window), GTK_DIALOG_MODAL, GTK_MESSAGE_INFO, GTK_BUTTONS_OK, message, NULL);
	gtk_window_set_title(GTK_WINDOW(dialog), gtk_window_get_title(GTK_WINDOW(parent_window)));
	
	gtk_dialog_run(GTK_DIALOG(dialog));
	gtk_widget_destroy(dialog);

	return TRUE;
}

/*
 * Updates the window title when changed in the web view
 */
static void cwebkit_window_title_changed_cb(GObject *object, GParamSpec *pspec, gpointer data) {
	WebKitWebView *web_view = WEBKIT_WEB_VIEW(object);
	const gchar *title = webkit_web_view_get_title(web_view);

	if (title != NULL) {
		gtk_window_set_title(GTK_WINDOW(gtk_widget_get_toplevel(GTK_WIDGET(web_view))), title);
	}
}