# Shutil
Shutil (SHU uTILities) is a portable, cross platform programming utility library.

It uses the [SHU](https://github.com/omerfuyar/shu) system. By defining `SHU` you can tell the library where to find `shu.h` or include it yourself  before any shu... library to prevent any complication. See [SHU](https://github.com/omerfuyar/shu) repo for more information.

Goal is to use most common data structures with a united, easy interface.

# Usage
You can pick which data structures or algorithms you will use by defining corresponding `SHUTIL_<...>` macro. Or use the `SHUTIL_ALL` macro for everything that the library provides. See first lines of the header for more information.