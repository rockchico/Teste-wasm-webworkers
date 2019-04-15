# Teste-wasm-webworkers

# Build with ninja
https://www.opengeosys.org/docs/devguide/advanced/build-with-ninja/


cmake . -GNinja -DCMAKE_TOOLCHAIN_FILE=/home/francisco/emsdk/emscripten/1.38.30/cmake/Modules/Platform/Emscripten.cmake
ninja

# instaler ccmake
sudo apt-get install cmake-curses-gui