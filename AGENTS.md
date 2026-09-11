# AGENTS.md

## 1. Project Overview（项目基础信息）

- 项目类型：Minecraft社区资源下载工具
- 核心技术栈：C++
- 项目用途：解析并下载Minecraft社区资源（如模组）
- 核心约束：使用C++23规范

## 2. Setup & Development（环境搭建与开发流程）

### 2.1 开发运行

- 配置项目：cmake -B build
- 构建命令：cmake --build build，输出目录为 build/

## 3. Other Rules（其他规则）

### 3.1 禁止操作

- 不得修改/删除：.python-version（uv生成的Python版本文件）、.env/（Python虚拟环境）、pkg/（软件包配置文件）、data/（额外数据文件）、screenshots/（截图文件）、images/（图片文件）
- 不得修改：package.json 中的依赖版本、CI/CD 流水线配置（`.github/workflows/`、`.gitlab-ci.yml`）
- 不得提交：build 目录、out 目录、IDE 配置文件（`.vscode/`、`.idea/`）、未完成的测试代码
