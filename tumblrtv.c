#include <gtk/gtk.h>
#include <webkit2/webkit2.h>


char* url = "https://www.tumblr.com/tv/@computersarerad";
static void destroyWindowCb(GtkWidget* widget, GtkWidget* window);
//static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

    // Create an 800x600 window that will contain the browser instance
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    // Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindowCb), NULL);
		//TODO is this necessary
    //g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

    // Load a web page into the browser instance
    webkit_web_view_load_uri(webView, url);

    // Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));

    // Make sure the main window and all its contents are visible
    gtk_widget_show_all(main_window);

    // Run the main GTK+ event loop
    gtk_main();

    return 0;
}


static void destroyWindowCb(GtkWidget* widget, GtkWidget* window)
{
    gtk_main_quit();
}
/*

//TODO: when this callback is hooked up, closing the window gives:
//(WebKitWebProcess:7873): Gdk-ERROR **: The program 'WebKitWebProcess' received an X Window System error.
//This probably reflects a bug in the program.
//The error was 'BadDrawable (invalid Pixmap or Window parameter)'.
//  (Details: serial 285 error_code 9 request_code 14 (core protocol) minor_code 0)
//  (Note to programmers: normally, X errors are reported asynchronously;
//   that is, you will receive the error a while after causing it.
//   To debug your program, run it with the GDK_SYNCHRONIZE environment
//   variable to change this behavior. You can then get a meaningful
//   backtrace from your debugger if you break on the gdk_x_error() function.)

static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window)
{
    gtk_widget_destroy(window);
    return TRUE;
}
*/
