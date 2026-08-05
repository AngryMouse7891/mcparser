cmake_minimum_required(VERSION 3.10)

project(MCParser
  VERSION 1.4.2
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
install(FILES LICENSE README.md BUILD.md CHANGELOG DESTINATION share/MCParser)
install(DIRECTORY screenshots/ DESTINATION share/MCParser/screenshots)
install(DIRECTORY images/ DESTINATION share/MCParser/images)
install(FILES data/mcparser.png DESTINATION share/icons/hicolor/256x256/apps)
install(FILES data/256x256@2x/mcparser.png DESTINATION share/icons/hicolor/256x256@2x/apps)
install(FILES data/MCParser.desktop DESTINATION share/applications)
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
  # 在脚本模式执行依赖拷贝，需要生成一个 .cmake 脚本，安装结束自动运行
  install(FILES data/mcparser.exe.manifest DESTINATION bin)
endif()

include(BundleUtilities)
# 1. 设置安装目录根路径（CMAKE_INSTALL_PREFIX）
set(BU_COPY_TO_INSTALL ON)

if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
  if(MCPARSER_LINUX_BUNDLE)
    # 使用ldd手动收集依赖库
    install(CODE "
      message(STATUS \"开始收集Linux依赖库...\")
      
      # 获取绝对路径
      get_filename_component(EXE_ABSOLUTE \"\${CMAKE_INSTALL_PREFIX}/bin/mcparser\" ABSOLUTE)
      get_filename_component(INSTALL_PREFIX_ABSOLUTE \"\${CMAKE_INSTALL_PREFIX}\" ABSOLUTE)
      
      if(EXISTS \"\${EXE_ABSOLUTE}\")
        # 使用ldd获取依赖库列表
        execute_process(
          COMMAND ldd \"\${EXE_ABSOLUTE}\"
          OUTPUT_VARIABLE LDD_OUTPUT
          ERROR_VARIABLE LDD_ERROR
          RESULT_VARIABLE LDD_RESULT
        )
        
        if(LDD_RESULT EQUAL 0)
          # 解析ldd输出，提取动态库路径
          string(REGEX MATCHALL \"(/[^\n ]+\\.so[^\n ]*)\" LIB_LIST \"\${LDD_OUTPUT}\")
          
          # 需要过滤的系统基础库
          set(SKIP_PATTERNS
            \"linux-vdso\.so\"           # 内核虚拟库
            \"ld-linux\"                 # 动态链接器
            \"libc\.so\6\"                # C标准库
            \"libm\.so\6\"                # 数学库
            \"libstdc\+\+\.so\6\"         # C++标准库
            \"libgcc_s\.so\1\"            # GCC运行时
            \"libpthread\.so\0\"          # 线程库
            \"libdl\.so\2\"               # 动态加载库
            \"librt\.so\1\"               # 实时扩展库
          )
          
          set(COLLECTED_COUNT 0)
          set(SKIPPED_COUNT 0)
          
          # 处理每个依赖库
          foreach(LIB_FULL_PATH \${LIB_LIST})
            # 获取文件名
            get_filename_component(LIB_NAME \"\${LIB_FULL_PATH}\" NAME)
            
            # 检查是否应该跳过
            set(SHOULD_SKIP FALSE)
            foreach(SKIP_PATTERN \${SKIP_PATTERNS})
              if(\"\${LIB_NAME}\" MATCHES \"\${SKIP_PATTERN}\")
                set(SHOULD_SKIP TRUE)
                break()
              endif()
            endforeach()
            
            # 如果不应该跳过，则复制
            if(NOT SHOULD_SKIP)
              message(STATUS \"收集依赖库: \${LIB_NAME} from \${LIB_FULL_PATH}\")
              
              # 确保目标目录存在
              file(MAKE_DIRECTORY \"\${INSTALL_PREFIX_ABSOLUTE}/lib\")
              
              # 复制库文件
              execute_process(
                COMMAND \${CMAKE_COMMAND} -E copy \"\${LIB_FULL_PATH}\" \"\${INSTALL_PREFIX_ABSOLUTE}/lib/\${LIB_NAME}\"
                RESULT_VARIABLE COPY_RESULT
              )
              
              if(COPY_RESULT EQUAL 0)
                math(EXPR COLLECTED_COUNT \"\${COLLECTED_COUNT} + 1\")
                
                # 如果是符号链接，也复制指向的实际文件
                get_filename_component(LIB_REAL \"\${LIB_FULL_PATH}\" REALPATH)
                if(NOT \"\${LIB_REAL}\" STREQUAL \"\${LIB_FULL_PATH}\")
                  get_filename_component(LIB_REAL_NAME \"\${LIB_REAL}\" NAME)
                  execute_process(
                    COMMAND \${CMAKE_COMMAND} -E copy \"\${LIB_REAL}\" \"\${INSTALL_PREFIX_ABSOLUTE}/lib/\${LIB_REAL_NAME}\"
                  )
                  math(EXPR COLLECTED_COUNT \"\${COLLECTED_COUNT} + 1\")
                endif()
              else()
                message(WARNING \"无法复制库文件: \${LIB_FULL_PATH}\")
              endif()
            else()
              math(EXPR SKIPPED_COUNT \"\${SKIPPED_COUNT} + 1\")
              message(STATUS \"跳过系统库: \${LIB_NAME}\")
            endif()
          endforeach()
          
          message(STATUS \"依赖库收集完成，共收集 \${COLLECTED_COUNT} 个文件，跳过 \${SKIPPED_COUNT} 个系统基础库\")
        else()
          message(WARNING \"ldd命令执行失败: \${LDD_ERROR}\")
        endif()
      else()
        message(WARNING \"可执行文件不存在: \${EXE_ABSOLUTE}\")
      endif()
    ")
    
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
