# Monitor Arrangement

A small Qt Widgets application that visualizes connected displays in their relative desktop positions. Displays to the left or above the primary screen retain their negative coordinates; the whole layout scales to fit the window.

The primary display is highlighted. Geometry refreshes at startup, when screens are added or removed, and when their geometry changes. **Refresh displays** requests another snapshot. The application reads display information and does not change monitor settings.

## Build

Requires a C++17 compiler, CMake 3.16+, and a matching desktop Qt 5.15 or Qt 6 Widgets kit. Open the root `CMakeLists.txt` in Qt Creator and select that kit, or use:

```sh
cmake -S . -B build -DCMAKE_PREFIX_PATH="path/to/Qt/6.x/compiler_kit"
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

Run `build/monitor-arrangement` (or `build/Release/monitor-arrangement.exe` with a multi-configuration Windows generator). Qt's runtime libraries and platform plugins must be available; running through Qt Creator supplies the kit environment. For distributing a Windows build, use the matching kit's [windeployqt](https://doc.qt.io/qt-6/windows-deployment.html).

## Code map

| File | Responsibility |
| --- | --- |
| [main.cpp](src/main.cpp) | Application entry point and hidden rendering check |
| [mainwindow.cpp](src/mainwindow.cpp) | Window, explanatory text and refresh button |
| [monitorarrangementwidget.cpp](src/monitorarrangementwidget.cpp) | Screen discovery, notifications and painting |
| [monitorlayout.h](src/monitorlayout.h) | Shared translation and scale for all monitor rectangles |
| [layout_tests.cpp](tests/layout_tests.cpp) | Negative origins, adjacency, aspect ratio and invalid geometry |

Display information comes from [QScreen](https://doc.qt.io/qt-6/qscreen.html). Sizes are **Qt logical coordinates**, not necessarily physical pixel resolution. Mixed-DPI desktops can contain gaps in Qt's coordinate space, which this viewer preserves. Very small display rectangles may clip their labels.

## Validation and history

Built with Qt 6.8.3 and MinGW-w64 on Windows. Geometry tests and the offscreen `--check` rendering check pass. Qt 5, Linux/macOS, hot-plugging and mixed-DPI hardware have not been exercised locally.

The original Qt Creator project was named `untitled3`. Sources now live in `src/`; generated binaries, caches and user-specific kit settings are excluded. [Qt.PNG](Qt.PNG) is a historical screenshot of the earlier interface.

MIT license; see [LICENSE](LICENSE).
