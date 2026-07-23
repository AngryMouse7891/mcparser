#!/usr/bin/python
import subprocess,os


TITLE="""
************************************

MCParser 构建脚本

************************************
"""

GENERATOR="Visual Studio 14 2015"

print(TITLE)

print('生成器：'+GENERATOR)

print('正在配置并生成...')

# 切换工作目录，替代 cd 命令
root_dir = os.path.abspath(os.path.join(__file__, "..", ".."))
build_dir = os.path.join(root_dir, "build")

ret = subprocess.run([
    "cmake",
    "-S", root_dir,
    "-B", build_dir,
    "-DCMAKE_BUILD_TYPE=Release",
    "-G", GENERATOR
])

if ret.returncode:
    print('构建 大 失 败。')
    exit(1)

ret = subprocess.run(["cmake", "--build", build_dir])

if ret.returncode:
    print('构建 大 失 败。')
    exit(1)
else:
    print('构建完了。')