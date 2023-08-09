# windows部署
## Visual Studio 2022 Community
### 下载
https://visualstudio.microsoft.com/zh-hans/vs/
### 安装
额外添加英文语言包
## opencv4.4
### 下载
https://sourceforge.net/projects/opencvlibrary/files/4.4.0/opencv-4.4.0-vc14_vc15.exe/download
### 配置
https://cloud.tencent.com/developer/article/1756195

## git
### 下载
https://git-scm.com/downloads

## vcpkg
### 教程
https://blog.csdn.net/qq_41023270/article/details/109274433
https://zhuanlan.zhihu.com/p/87391067

```shell
mkdir vcpkg
cd vcpkg
git clone https://github.com/Microsoft/vcpkg
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```

## eigen
### 安装
```shell
.\vcpkg install eigen3:x64-windows
```

## boost
### 安装
```shell
.\vcpkg install boost:x64-windows
```

## g2o
### 修改
需要在CMakeLists.txt中补充 （详见git commit）
```cmake
SET(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
add_definitions(-DWINDOWS)
```
### 编译
使用cmake_gui

1. 设置源代码路径
2. 设置编译路径
3. Configure
4. Generate
5. Open Project

使用Visual Studio，ALL_BUILD->生成
- Right click on g2o project -> Properties -> General -> Target Extension: .lib, and Configure Type: Static Library (.lib)  
- Build ALL_BUILD. Finish(g2o.lib).
### 操作参考
https://www.jianshu.com/p/2e9533f0898e

## DBoW2
### 修改
- 需要在CMakeLists.txt中补充 （详见git commit）
```cmake
SET(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
add_definitions(-DWINDOWS)
list(APPEND CMAKE_PREFIX_PATH D:\\opencv4.4\\opencv\\build\\x64\\vc15\\lib)
```
- 修改DBoW2\DBoW2\FORB.cpp
```diff
-#include <stdint-gcc.h>
+#ifdef WINDOWS
+    #include <stdint.h>
+#else
+    #include <stdint-gcc.h>
+#endif
```
### 编译
使用cmake_gui

1. 设置源代码路径
2. 设置编译路径
3. Configure
4. Generate
5. Open Project

使用Visual Studio，ALL_BUILD->生成
- Right click on DBoW2 project -> Properties -> General -> Target Extension: .lib, and Configure Type: Static Library (.lib)  
- Build ALL_BUILD. Finish(DBoW2.lib).
## Sophus
### 修改
- 需要在CMakeLists.txt中补充 （详见git commit）
```cmake
SET(CMAKE_TOOLCHAIN_FILE "D:/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake")
add_definitions(-DWINDOWS)
```
- 修改CMakeLists.txt
```diff
-FIND_PACKAGE(Eigen3 3.1.0 REQUIRED)
+set(Eigen3_DIR "D:/vcpkg/vcpkg/installed/x64-windows/share/eigen3")
```
### 编译
使用cmake_gui

1. 设置源代码路径
2. 设置编译路径
3. Configure
4. Generate
5. Open Project

使用Visual Studio，ALL_BUILD->生成
## Pangolin
忽略pthread.lib缺失的错误
### 编译
使用cmake_gui

1. 设置源代码路径
2. 设置编译路径
3. Configure
4. Generate
5. Open Project

使用Visual Studio，ALL_BUILD->生成
## PANG_SLAM
### 修改
- 修改CMakeLists.txt（详见git commit）
```diff
+add_definitions(-DWINDOWS)
+list(APPEND CMAKE_PREFIX_PATH D:\\opencv4.4\\opencv\\build\\x64\\vc15\\lib)

-include(CheckCXXCompilerFlag)
-CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
-CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
-if(COMPILER_SUPPORTS_CXX11)
-   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
-   add_definitions(-DCOMPILEDWITHC11)
-   message(STATUS "Using flag -std=c++11.")
-elseif(COMPILER_SUPPORTS_CXX0X)
-   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
-   add_definitions(-DCOMPILEDWITHC0X)
-   message(STATUS "Using flag -std=c++0x.")
-else()
-   message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
-endif()
+set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
+add_definitions(-DCOMPILEDWITHC11)
+message(STATUS "Using flag -std=c++11.")

+set(Eigen3_DIR "D:/vcpkg/vcpkg/installed/x64-windows/share/eigen3")
-find_package(Eigen3 3.1.0 REQUIRED)
```

### 编译
使用cmake_gui

1. 设置源代码路径
2. 设置编译路径
3. Configure
4. Generate
5. Open Project

使用Visual Studio，ALL_BUILD->生成
- Right click on ORB-SLAM3 project -> Properties -> General -> Target Extension: .lib, and Configure Type: Static Library (.lib)  