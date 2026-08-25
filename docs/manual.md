# 安装

## 通过预编译二进制文件下载安装

!!! warning "Gitee Releases不再更新预编译二进制文件通知"
    由于Gitee Releases附件大小限额已达1G，v1.4.5及之后的版本的预构建二进制文件已不再在Gitee Releases上提交。请大家选择其他下载线路以下载最新版本。
    虽然以后仍会创建发行版，但只会上传源码了……

!!! tip "新增蓝奏云盘下载线路"
    由于2026年8月20日本人已注册蓝奏云盘账号，新版本已开始上传至蓝奏云盘，速度更快！
    分享链接（提取码`cu7m`）：<https://wwbdd.lanzouu.com/b01euppgqj>

Gitee Releases（`v1.4.5`之后停止更新二进制文件）：<https://gitee.com/AngryMouse7891/mcparser/releases>

夸克网盘：<https://pan.quark.cn/s/f88f5aed5752>

百度网盘（提取码`bikb`）：<https://pan.baidu.com/s/1-WTiixGq7kUxkVbkALO_Ew>

蓝奏云（可下载Windows、Linux版，提取码`cu7m`）：<https://wwbdd.lanzouu.com/b01euppgqj>

MineBBS：<https://www.minebbs.com/resources/mcparser.17435/>

MCBBS纪念版：<https://www.mcbbs.co/thread-5638-1-1.html>

## 通过源码编译安装

详细请看[开发指南](./BUILD.md)。

# 使用

!!! warning "避坑指南"
    输入文字之后，一定要按回车，一定要按回车！！！

启动之后，一般界面如下：

![启动屏幕](./screenshots/splashscreen.png "启动屏幕")

输入项目id之后按回车，解析成功后，一般界面如下：

![解析成功](./screenshots/parse_success.png "解析成功")

再输入要列出的文件数之后按回车，一般界面如下：

<!-- md:version 1.3.8 -->
??? note "提示"
    当输入的数字比解析到的文件数量大时，将会设置为最后一个文件；如果输入的数字比0小，则会设置为0。

![文件列表](./screenshots/filelist.png "文件列表")

再输入要下载的文件索引之后按回车，然后输入下载路径后按回车，就会开始下载，一般界面如下：

<!-- md:version 1.3.8 -->
??? note "提示"
    当输入的数字比解析到的文件数量大时，将会设置为最后一个文件；如果输入的数字比0小，则会设置为0。

!!! warning "注意"
    由于使用Modrinth官方源解析下载，速度会有点慢

![下载文件](./screenshots/download.png "下载文件")

下载完成后，一般界面如下：

![下载完成](./screenshots/complete.png "下载完成")
