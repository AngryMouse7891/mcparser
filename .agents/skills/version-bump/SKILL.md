---
name: version-bump
description: 根据语义版本调整CMakeLists.txt、resources.rc的版本并创建git tag。分析与上次git tag的差异，自动判定版本类型（major/minor/patch）。“升级版本”、“发布”、“version bump”、“版本升级”、“写入更新日志”等请求启动。
---

# Version Bump

安装CMakeLists.txt等版本并创建git tag。

## 工作流程

### 1. 分析当前状态

```bash
#获取最新版本标签
git describe --tags --abbrev=0 2>/dev/null || echo "v0.0.0"

#获取与前一个标签的差异
git diff <上回标签结果>..HEAD --stat
git diff <上回标签结果>..HEAD
```

### 2. 确定版本类型

分析差异内容，根据以下标准判断版本类型：

| 类别 | 判定标准 |
| ------ | ---------- |
| **major** | 破坏性变更：公共API的签名变更、删除、不兼容的变更 |
| **minor** | 新增功能：新增公共函数/结构/模块，新增功能 |
| **patch** | 错误修复：现有功能修复，重构，文档更新，依赖关系更新 |

### 3. 用户建议

将结果呈现给用户，并在AskUserQuestion中确认：

```
当前版本：X.Y.Z
建议版本：X.Y.Z +1 （patch）

主要变化：
-[更改摘要]

这个版本可以吗？
```

选项：
（patch/minor/major）
-选择不同的版本类型

### 4. 更新版本

用户授权后：

1. 更新`CMakeLists.txt`的`project`指令里面的`VERSION`字段
2. 更新`resources.rc`如下：
```rc
#include <windows.h> // include for version info constants

MCParser ICON "data/mcparser.ico"

#define RT_MANIFEST 24
1 RT_MANIFEST "mcparser.exe.manifest"

//
// TO CHANGE VERSION INFORMATION, EDIT PROJECT OPTIONS...
//
1 VERSIONINFO
FILEVERSION x,y,z,0 //修改为实际的版本
PRODUCTVERSION x,y,z,0 //修改为实际的版本
FILETYPE VFT_APP
{
  BLOCK "StringFileInfo"
  {
    BLOCK "080404e4"
    {
      VALUE "CompanyName", "AngryMouse7891"
      VALUE "FileVersion", "x.y.z" //修改为实际的版本
      VALUE "FileDescription", "一个一个一个一个一个一个一个一个一个一个一个一个一个解析《我的世界》社区资源（如模组）的工具。"
      VALUE "InternalName", "MCParser"
      VALUE "LegalCopyright", "Copyright (c) 2026 红温的鼠鼠7891"
      VALUE "LegalTrademarks", ""
      VALUE "OriginalFilename", "mcparser.exe"
      VALUE "ProductName", "MCParser"
      VALUE "ProductVersion", "x.y.z" //修改为实际的版本
    }
  }
  BLOCK "VarFileInfo"
  {
    VALUE "Translation", 0x0804, 1252
  }
}
```
3. 更新`pkg/PKGBUILD`里面的`pkgver`字段
4. 更新`pkg/snapcraft.yaml`里面的`version`字段
5. 添加`docs/CHANGELOG.md`如下信息（须在`# MCParser发行注记`之下）：
```markdown

## X.Y.Z (yyyy/mm/dd)

* 写一下更新了啥

```
6. 提交更改：`chore: bump version to X.Y.Z `
7. 创建git tag: `vX.Y.Z`

### 5. 完成报告

```
将版本更新为v{新版本}。

请使用git push && git push --tags远程反映。
```

## 注意事项

- 标签带有前缀（例如v1.2.3）
- 工作区仅更新root的CMakeLists.txt