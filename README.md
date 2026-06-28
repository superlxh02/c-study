# 零基础 C 语言入门到进阶

一份面向零基础学习者的 C 语言中文教程，附带完整可运行源码，覆盖从基础语法、内存管理到工程组织与数据结构的完整入门路径。

[在线阅读完整教程](https://superlxh02.github.io/c-study/)

## 课程大纲

| 阶段     | 章节                 | 核心内容                                                             |
| -------- | -------------------- | -------------------------------------------------------------------- |
| 基础入门 | 第 0～2 章           | 计算机基础、开发环境搭建、变量、类型、表达式、分支、循环、函数       |
| 组织数据 | 第 3～5 章、第 13 章 | 数组、字符串、结构体、共用体、枚举                                   |
| 理解内存 | 第 6～12 章          | 内存模型、指针、结构体指针、函数指针、动态分配、生命周期             |
| 语法扩展 | 第 14～15 章         | 宏、文件 I/O                                                        |
| 工程基础 | 第 16～17 章         | 头文件组织、编译链接、CMake 构建                                    |
| 数据结构 | 总览篇、第 18～19 章 | 单链表、双链表、顺序栈、链式队列、环形队列                           |
| 查漏补缺 | 第 20 章             | C 语言常见语法与概念辨析                                             |

## 进阶篇（规划中）

入门篇覆盖了 C 语言的核心语法、内存模型、基础数据结构和工程构建，但要真正驾驭 C，还需要深入以下方向：

- **CMake 进阶**：创建与导入库、编译参数配置、构建优化
- **函数接口设计**：灵活运用 `void *` 适配多类型参数，善用 `const` 限定符约束接口契约，设计出不易误用的 API
- **宏魔法**：利用预处理器消除样板代码、实现编译期分支和代码生成
- **内存对齐**：分析 `struct` 与 `union` 的成员排布和整体大小，理解对齐规则如何影响内存布局；利用共用体实现 SSO（Small String Optimization）等空间优化技术
- **柔性数组**：在结构体末尾放置可变长度缓冲区，一次分配同时容纳元数据和数据
- **面向对象编程**：不止于结构体嵌函数指针——手动构造虚表（vtable），在 C 中实现封装、继承与运行时多态
- **树与图**：二叉树、平衡树、图的遍历与常见算法
- **实战项目**：待定

## 仓库结构

```text
.
├─ book/
│  ├─ book.toml          # mdBook 配置
│  └─ src/               # 课程正文与目录
└─ src/
   ├─ ch01-basics/       # 基础章节的独立示例
   ├─ ...
   ├─ ch16-headers/      # 多文件与头文件示例
   ├─ ch17-cmake/        # CMake 入门项目
   └─ ch18-data-structures/ # 六个独立数据结构项目
```

文档中的完整示例与 `src/` 下的源码相互对应。数据结构项目采用 `include/`、`src/` 和 `CMakeLists.txt` 的常见布局，方便查看接口与实现的边界。

## 本地构建与阅读

安装 [mdBook](https://rust-lang.github.io/mdBook/guide/installation.html) 后，在仓库根目录运行：

```bash
mdbook serve book --open
```

只生成静态站点时运行：

```bash
mdbook build book
```

输出目录是 `book/book/`。仓库中的 GitHub Actions 工作流也会构建该目录并发布到 GitHub Pages。

## 编译配套源码

单文件示例可直接使用 Clang 编译：

```bash
clang -std=c17 -Wall -Wextra -Wpedantic path/to/example.c -o example
```

第十六章起包含多文件项目，需同时指定多个源文件和头文件路径：

```bash
clang -std=c17 src/ch16-headers/src/main.c src/ch16-headers/src/mathutils.c \
  -Isrc/ch16-headers/include -o mathutils_demo
```

CMake 项目（第十七章起及数据结构部分）使用统一流程：

```bash
cmake -S src/ch17-cmake -B build/ch17
cmake --build build/ch17
```

数据结构目录（`src/ch18-data-structures/`）下的每个子目录均为独立 CMake 项目，将 `-S` 指向对应目录即可。
