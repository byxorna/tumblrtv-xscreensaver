#include<stdlib.h>
#include<X11/Xlib.h>
#include<gdk/gdk.h>
#include<glib/glib.h>

#include "vroot.h"

main ()
{
  Display *dpy;
  Window root;
  XWindowAttributes wa;
  /* graphics context */
  GC g;
  /* gdk display */
  GdkDisplay gdk_display;


  /* open the display (connect to the X server) */
  dpy = XOpenDisplay (getenv ("DISPLAY"));


  /* get the root window */
  root = DefaultRootWindow (dpy);

  // for things like window size, etc
  XGetWindowAttributes(dpy, root, &wa);


  /* create a GC for drawing in the window */
  g = XCreateGC (dpy, root, 0, NULL);


  // https://developer.gnome.org/gdk3/stable/gdk3-X-Window-System-Interaction.html#gdk-x11-window-foreign-new-for-display
  gdk_x11_window_foreign_new_for_display(gdk_display, root);

  /* set foreground color */
  XSetForeground(dpy, g, WhitePixelOfScreen(DefaultScreenOfDisplay(dpy)) );


  /* draw something */
  while (1)
    {
      /* draw a square */
      XFillRectangle (dpy, root, g, random()%500, random()%500, 50, 40);


      /* once in a while, clear all */
      if( random()%500<1 )
        XClearWindow(dpy, root);


      /* flush changes and sleep */
      XFlush(dpy);
      usleep (10);
    }


  XCloseDisplay (dpy);
}
