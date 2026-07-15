# 通用开发说明

## Windows

1. 安装 [MSYS2](https://www.msys2.org)

2. 配置环境

在MSYS2中安装工具链以及其它依赖然后配置环境变量：

```bash
pacman -S $MINGW_PACKAGE_PREFIX-{gcc,make,jsoncpp,curl,fmt,openssl,pkgconf,cmake} #安装GCC、make、jsoncpp、cURL、fmt、OpenSSL、pkg-config、CMake
export PATH=$MSYSTEM_PREFIX/bin:$PATH
```

你也可以将Ninja作为底层构建工具：
```bash
pacman -S $MINGW_PACKAGE_PREFIX-ninja
```

如果你不想通过MSYS2安装CMake，你也可以从 [CMake官网](https://cmake.org) 下载安装。

3. 获取源码：

通过Git克隆该仓库：

```bash
pacman -S git #安装git

git clone https://gitee.com/AngryMouse7891/mcparser.git #克隆仓库

```

如果你不想通过MSYS2安装Git，你也可以从 [Git官网](https://git-scm.com) 下载安装。

4. 正式构建：

```bash
cd mcparser #切换到源码目录
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G "MinGW Makefiles" #配置项目
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -G "Ninja" #若使用Ninja
cd build #切换到构建目录
cmake --build . -- -j $(nproc) #构建项目（最大线程）
cmake --install . --prefix test_install --config Release #安装项目（带收集dll）
```

上述步骤完成后，`build/test_install/bin/mcparser.exe`就是构建之后的文件。

5. 打包（可选）

在MSYS2中安装NSIS并配置：

```bash
pacman -S $MINGW_PACKAGE_PREFIX-nsis #安装NSIS
```

如果你不想通过MSYS2安装NSIS，你也可以从 [NSIS官网](https://nsis.sourceforge.io/) 下载安装。

之后在源码目录下的`build`目录运行命令：

```bash
cpack -C Release #通过CPack打包
````

打包完成后，会出现两个文件：

`MCParser_xxx_xxx_xxxxxxxx_xxxxxx_x.x.x.exe`

`MCParser_xxx_xxx_xxxxxxxx_xxxxxx_x.x.x.zip`

这就是打包之后的文件。