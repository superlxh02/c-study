# 教程配套源码

目录名与 `book/src/入门` 的当前章节编号保持一致。

## 第十七章以前

第一至第十五章以独立 `.c` 文件为主。带有 `main` 函数的完整示例可以直接用 Clang 编译；文件名为 `00_snippets.c` 的文件主要用于保存章节片段，不一定是独立程序：

```bash
clang -std=c17 -Wall -Wextra -Wpedantic 示例文件.c -o 示例程序
```

第十六章专门讲解头文件与多文件组织，因此保留 `include/`、`src/` 与多个 `.c` 文件，但仍然手动调用 Clang，不使用 CMake：

```bash
cd ch16-headers
clang -std=c17 -Wall -Wextra -Wpedantic src/main.c src/mathutils.c -Iinclude -o mathutils_demo
```

## 第十七章以后

- `ch17-cmake`：与 CMake 初识章节配套的多文件项目。
- `ch18-data-structures`：对应第十八、十九章；每种数据结构都是一个独立 CMake 项目，各自包含公共头文件、实现文件和 `main.c`。

任意数据结构项目都使用相同构建流程：

```bash
cmake -S 项目目录 -B 项目目录/build
cmake --build 项目目录/build
```

目前包含：数组增删改查、单链表、双链表、顺序栈、链式队列和环形队列。
