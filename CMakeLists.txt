cmake_minimum_required(VERSION 3.10)

project(MCParser VERSION 1.3.10)

set(SOURCE_DIR src)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_HOMEPAGE_URL "https://gitee.com/AngryMouse7891/mcparser/")

message(STATUS "CMake版本: ${CMAKE_VERSION}")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "正在以发布模式构建")
else()
  message(STATUS "正在以调试模式构建")
endif()

# 查找依赖
find_package(PkgConfig REQUIRED)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
pkg_check_modules(FMT REQUIRED fmt)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

# 获取当前时间戳，格式为 YYYYMMDD_HHMMSS
string(TIMESTAMP CURRENT_TIMESTAMP "%Y%m%d_%H%M%S")

find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --short HEAD
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    execute_process(
        COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
else()
    set(GIT_COMMIT_HASH "unknown")
    set(GIT_BRANCH "no-git")
endif()

# 将时间戳存储到变量中
set(BUILD_TIME ${CURRENT_TIMESTAMP})

# 创建版本头文件
configure_file(
  "${CMAKE_SOURCE_DIR}/version.h.in"
  "${CMAKE_BINARY_DIR}/version.h"
)

aux_source_directory(${CMAKE_SOURCE_DIR}/src SRC_FILES)

# 添加到包含目录
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OPENSSL_INCLUDE_DIR})
include_directories(${JSONCPP_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(src/include)

add_executable(mcparser ${SRC_FILES} resources.rc)

target_link_libraries(
  mcparser 
  PRIVATE
  OpenSSL::SSL OpenSSL::Crypto 
  ${JSONCPP_LIBRARIES} 
  ${CURL_LIBRARIES} 
  ${FMT_LIBRARIES} 
  ${CMAKE_BINARY_DIR} 
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  # 给mcparser目标添加O2优化，跨平台兼容
  target_compile_options(mcparser PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/O2>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2>
  )
endif()


file(COPY "${CMAKE_SOURCE_DIR}/src/cacert.pem"
     DESTINATION ${CMAKE_BINARY_DIR}/)

set(CPACK_PACKAGE_NAME "MCParser")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "一个解析MC社区资源的软件")
set(CPACK_PACKAGE_VENDOR "AngryMouse7891")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://www.luogu.com.cn/user/1342923")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "AngryMouse7891 <pystart@qq.com>")
set(CPACK_IFW_ARCHIVE_COMPRESSION "5")
set(CPACK_IFW_PACKAGE_WIZARD_STYLE "Modern")

# set the install/uninstall icon used for the installer itself
set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/data/uninst_icon.ico")
set (CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/data/installer_icon.ico")
set (CPACK_PACKAGE_ICON
     "${CMake_SOURCE_DIR}/data/install.bmp")

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  set(CPACK_GENERATOR "NSIS;ZIP")
else()
  set(CPACK_GENERATOR "TGZ;IFW")
endif ()

# 编译目标 mcparser 安装到系统 bin 目录
install(TARGETS mcparser
  RUNTIME DESTINATION bin       # 可执行文件路径
  LIBRARY DESTINATION lib       # 动态库路径
  ARCHIVE DESTINATION lib       # 静态库路径
)

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  install(FILES ${CMAKE_BINARY_DIR}/cacert.pem DESTINATION bin/)
endif ()
install(FILES LICENSE README.md BUILD.md CHANGELOG DESTINATION share/MCParser)
install(DIRECTORY screenshots/ DESTINATION share/MCParser/screenshots)
install(DIRECTORY images/ DESTINATION share/MCParser/images)
install(FILES data/mcparser.png DESTINATION share/icons/hicolor/256x256/apps)
install(FILES data/256x256@2x/mcparser.png DESTINATION share/icons/hicolor/256x256@2x/apps)
install(FILES data/MCParser.desktop DESTINATION share/applications)
install(FILES "data/installer_icon.ico"
    DESTINATION "data"
)

include(BundleUtilities)
# 1. 设置安装目录根路径（CMAKE_INSTALL_PREFIX）
set(BU_COPY_TO_INSTALL ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  # 在脚本模式执行依赖拷贝，需要生成一个 .cmake 脚本，安装结束自动运行
  install(CODE "
    include(BundleUtilities)
    message(STATUS \"开始收集动态库...\")
    file(GLOB EXE_LIST \"\${CMAKE_INSTALL_PREFIX}/bin/mcparser\")
    foreach(exe \${EXE_LIST})
      fixup_bundle(\"\${exe}\" \"\" \"\" COPY_REQUIRED_FILES)
    endforeach()
  ")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # 在脚本模式执行依赖拷贝，需要生成一个 .cmake 脚本，安装结束自动运行
  install(CODE "
    include(BundleUtilities)
    message(STATUS \"开始收集依赖DLL...\")
    file(GLOB EXE_LIST \"\${CMAKE_INSTALL_PREFIX}/bin/*.exe\")
    foreach(exe \${EXE_LIST})
      fixup_bundle(\"\${exe}\" \"\" \"\" COPY_REQUIRED_FILES)
    endforeach()
  ")
endif()

set(CPACK_PACKAGE_FILE_NAME 
  "${CMAKE_PROJECT_NAME}_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}_${BUILD_TIME}_${CPACK_PACKAGE_VERSION}"
)

# 包含许可证文件（可选）
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

# 包含 Readme 文件（可选）
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# NSIS 默认安装路径
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MCParser")
# 桌面快捷方式
set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '$DESKTOP/MCParser.lnk' '$INSTDIR/bin/mcparser.exe'")
# 开始菜单名称
set(CPACK_NSIS_PACKAGE_NAME "MCParser")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libc6 (< 2.4)")

include(CPack)