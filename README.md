# xscreensaver-tumblrtv

Build the thing:
```
$ make
```

Add a config to xscreensaver to make your screensaver work: (point this to your binary) in ~/.xscreensaver
```
...
programs:                     \
                        \
                                  /home/gconradi/code/xscreensaver-tumblrtv/tumblrtv \n\ 
...

```

Then run `xscreensaver-demo` and select your ish.

# TODO

[ ] how does no internet work? Can we render a different widget if it doesnt have connection?
[x] zoom browser if too small
[x] load tags and users from config file
[ ] multi monitor support?
[ ] package this up for lots of distros
[ ] turn off chatter from webkit stdout
[ ] Document the file to edit which tags show up in postinstall
[ ] Document how to configure xscreensaver for this screenie

# Install

There is an AUR build available: https://aur.archlinux.org/packages/tumblrtv-xscreensaver/

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
