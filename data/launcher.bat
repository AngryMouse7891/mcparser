@echo off
title MCParser启动器脚本
mcparser.exe

set exitcode=%errorlevel%

if %exitcode% == 0 ( goto ok ) else ( goto err )

:ok
echo 进程已完成
exit

:err
echo 进程已完成 - 退出代码 %exitcode%
pause
exit