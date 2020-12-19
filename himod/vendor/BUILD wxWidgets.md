# Build wxWidgets

Building wxWidgets is going to take some time.

## Windows

- Go to `build/msw/` and open the correct `wx_vc<version>.sln` solution file. For example `wx_vc16.sln` is for Visual Studio 2019.
- Select all projects in solution (except `_custom_build`). Go into Properties. Under `Configuration Properties`/`C/C++`/`Code Generation`. Then change the `Runtime Library` option to the non-DLL version (For Debug change `Multi-threaded Debug DLL` to `Multi-threaded Debug`, and same for Release except without Debug).
- Right-click solution and click `Batch Build...`. Select all projects except for where `Solution Config` is `DLL`
- Then click `Build`

## Linux

- cd into `himod/vendor/wxWidgets`
- `mkdir build_gtk`
- `cd build_gtk`
- `../configure --with-gtk`
- `make -j<number>` where `<number>` is how many logical cores you want to use for building.
