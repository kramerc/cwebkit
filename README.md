# CWebKit
A library written in C that uses the GTK+ WebKit bindings for building web applications towards the desktop.

CWebKit is currently in alpha.

## Features
* `app://` scheme for easy reference to other application pages.
* Ability to implement JavaScript methods with C.

## Compiling
Ensure you have the development libraries of [GTK+](http://www.gtk.org/) 3.0 and [WebKit/Gtk+](https://live.gnome.org/WebKitGtk) and then simply run `make`.

On Ubuntu, the following will install these:

```
sudo apt-get install libgtk-3-dev libwebkitgtk-3.0-dev
```

## Demonstration
Check out the `tester/` directory for an example implementation of the library.

### Compiling
Ensure you have compiled CWebKit first, then run `make` within the `tester/` directory.

### Running
In order to run the demonstration, you will need to modify the library path. This can be done temporarily by using the following within the `tester/` directory:

```
LD_LIBRARY_PATH=../bin/:$LD_LIBRARY_PATH bin/tester
```

## License
Copyright (c) 2013 Kramer Campbell, released under the MIT license.