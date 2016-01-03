#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <webkit/webkit.h>


char* url = "https://www.tumblr.com/tv/@computersarerad";
//static gboolean closeWebViewCb(WebKitWebView* webView, GtkWidget* window);

static void destroyWindow(GtkWidget *widget, GtkWidget* data ) {
  gtk_main_quit ();
}

static GtkWidget* getWindow(){
  GtkWidget *main_window;
  char* xwindow_s = getenv("XSCREENSAVER_WINDOW");

  if (xwindow_s != NULL) {
    // parse out the xid from xscreensaver's env var, which is given as
    // hex like 0x12023
    int xid = (int)strtol(xwindow_s, NULL, 0);

    // if we are running in xscreensaver mode, use the provided window XID
    main_window = gtk_window_new(GTK_WINDOW_POPUP);
    GdkWindow *gdk_win = gdk_window_foreign_new(xid);
    gtk_widget_show_all(main_window);
    // reparent window of main_window to gdk_win
    //      win.get_window().reparent(self.gdk_win, 0, 0)
    //gtk_widget_reparent(gdk_win, 0, 0)
    //gtk_widget_set_parent_window(main_window, gdk_win);
    gdk_window_reparent(gtk_widget_get_window(main_window), gdk_win, 0, 0);
    gint width;
    gint height;
    gdk_window_get_geometry(gdk_win, NULL, NULL, &width, &height, NULL);
    printf("Got height of gdk window: %dx%d\n",width,height);
    // Make us cover our parent window
    gtk_window_move(main_window, 0, 0);
    gtk_window_set_default_size(main_window, width, height);
    gtk_widget_set_size_request(main_window, width, height);
  } else {
    // otherwise just get a normal window

    printf("creating gtk stuff for browser\n");
    // Create an 800x600 window that will contain the browser instance
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
  }
  return main_window;
}

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);

    GtkWidget *main_window = getWindow();

    // Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindow), NULL);
    g_signal_connect(main_window, "delete-event", G_CALLBACK(destroyWindow), NULL);

    // transparent background so we dont have any white flashes
    webkit_web_view_set_transparent(webView, true);

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

