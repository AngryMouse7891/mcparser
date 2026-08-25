cmake_minimum_required(VERSION 3.10)

project(MCParser
  VERSION 1.4.6
  DESCRIPTION "一个一个一个一个一个一个一个一个一个一个一个一个一个解析Minecraft社区资源（如模组）的工具，部分由AI赋能。"
  HOMEPAGE_URL "https://www.mcbbs.co/thread-5638-1-1.html"
)

set(SOURCE_DIR src)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MCPARSER_LINUX_BUNDLE OFF CACHE BOOL "启用Linux动态库打包")

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
string(TIMESTAMP BUILD_TIME_NORMAL "%Y/%m/%d %H:%M:%S")

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

# 选项：是否开启文档构建，默认OFF，按需打开
option(MCPARSER_BUILD_DOCS "Build documentation with MkDocs" OFF)

if(MCPARSER_BUILD_DOCS)
    find_program(MKDOCS_EXECUTABLE
            NAMES mkdocs
            DOC "MkDocs static site generator"
    )

    if(NOT MKDOCS_EXECUTABLE)
        message(FATAL_ERROR "BUILD_DOCS is ON but mkdocs was not found!")
    endif()

    # 文档输出路径：构建目录下 docs/site
    set(MKDOCS_OUTPUT_DIR "${CMAKE_BINARY_DIR}/site")

    add_custom_target(docs
            COMMAND ${MKDOCS_EXECUTABLE} build
                    -d ${MKDOCS_OUTPUT_DIR}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
            COMMENT "Building MkDocs documentation -> ${MKDOCS_OUTPUT_DIR}"
            VERBATIM
    )

    # 安装规则
    install(DIRECTORY ${MKDOCS_OUTPUT_DIR}/
            DESTINATION "share/doc/mcparser"
            COMPONENT docs
    )
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
)

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  # 给mcparser目标添加O2优化，跨平台兼容
  target_compile_options(mcparser PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/O2>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-O2>
  )
else()
  target_compile_options(mcparser PRIVATE
    $<$<CXX_COMPILER_ID:MSVC>:/DEBUG>
    $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-g>
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

# rpm包配置字段
set(CPACK_RPM_PACKAGE_NAME "mcparser")
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_RPM_PACKAGE_SUMMARY "A toolkit that can parse Minecraft community resources (such as mods)")
set(CPACK_RPM_PACKAGE_RELEASE 1)
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "games")
set(CPACK_RPM_PACKAGE_REQUIRES "libjsoncpp27 >= 1.0.0, libfmt12, libcurl4 >= 8.0.0, libopenssl3, ca-certificates")
set(CPACK_RPM_PACKAGE_DESCRIPTION "一个解析Minecraft社区资源的软件")
set(CPACK_RPM_CHANGELOG_FILE ${CMAKE_SOURCE_DIR}/CHANGELOG)

# set the install/uninstall icon used for the installer itself
set (CPACK_NSIS_MUI_ICON "${CMAKE_SOURCE_DIR}/data/installer_icon.ico")
set (CPACK_NSIS_MUI_UNIICON "${CMAKE_SOURCE_DIR}/data/uninst_icon.ico")
set (CPACK_PACKAGE_ICON
     "${CMAKE_SOURCE_DIR}/data/install.bmp")

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Windows")
  set(CPACK_GENERATOR "NSIS;ZIP")
else()
  set(CPACK_GENERATOR "TGZ")
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
install(FILES LICENSE DESTINATION share/licenses/mcparser)
install(FILES data/mcparser.png DESTINATION share/icons/hicolor/256x256/apps)
install(FILES data/256x256@2x/mcparser.png DESTINATION share/icons/hicolor/256x256@2x/apps)
install(FILES data/MCParser.desktop DESTINATION share/applications)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  install(FILES mcparser.exe.manifest DESTINATION bin)
endif()

include(BundleUtilities)
# 1. 设置安装目录根路径（CMAKE_INSTALL_PREFIX）
set(BU_COPY_TO_INSTALL ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(MCPARSER_LINUX_BUNDLE)
    # 使用独立的cmake脚本收集依赖库
    install(SCRIPT "${CMAKE_SOURCE_DIR}/cmake/collect_linux_deps.cmake")

    # 构建阶段rpath
    set(CMAKE_BUILD_RPATH "$ORIGIN/../lib")
    # 安装阶段rpath
    set(CMAKE_INSTALL_RPATH "$ORIGIN/../lib")
    set(CMAKE_INSTALL_RPATH_USE_LINK_PATH ON)
  endif()
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

set (CPACK_PACKAGE_EXECUTABLES "mcparser;MCParser" )
# NSIS 默认安装路径
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "MCParser")
# 桌面快捷方式
set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '$DESKTOP/MCParser.lnk' '$INSTDIR/bin/mcparser.exe'")
# 开始菜单名称
set(CPACK_NSIS_PACKAGE_NAME "MCParser")

set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1-6), libc6 (< 2.4)")

include(CPack)
