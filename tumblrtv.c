#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <webkit2/webkit2.h>


char* url = "https://www.tumblr.com/tv/@computersarerad";
//static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

static void destroyWindow(GtkWidget *widget, GtkWidget* data ) {
  gtk_main_quit ();
}

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

/*
		//Open the display
    printf("Getting x11 display\n");
    Display *display = XOpenDisplay(NULL);
    if (display == NULL){
      printf("display is null. what in the fuck\n");
      exit(1);
    }
    */

    printf("Getting gdk screen?\n");
    GdkDisplay *gdkscreen = gdk_screen_get_default ();
    if (gdkscreen == NULL){
      printf("gdkscreen is null. what in the fuck\n");
      exit(1);
    }

    printf("Getting gdk root window from screen\n");
    GdkWindow *gdk_window = gdk_screen_get_root_window (gdkscreen);
    if (gdk_window == NULL){
      printf("gdkwindow is null. what in the fuck\n");
      exit(1);
    }

    gint width;
    gint height;
    gdk_window_get_geometry(gdk_window, NULL, NULL, &width, &height);
    printf("Got GDK window width height %d %d\n", width, height);

    GdkRGBA bg = {
      .red = 1.0,
      .blue = 1.0,
      .green = 0.0,
      .alpha = 1.0
    };
    printf("Setting gdk window background\n");
    gdk_window_set_background_rgba(gdk_window, &bg);
    /*
    //Create the window
    printf("Getting X window\n");
    //Window w = XCreateSimpleWindow(display, DefaultRootWindow(display), 0, 0, 200, 100, 20, black, 10201020);
    Window w = DefaultRootWindow(display);
    //Window w = gdk_x11_get_default_root_xwindow();
    printf("seting background\n");
    //TODO(this isnt working)
		XSetWindowBackground(display, w, 254);
    */


    printf("creating gtk stuff for browser\n");
    // Create an 800x600 window that will contain the browser instance
    GtkWidget *main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);

    // Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindow), NULL);
    //g_signal_connect(main_window, "destroy", G_CALLBACK(print), NULL);
		//TODO is this necessary
    //g_signal_connect(webView, "close", G_CALLBACK(closeWebViewCb), main_window);

		// set the window for the GTKWindow to the X11 Root window
		//GdkDisplay* gdk_display = gdk_x11_lookup_xdisplay(display);
		//GdkDisplay* gdk_display = GDK_DISPLAY_XDISPLAY(display);
    /*
		if (gdk_display == NULL){
			printf("gdk_display is null! Shit!\n");
			exit(1);
    }
		GdkWindow* gdk_window = gdk_x11_window_foreign_new_for_display(gdk_display, w);
    */
		//gtk_widget_set_parent_window(main_window, gdk_window_foreign_new((guint32)w));
		gtk_widget_set_parent_window(main_window, gdk_window);

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
