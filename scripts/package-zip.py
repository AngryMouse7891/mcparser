#!/usr/bin/python
import subprocess,os


TITLE="""
************************************

MCParser 打包脚本

************************************
"""

print(TITLE)


print('正在安装……')

# 切换工作目录，替代 cd 命令
root_dir = os.path.abspath(os.path.join(__file__, "..", ".."))
build_dir = os.path.join(root_dir, "build")

ret = subprocess.run([
    "cmake",
    "--install",
    build_dir,
    "--prefix",
    os.path.join(build_dir,"inst"),
    "--config",
    "Release"
])

if ret.returncode:
    print('打包 大 失 败。')
    exit(1)

ret = subprocess.run(["cpack", "-C", "Release", "-G", "ZIP"])

if ret.returncode:
    print('打包 大 失 败。')
    exit(1)
else:
    print('打包完了。')