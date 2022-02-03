SKSE Plugin Component Piping Papyrus Log Output to joels papyrus plugin

This is 10000% Scuffed do not use.

This SKSE dll pipes papyrus debug output to VSCode debug window.

The log viewer portion of https://github.com/joelday/papyrus-debug-server

Dont think its been updated to work with AE so here we are.

Integrates with https://github.com/joelday/papyrus-lang


To lazy to properly submit build system so you just get raw source.

I gave up trying to use an actually DAP so just manually pipe the log output to the websocket server :/


## Requirements
* [CMake](https://cmake.org/)
	* Add this to your `PATH`
* [The Elder Scrolls V: Skyrim Special Edition](https://store.steampowered.com/app/489830)
	* Add the environment variable `Skyrim64Path` to point to the root installation of your game directory (the one containing `SkyrimSE.exe`).
* [Vcpkg](https://github.com/microsoft/vcpkg)
	* Add the environment variable `VCPKG_ROOT` with the value as the path to the folder containing vcpkg
* [Visual Studio Community 2022](https://visualstudio.microsoft.com/)
	* Desktop development with C++

## Building
```
git submodule init
git submodule update
cmake --preset vs2022-windows
cmake --build build --config Release
```