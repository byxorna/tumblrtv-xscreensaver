#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wordexp.h>
#include <webkit/webkit.h>

const int MAX_TAG_LENGTH = 100;
const int MAX_NUMBER_TAGS = 100;
const int MAX_URL_LENGTH = 200;
const char* URL_FORMAT = "https://www.tumblr.com/tv/%s";
const char* CONFIG_PATH = "~/.config/tumblrtv-xscreensaver/tags";
const char* DEFAULT_TAGS[] = {
  "bill nye",
  "@computersarerad",
  "trippy"
};

static void load_status_cb(WebKitWebView* webview, GParamSpec *pspec, gpointer user_data){
  //TODO is GParamSpec holding the actual value?
  WebKitLoadStatus s = webkit_web_view_get_load_status(webview);
  if (s == WEBKIT_LOAD_FINISHED){
    printf("Loading Tumblr TV succeeded!\n");
    // Make sure the webview contents are visible now that things are loaded
    gtk_widget_show(GTK_WIDGET(webview));
  } else if (s == WEBKIT_LOAD_FAILED){
    printf("Load failed! Womp womp :(\n");
    gtk_widget_hide(GTK_WIDGET(webview));
    // schedule a refresh for a while from now
    //TODO this blocks the main thread!!!! :(
    sleep(10);
    printf("requesting reload\n");
    gtk_widget_show(GTK_WIDGET(webview));
    //TODO should we request_uri instead? looks like we dont receive load-status events
    // when loading from a load-failure page :(
    webkit_web_view_go_back(webview);
    webkit_web_view_reload(webview);
    //webkit_web_view_reload_bypass_cache(webview);
  } else {
    printf("at least something is happening\n");
  }
}

static void destroyWindow(GtkWidget* widget, GtkWidget* data ) {
  gtk_main_quit ();
}

static void createDrawContext(GtkWidget** widget, GdkWindow** window){
  GtkWidget *main_window;
  GdkWindow *gdk_win;
  char* xwindow_s = getenv("XSCREENSAVER_WINDOW");

  if (xwindow_s != NULL) {
    // parse out the xid from xscreensaver's env var, which is given as
    // hex like 0x12023
    int xid = (int)strtol(xwindow_s, NULL, 0);

    // if we are running in xscreensaver mode, use the provided window XID
    main_window = gtk_window_new(GTK_WINDOW_POPUP);
    //main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gdk_win = gdk_window_foreign_new(xid);
    // reparent window of main_window to gdk_win
    gdk_window_reparent(gtk_widget_get_window(main_window), gdk_win, 0, 0);
    gint width;
    gint height;
    gdk_window_get_geometry(gdk_win, NULL, NULL, &width, &height, NULL);
    printf("Looks like we are about %dx%d\n",width,height);
    // Make us cover our parent window
    gtk_window_move(GTK_WINDOW(main_window), 0, 0);
    gtk_window_set_default_size(GTK_WINDOW(main_window), width, height);
    gtk_widget_set_size_request(main_window, width, height);
  } else {
    // otherwise just get a normal window
    main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(main_window), 800, 600);
    gdk_win = gtk_widget_get_window(main_window);
  }
  *widget = main_window;
  *window = gdk_win;
}

int main(int argc, char* argv[])
{
    // Initialize GTK+
    gtk_init(&argc, &argv);
    gdk_threads_init();

    GtkWidget *main_window;
    GdkWindow *gdk_window;
    createDrawContext(&main_window, &gdk_window);

    // Create a browser instance
    WebKitWebView *webView = WEBKIT_WEB_VIEW(webkit_web_view_new());

    // make sure the background of the main window is black plz
    GdkColor blaaack;
    gdk_color_parse("#000000", &blaaack);
    gtk_widget_modify_bg(main_window, GTK_STATE_NORMAL, &blaaack);

    // Put the browser area into the main window
    gtk_container_add(GTK_CONTAINER(main_window), GTK_WIDGET(webView));

    //hide the webview; we will handle showing it when we get the WEBKIT_LOAD_FINISHED notify
    gtk_widget_hide(GTK_WIDGET(webView));
    gtk_widget_show(main_window);

    // Set up callbacks so that if either the main window or the browser instance is
    // closed, the program will exit
    g_signal_connect(main_window, "destroy", G_CALLBACK(destroyWindow), NULL);
    g_signal_connect(main_window, "delete-event", G_CALLBACK(destroyWindow), NULL);

    // transparent background so we dont have any white flashes
    webkit_web_view_set_transparent(webView, true);

    int height;
    int width;
    gdk_window_get_geometry(gdk_window, NULL, NULL, &width, &height, NULL);
    if (height < 480 && width < 640) {
      // make the tiny preview windows look reasonable
      webkit_web_view_set_full_content_zoom(webView, true);
      webkit_web_view_set_zoom_level(webView, 0.4);
    }

    // set up some webkit settings
    WebKitWebSettings *settings = webkit_web_view_get_settings(webView);
    g_object_set (G_OBJECT(settings), "enable-webgl", true, NULL);
    // accelerated-compositing chokes on my machine, but maybe its my shitty nvidia drivers
    g_object_set (G_OBJECT(settings), "enable-accelerated-compositing", false, NULL);

    // select tag and format url
    wordexp_t exp_result;
    wordexp(CONFIG_PATH, &exp_result, 0);
    printf("Loading tags file at %s\n", exp_result.we_wordv[0]);
    char* tags_path = exp_result.we_wordv[0];
    char url[MAX_URL_LENGTH];
    char tags[MAX_NUMBER_TAGS][MAX_TAG_LENGTH];
    int  tags_length = 0;

    FILE* tags_file;
    if (tags_path == NULL || (tags_file = fopen(tags_path, "r")) == NULL) {
        printf("No tag file found. using defaults\n");
        int default_tags_length = sizeof(DEFAULT_TAGS) / sizeof(char*);
        for (int i = 0; i < default_tags_length; ++i) {
            printf("%d\n", i);
            strcpy(tags[i], DEFAULT_TAGS[i]);
        }
        tags_length = default_tags_length;
    } else {
        int i = 0;
        printf("Iterating through file\n");
        while (i < MAX_NUMBER_TAGS && fgets(tags[i], sizeof(tags[0]), tags_file)) {
            tags[i][strlen(tags[i]) - 1] = '\0';
            printf("Got %s!\n", tags[i]);
            ++i;
        }
        tags_length = i;
    }

    printf("%d tags found. selecting one.\n", tags_length);
    srand(time(0));
    int index = rand() % tags_length;
    printf("%d is our index...\n", index);
    printf("%s selected!\n", tags[index]);
    sprintf(url, URL_FORMAT, tags[index]);

    printf("Loading %s\n", url);
    webkit_web_view_load_uri(webView, url);

    // Make sure that when the browser area becomes visible, it will get mouse
    // and keyboard events
    gtk_widget_grab_focus(GTK_WIDGET(webView));
    // hit our callback whenever load-status changes
    g_signal_connect(G_OBJECT(webView), "notify::load-status", G_CALLBACK(load_status_cb), &url);

    // Run the main GTK+ event loop
    gtk_main();

    return 0;
}

