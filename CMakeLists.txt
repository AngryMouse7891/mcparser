cmake_minimum_required(VERSION 3.10)

project(MCParser VERSION 1.0.0)

set(SOURCE_DIR src)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(SRC_WINRC ${CMAKE_CURRENT_SOURCE_DIR}/resources.rc)
#set(JSONCPP_INCLUDE_DIRS "/ucrt64/include/json")
#set(JSONCPP_LIBRARIES "/ucrt64/lib/libjsoncpp.a")

#message(STATUS "JSONCPP_LIBRARIES: ${JSONCPP_LIBRARIES}")

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  message(STATUS "正在以发布模式构建")
else()
  message(STATUS "正在以调试模式构建")
endif()

#add_definitions(-DJSON_DLL)

# 查找 json-cpp
#find_package(JsonCpp REQUIRED)
find_package(fmt REQUIRED)
find_package(PkgConfig REQUIRED)
#pkg_check_modules(LIBARIA2 REQUIRED libaria2)
pkg_check_modules(JSONCPP REQUIRED jsoncpp)
find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)

# 获取当前时间戳，格式为 YYYYMMDD_HHMMSS
string(TIMESTAMP CURRENT_TIMESTAMP "%Y%m%d_%H%M%S")

# 将时间戳存储到变量中
set(BUILD_TIME ${CURRENT_TIMESTAMP})

#add_custom_command(
#  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/resources.res
#  COMMAND windres -i ${SRC_WINRC} -o ${CMAKE_CURRENT_BINARY_DIR}/resources.res
#  DEPENDS ${SRC_WINRC}
#)

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
#include_directories(${LIBARIA2_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(src/include)

add_executable(mcparser ${SRC_FILES} resources.rc)

target_link_libraries(
  mcparser 
  PRIVATE
  OpenSSL::SSL OpenSSL::Crypto 
  ${JSONCPP_LIBRARIES} 
  ${CURL_LIBRARIES} 
  fmt::fmt 
  ${CMAKE_BINARY_DIR} 
)

set(CPACK_PACKAGE_NAME "MCParser")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "一个解析MC社区资源的软件")
set(CPACK_PACKAGE_VENDOR "AngryMouse7891")
set(CPACK_PACKAGE_LICENSE "MIT")
set(CPACK_PACKAGE_HOMEPAGE_URL "https://www.luogu.com.cn/user/1342923")
set(CPACK_GENERATOR "NSIS;ZIP")

# 编译目标 MyExecutable 安装到系统 bin 目录
install(TARGETS mcparser
  RUNTIME DESTINATION bin       # 可执行文件路径
  LIBRARY DESTINATION lib       # 动态库路径
  ARCHIVE DESTINATION lib       # 静态库路径
)
install(FILES LICENSE README.md DESTINATION share/MCParser)
install(DIRECTORY screenshots/ DESTINATION share/MCParser/screenshots)
install(FILES data/mcparser.png DESTINATION share/icons/hicolor/256x256/apps)
install(FILES data/MCParser.desktop DESTINATION share/applications)

set(CPACK_PACKAGE_FILE_NAME 
  "${CMAKE_PROJECT_NAME}_${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_PROCESSOR}_${BUILD_TIME}_${CPACK_PACKAGE_VERSION}"
)

# 包含许可证文件（可选）
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")

# 包含 Readme 文件（可选）
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")

# NSIS 默认安装路径
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
# 桌面快捷方式
set(CPACK_NSIS_CREATE_ICONS_EXTRA "CreateShortCut '$DESKTOP/MCParser.lnk' '$INSTDIR/bin/mcparser.exe'")
# 开始菜单名称
set(CPACK_NSIS_PACKAGE_NAME "MCParser")

include(CPack)