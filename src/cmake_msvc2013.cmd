mkdir build\msvc2013-x86
pushd build\msvc2013-x86
cmake -G "Visual Studio 12 2013" %* ../..
popd