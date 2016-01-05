# xscreensaver-tumblrtv

xscreensaver to display Tumblr TV (https://tumblr.com/tv/trippy)

# Build and Install

There is an AUR build available if you are on Arch: https://aur.archlinux.org/packages/tumblrtv-xscreensaver/

You will need:
* webkitgtk2 (provides webkitgtk-1.0)
* gtk2
* xscreensaver

Build the thing:
```
$ make
$ sudo make install
```

The install drops the `tumblrtv` binary into `/usr/lib/xscreensaver`. Alternatively, you can run the `./tumblrtv` binary standalone.

# Configure

Run `xscreensaver-demo`, and it will generate a `~/.xscreensaver` config for you if you didnt have one before. Now, add a config to xscreensaver to make your screensaver work: (point this to your binary) in ~/.xscreensaver.

```
...
programs:                     \
    tumblrtv \n\
...

```

Then run `xscreensaver-demo` and select `tumblrtv`.


`tumblrtv` uses a config file in `~/.config/tumblrtv-xscreensaver/tags`, which is newline delimited tags to display. A random tag will be chosen from the file each time the screensaver launches. By default, it will pick from a set of tags.

Example `~/.config/tumblrtv-xscreensaver/tags`:
```
@computersarerad
lsd
cyberpunk
```

# TODO

* [ ] multi monitor support?
* [ ] package this up for lots of distros
* [ ] turn off chatter from webkit stdout
* [ ] gif rendering looks pixelated. Is there a smoothing option?
* [ ] Document the file to edit which tags show up in postinstall
* [x] Document how to configure xscreensaver for this screenie
* [x] how does no internet work? (very poorly!) Can we render a different widget if it doesnt have connection?
* [x] zoom browser if too small
* [x] load tags and users from config file

# License

Copyright 2016 Gabe Conradi

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
