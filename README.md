# Fun with TIGR
A bunch of small programs to demonstrate what you can do with TIGR, the TIny
GRaphics library

## Building a fun program
TIGR is cross platform, but you will need to link the correct libraries
based on your host operating system.  For the sake of these examples, I'm
using GCC/G++, although the same options worked with Clang/Clang++ at the
time this was written.

Since each fun TIGR program is written in only one source file, these can be
compiled with tigr.c very easily.  Keep in mind that linking flags differ
by host operating system.

| **Host Operating System** | **Link with...** |
| :---: | :--- |
| Windows | `-lopengl32 and -lgdi32` |
| macOS | `-framework OpenGL and -framework Cocoa` |
| Linux<sup>*</sup> | `-lGLU -lGL -lX11` |

<sup>*</sup> For Linux/Ubuntu users, you'll need to install the X11 and
MESA-based utility library files... `sudo apt install libx11-dev
libglu1-mesa-dev`

### An example build

As an example, if I were building the simplest fun TIGR program,
00_hello_window.c, using GCC on my Ubuntu Linux system...

```gcc -o 00_hello_window 00_hello_window.c tigr.c -lGLU -lGL -lX11```

## License
This source code is licensed under the MIT license found in the
[LICENSE](LICENSE) file in the root directory of this source tree.
