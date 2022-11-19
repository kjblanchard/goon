# Goon Engine

A engine built in Cpp, that you can create a game with lua scripts.  Trying to learn a bit more about cpp, 3d programming/opengl, and multi platform engine building.  Thanks to @Cherno for insight.
- Mostly developed on macos apple silicon
- Using minimal IDE, 100% vim and lldb for debugging.
- Tracking the project in github projects

## License

All of the licenses that I'm using will be listed here.

### Libraries
- [glfw](https://www.glfw.org/license.html) - ZLIB
- [ImGui](https://github.com/ocornut/imgui/blob/master/LICENSE.txt) - MIT
- [doxygen](https://doxygen.nl) - GPL
- [openalsoft](https://github.com/kcat/openal-soft/blob/master/COPYING) - LGPLv2


## Acknowledgements
- **[TheCherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw)** - For the great C++, and opengl tutorials for self taught!
- **Make** - Used to run simple commands easily
- **CMake** - Build system, for cross-platform building.
- **OpenAl** - original open source audo library
- **[Audacity](https://www.audacityteam.org)** - Music edits

## Building
- All dependencies are in the external folder, and if you need any of them, pull the submodule and build/install them with 
- - git submodule update --init --recursive
- Only tested with clang currently on macos/windows/linux.  Windows sets prefix to c/cmake, so make sure when you install your libs to put them there, or change the prefix path in cmake

## Authors

- [@Kevin Blanchard](https://www.github.com/kjblanchard)
