## Build & Run Instructions (Windows / MinGW)

### Requirements
- Qt 6.10+ (MinGW build)
- CMake 3.21+
- Ninja
- MinGW toolchain (matching Qt)
- Windows

---

### Step 1: Configure the build (Debug recommended for development)

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
```
### Step 2: Build the executable
cmake --build build

### Step 3: Run the application
./build/gui/NeedSpeedRead.exe

### Step 4: Deploy Qt runtime libraries (required once)

# After the first successful build, deploy the required Qt DLLs:

C:\Qt\6.10.2\mingw_64\bin\windeployqt.exe build\gui\NeedSpeedRead.exe

# Release Build
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release


# Release build Cmake lists file:
# Release Build
"""find_package(Qt6 REQUIRED COMPONENTS Quick) 

qt_standard_project_setup()

qt_add_executable(NeedSpeedRead
    main.cpp
)

qt_add_qml_module(NeedSpeedRead
    URI NeedSpeedRead #was DocViewer
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

target_link_libraries(NeedSpeedRead
    PRIVATE
        Qt6::Quick
        backend
)
"""

