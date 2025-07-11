# Minesweeper Game

This project is inspired by the popular logic game [Minesweeper](https://en.wikipedia.org/wiki/Minesweeper_(video_game)). The goal was not to create an exact copy, but rather a variation of the game. The project is implemented in C++ using the QT graphical framework, which enables an interactive and visually friendly interface.

## Game Description

The game starts by creating a playing field of specific dimensions, where mines are distributed according to the chosen difficulty level. The dimensions of the game field and its complexity are set by the user in a dialog window at the start of the game.

![](media/setting.png)

During the game, the player clicks on tiles in the playing field. Clicking on an empty tile opens it, and if the neighboring tiles do not contain a mine, they are automatically opened as well. Tiles adjacent to mines display a number indicating the number of mines nearby, with neighboring tiles including those in diagonal directions.

However, the search for safe tiles is limited only to those that share a full edge (not just a corner) with an already opened tile.

The player can use the Ctrl key in combination with clicking on a tile to mark a tile where they suspect a mine. Such a marked tile is highlighted in yellow.

![Alt text](media/field.png)

If the player clicks on a tile with a mine, a warning message appears and the action is recorded as a wrong move.

![Alt text](media/end.png)

## Solution Description

The game solution uses the QT graphical framework, which, in addition to graphical components, provides other tools. From the QT framework, signals and slots, the runtime environment, and QT widget attributes were used to transfer game state information. QT Dialogs are also used for the initial settings menu and for the "stepped on a mine" warning dialog.

### Graphical Interface

QT widgets are used to create a clear and user-friendly interface. This includes buttons for game controls, dialog windows for settings, and notifications for players about the game progress.

### Game Logic

The playing field is generated with mines placed randomly. The number of mines around "opened" fields is calculated in real-time after opening them. It would be possible to precompute these values, but given the high performance of modern computers, this is not necessary. I implemented the logic for revealing neighboring tiles and detecting the end of the game when a player clicks on a mine.

### Interaction and Features

The game uses QT signals and slots to effectively respond to user actions such as clicking on a tile or selecting game settings. The code is designed with readability in mind, which makes it easier to extend in the future.

## Compilation

The program was developed on Linux (Ubuntu 22.04). It is assumed that the QT6 framework is installed: `sudo apt install qt6-base-dev`.

Next, you need to run the `cmake .` and `make` commands in the source code directory.

The output should look approximately as follows:

```bash
 $ cmake .
-- The CXX compiler identification is GNU 11.4.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/c++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD
-- Performing Test CMAKE_HAVE_LIBC_PTHREAD - Success
-- Found Threads: TRUE  
-- Performing Test HAVE_STDATOMIC
-- Performing Test HAVE_STDATOMIC - Success
-- Found WrapAtomic: TRUE  
-- Found OpenGL: /usr/lib/x86_64-linux-gnu/libOpenGL.so   
-- Found WrapOpenGL: TRUE  
-- Found XKB: /usr/lib/x86_64-linux-gnu/libxkbcommon.so (found suitable version "1.4.0", minimum required is "0.5.0") 
-- Found WrapVulkanHeaders: /usr/include  
-- Configuring done
-- Generating done
-- Build files have been written to: /home/****/Miny


 $ make 
[ 20%] Automatic MOC and UIC for target Miny
[ 20%] Built target Miny_autogen
[ 40%] Building CXX object CMakeFiles/Miny.dir/Miny_autogen/mocs_compilation.cpp.o
[ 60%] Building CXX object CMakeFiles/Miny.dir/main.cpp.o
[ 80%] Building CXX object CMakeFiles/Miny.dir/minywindow.cpp.o
[100%] Linking CXX executable Miny
[100%] Built target Miny

````

Now, in the same folder, you should have the executable file `Miny`.

Run the game with the command `./Miny`.

> The repository contains the binary `Miny`, which was compiled for Linux, x86\_64.
