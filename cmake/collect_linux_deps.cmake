# 收集Linux依赖库脚本
# 由CMake install(SCRIPT ...)调用

message(STATUS "开始收集Linux依赖库...")

# 获取绝对路径
get_filename_component(EXE_ABSOLUTE "${CMAKE_INSTALL_PREFIX}/bin/mcparser" ABSOLUTE)
get_filename_component(INSTALL_PREFIX_ABSOLUTE "${CMAKE_INSTALL_PREFIX}" ABSOLUTE)

if(EXISTS "${EXE_ABSOLUTE}")
  # 使用ldd获取依赖库列表
  execute_process(
    COMMAND ldd "${EXE_ABSOLUTE}"
    OUTPUT_VARIABLE LDD_OUTPUT
    ERROR_VARIABLE LDD_ERROR
    RESULT_VARIABLE LDD_RESULT
  )

  if(LDD_RESULT EQUAL 0)
    # 解析ldd输出，提取动态库路径
    string(REGEX MATCHALL "([^ ]+\\.so[^ ]*)" LIB_LIST "${LDD_OUTPUT}")

    # 需要过滤的系统基础库
    set(SKIP_PATTERNS
      "linux-vdso\\.so"
      "ld-linux"
      "libc\\.so\\.[0-9]+"
      "libm\\.so\\.[0-9]+"
      "libstdc\\+\\+\\.so\\.[0-9]+"
      "libgcc_s\\.so\\.[0-9]+"
      "libpthread\\.so\\.[0-9]+"
      "libdl\\.so\\.[0-9]+"
      "librt\\.so\\.[0-9]+"
    )

    set(COLLECTED_COUNT 0)
    set(SKIPPED_COUNT 0)

    # 处理每个依赖库
    foreach(LIB_FULL_PATH ${LIB_LIST})
      # 获取文件名
      get_filename_component(LIB_NAME "${LIB_FULL_PATH}" NAME)

      # 检查是否应该跳过
      set(SHOULD_SKIP FALSE)
      foreach(SKIP_PATTERN ${SKIP_PATTERNS})
        if("${LIB_NAME}" MATCHES "${SKIP_PATTERN}")
          set(SHOULD_SKIP TRUE)
          break()
        endif()
      endforeach()

      # 如果不应该跳过，则复制
      if(NOT SHOULD_SKIP)
        message(STATUS "收集依赖库: ${LIB_NAME} from ${LIB_FULL_PATH}")

        # 确保目标目录存在
        file(MAKE_DIRECTORY "${INSTALL_PREFIX_ABSOLUTE}/lib")

        # 复制库文件
        execute_process(
          COMMAND ${CMAKE_COMMAND} -E copy "${LIB_FULL_PATH}" "${INSTALL_PREFIX_ABSOLUTE}/lib/${LIB_NAME}"
          RESULT_VARIABLE COPY_RESULT
        )

        if(COPY_RESULT EQUAL 0)
          math(EXPR COLLECTED_COUNT "${COLLECTED_COUNT} + 1")

          # 如果是符号链接，也复制指向的实际文件
          get_filename_component(LIB_REAL "${LIB_FULL_PATH}" REALPATH)
          if(NOT "${LIB_REAL}" STREQUAL "${LIB_FULL_PATH}")
            get_filename_component(LIB_REAL_NAME "${LIB_REAL}" NAME)
            execute_process(
              COMMAND ${CMAKE_COMMAND} -E copy "${LIB_REAL}" "${INSTALL_PREFIX_ABSOLUTE}/lib/${LIB_REAL_NAME}"
            )
            math(EXPR COLLECTED_COUNT "${COLLECTED_COUNT} + 1")
          endif()
        else()
          message(WARNING "无法复制库文件: ${LIB_FULL_PATH}")
        endif()
      else()
        math(EXPR SKIPPED_COUNT "${SKIPPED_COUNT} + 1")
        message(STATUS "跳过系统库: ${LIB_NAME}")
      endif()
    endforeach()

    message(STATUS "依赖库收集完成，共收集 ${COLLECTED_COUNT} 个文件，跳过 ${SKIPPED_COUNT} 个系统基础库")
  else()
    message(WARNING "ldd命令执行失败: ${LDD_ERROR}")
  endif()
else()
  message(WARNING "可执行文件不存在: ${EXE_ABSOLUTE}")
endif()
