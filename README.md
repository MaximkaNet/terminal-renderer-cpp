# Text based renderer

## Installation using CMake

```
add_executable(<app_name> <source files ...>)

include(FetchContent)

FetchContent_Declare(
  tren
  GIT_REPOSITORY https://github.com/MaximkaNet/terminal-renderer-cpp.git
  GIT_TAG        main
)

FetchContent_MakeAvailable(tren)

target_link_libraries(<app_name> PRIVATE tren)
```

## Using
Initialize Terminal Renderer
```
tren::init();
// or
// tren::init(width, height);
```

Define text
```cpp
tren::TextDef textDef;
textDef.content = "Hello terminal renderer (tren)";

tren::drawText(textDef);
```

Refresh screen
```cpp
tren::refresh();
```

Close Terminal renderer
```cpp
tren::endwin();
```