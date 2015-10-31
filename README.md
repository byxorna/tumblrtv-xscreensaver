# xscreensaver-tumblrtv

```
gcc -o tumblrtv tumblrtv.c -L/usr/lib -I/usr/include/gtk-3.0 -I/usr/include/glib-2.0 -lX11 -lgtk
```

http://www.dis.uniroma1.it/~liberato/screensaver/install.html

We consider as an example the module simplesquares.c. The steps needed to make it run are:
.) Compile the module. If it only uses Xlib functions (like the modules in this tutorial), this is:
```
gcc -o simplesquares simplesquares.c -L/usr/lib -lX11
```
.)In general, the directory to use in -Ldirectory is the one containing libX11.so, and can be found by:
```
find /usr -name libX11.so
```
.)The module can be tested by simply running it. The output goes in the root window, which is often visible as the "the background of the screen". Some window managers hide the root window with another window: in this case, the module can be tested by installing it as a screensaver module (see below)
.) Make sure that the executable is your path.
.) Add the module to the xscreensaver configuration file. This is done by creating a file .xscreensaver in your home directory. For a single module, this contains a line like:
```
programs: simplesquares
```
.) To test the module, use xscreensaver-demo (use the "preview" button)
