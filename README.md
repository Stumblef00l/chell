# wish
A simplified version of the UNIX shell.

## Requirements

1. A gcc version which supports C++17. **gcc-9** recommended.

```bash
sudo apt get install gcc-9 g++-9
```
2. CMake version 3.20 and above: Download from [here](https://cmake.org/download/) and follow the instructions to install
3. googletest for testing. This will be downloaded automatically while building.

## Building

It is recommended you use VSCode as your code editor and install the CMake and the CMake tools externsion. The following steps detail how to build the project in CMake.

1. Press `Ctrl+Shift+P`, type `CMake: Set Built Target` and set this to 'all'
2. Press `Ctrl+Shift+P`, type `CMake: Configure` and press enter.
3. Finally, press `Ctrl+Shift+P`, type `CMake: Build` and press enter.

## Testing

Press `Ctrl+Shift+P`, type `CMake: Run tests` and press enter.
