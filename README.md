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

## Usage

After building, the executable `wish` should appear in your project root directory. You can run this executable in two modes:

### Modes

1. **Interactive Mode**: Simply run `./wish` in the project root directory, to start the shell in interactive mode. The shell will process commands one by one based on your input in this mode.
2. **Batch Mode**: Use this mode if you have already have a list of commands that you want to execute written down in another script file. To start in batch mode type `./wish path/to/batch/file` in the project root directory.

### Inbuilt Commands

The shell provides three commands for managing the shell:

1. **cd**: `Usage: cd "path/to/dest/directory"` Like the original UNIX command `cd`, you can use this to change the current active directory of the shell.
2. **exit**: `Usage: exit` To stop the shell's execution, simply type `exit` without any arguments into the shell.
3. **path** `Usage: path [path1 | path2 | path3 | ...]` Similar to the original UNIX command `path`. Use this to edit the default command path for the shell to look for executables in. If left empty, `path` is set to `NULL` and you won't be able to execute any commands except the shell's inbuilt commands.


## Testing

Press `Ctrl+Shift+P`, type `CMake: Run Tests` and press enter.
