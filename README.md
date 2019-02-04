# ViewAndCompress

The program which works with the [Draco](https://github.com/google/draco) library
You can compress or decompress 3D models and displaying them.

**If you want to build this project you should:**
<ul>
    <li>install Conan Package Manager;</li>
    <li>install CMake;</li>
    <li>install GCC which support C++14 (for the Linux) or install Visual Studio 2017 (or 2015)(for the Windows).</li>
</ul>
You also must add remote repository of the conan package:

    conan remote add ableigdev https://api.bintray.com/conan/ableigdev/public-conan
    
# How to build?

You can use the next instruction:

    mkdir build && cd build
    conan install ..
    cmake ..
    cmake --build .