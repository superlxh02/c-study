# 第十五章 文件IO

在前面的章节中，我们的程序始终与键盘和屏幕打交道——数据从键盘输入，结果输出到终端窗口，程序一旦退出，所有的计算结果便荡然无存。

这一章将打破这个局限，引入 C 语言中一项关键的机制：**文件读写**。掌握了文件操作，你的程序就能将数据持久地保存在磁盘上，下次启动时可以继续使用；也能处理数量远超手工输入上限的数据集。

本章内容：

- **四种读写方式**：字符读写、行读写、格式化读写、二进制读写
- **高级主题**：文件定位、错误处理、标准流
- 动手练习

## 一、文件操作基础

### 1. 为什么需要文件操作

到目前为止，我们程序的数据都来自键盘输入，结果也都输出到屏幕。一旦程序关闭，所有数据就消失了。但现实中的程序往往需要把数据永久保存下来：

- **学生成绩管理系统**：成绩需要存到磁盘上，下次打开程序还能读取
- **日志系统**：每次操作都需要记录到文件中，方便事后排查问题
- **文本编辑器**：需要能打开文件、编辑内容、保存文件

这一切都依赖**文件操作**——让程序能够读写磁盘上的文件。C 语言通过标准库中的一组函数来操作文件，它们都声明在 `<stdio.h>` 中。

### 2. 文件指针：`FILE *`

在C语言中，操作文件的核心是一个叫 `FILE` 的结构体类型（由系统在 `<stdio.h>` 中定义）。我们不需要关心它的内部细节，只需要知道：每打开一个文件，系统会返回一个指向该文件信息结构的指针，我们通过这个指针来读写文件。

```c
FILE *fp;  // fp 是一个文件指针
```

你可以把 `FILE *` 想象成一张"通行证"：打开文件时，操作系统发放一张通行证，上面记录了文件的各种内部信息。后续的所有读写操作都必须出示这张通行证，系统通过它来辨认你操作的是哪个文件。

### 3. 打开和关闭文件

有了文件指针的概念，接下来看如何获取它。打开文件使用 `fopen` 函数，使用完毕则需要用 `fclose` 释放。

#### 3.1 `fopen` —— 打开文件

```c
FILE *fopen(const char *filename, const char *mode);
```

- `filename`：要打开的文件名（字符串）。
- `mode`：打开模式，决定读/写/追加等操作，见下表。
- 返回值：成功返回 `FILE *`，失败返回 `NULL`。

**常用模式**：

| 模式字符串 | 含义                                                   |
| ---------- | ------------------------------------------------------ |
| `"r"`    | 只读。文件必须存在，否则打开失败。                     |
| `"w"`    | 只写。如果文件存在，清空内容；如果不存在，创建新文件。 |
| `"a"`    | 追加写。在文件末尾添加内容；文件不存在则创建。         |
| `"r+"`   | 读写。文件必须存在。                                   |
| `"w+"`   | 读写。清空已有内容或创建新文件。                       |
| `"a+"`   | 读取和追加写。文件不存在则创建。                       |

#### 3.2 `fclose` —— 关闭文件

```c
int fclose(FILE *stream);
```

关闭文件会将缓冲区中的数据真正写入磁盘，并释放相关资源。**打开的文件使用完后必须关闭**，否则可能导致数据丢失或资源泄露。

将打开和关闭组合起来，就形成了文件操作的标准骨架：

```c
FILE *fp = fopen("data.txt", "r");
if (fp == NULL)
{
    printf("打开文件失败！\n");
    return 1;
}
// ... 读写操作 ...
fclose(fp);
```

这个模式值得牢记：

1. **先尝试打开**（`fopen`）
2. **立即检查返回值**是否为 `NULL`
3. **确认成功后**再进行后续读写操作
4. **最后无论是否出错**都要关闭文件（`fclose`）

---

## 二、文件读写方法

当我们成功打开了一个文件，接下来的问题自然是如何读取其中的数据，或者向其中写入内容。C 语言标准库提供了四组不同粒度的读写函数：

- **按字符**读写
- **按行**读写
- **按格式**读写
- **按二进制块**读写

它们各有适用场景，下面逐一介绍。

### 1. 字符读写：`fgetc` 和 `fputc`

这是最底层的读写方式，每次只处理一个字符。虽然粒度最细，但在需要逐字节处理文件内容时（如加密、统计字符频率）是不可替代的工具。

#### 1.1 `fgetc` —— 读取单个字符

```c
int fgetc(FILE *stream);
```

从文件中读取一个字符，返回值是读取到的字符（转为 `unsigned char` 后的 `int`）。如果读到文件末尾或出错，返回 `EOF`（End Of File，通常定义为 `-1`）。

#### 1.2 `fputc` —— 写入单个字符

```c
int fputc(int c, FILE *stream);
```

向文件写入一个字符 `c`，成功返回写入的字符，出错返回 `EOF`。

#### 1.3 示例：逐个字符复制文件

```c
#include <stdio.h>

int main(void)
{
    FILE *src = fopen("source.txt", "r");
    if (src == NULL) { printf("无法打开源文件\n"); return 1; }

    FILE *dest = fopen("copy.txt", "w");
    if (dest == NULL) { printf("无法打开目标文件\n"); fclose(src); return 1; }

    int ch;
    while ((ch = fgetc(src)) != EOF)
    {
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);
    printf("文件复制完成\n");
    return 0;
}
```

### 2. 行读写：`fgets` 和 `fputs`

字符级别的读写虽然灵活，但对于以行为单位的文本（如配置文件、日志）来说过于繁琐。`fgets` 和 `fputs` 提供了一次处理一整行的便利。

#### 2.1 `fgets` —— 读取一行

```c
char *fgets(char *str, int n, FILE *stream);
```

从文件读取最多 `n-1` 个字符，放入 `str` 中，直到遇到换行符 `'\n'` 或文件末尾。它会保留读到的换行符（如果读到了），并在最后自动添加 `'\0'`。成功返回 `str`，失败或读到文件尾返回 `NULL`。

#### 2.2 `fputs` —— 写入一行（不自动加换行）

```c
int fputs(const char *str, FILE *stream);
```

向文件写入字符串 `str`（不包括末尾的 `'\0'`）。成功返回非负值，失败返回 `EOF`。

> 注意：`fputs` 不会自动添加换行符，如果需要换行，字符串中必须包含 `'\n'`。

#### 2.3 示例：读取文件并显示行号

```c
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("data.txt", "r");
    if (fp == NULL) { printf("无法打开文件\n"); return 1; }

    char line[256];
    int num = 1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("%d: %s", num, line);  // line 本身可能包含换行
        num++;
    }

    fclose(fp);
    return 0;
}
```

### 3. 格式化读写：`fprintf` 和 `fscanf`

行读写处理的是原始字符串，更多时候我们需要按照特定格式存储和读取数据——比如用空格分隔的姓名、年龄和成绩。这时就要用到格式化读写，它们与我们已经熟悉的 `printf` 和 `scanf` 用法几乎一样，只是多了一个 `FILE *` 参数来指定读写目标。

#### 3.1 `fprintf` —— 格式化写入文件

```c
int fprintf(FILE *stream, const char *format, ...);
```

#### 3.2 `fscanf` —— 从文件按格式读取

```c
int fscanf(FILE *stream, const char *format, ...);
```

#### 3.3 示例：把学生信息写入文件再读出来

```c
#include <stdio.h>

struct Student
{
    char name[20];
    int age;
    float score;
};

int main(void)
{
    struct Student s1 = {"小明", 18, 92.5};

    // 写入文件
    FILE *fp = fopen("student.txt", "w");
    if (fp == NULL) return 1;
    fprintf(fp, "%s %d %.1f\n", s1.name, s1.age, s1.score);
    fclose(fp);

    // 从文件读取
    fp = fopen("student.txt", "r");
    if (fp == NULL) return 1;
    struct Student s2;
    if (fscanf(fp, "%19s %d %f", s2.name, &s2.age, &s2.score) != 3)
    {
        fprintf(stderr, "学生数据格式错误\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    printf("姓名：%s，年龄：%d，成绩：%.1f\n", s2.name, s2.age, s2.score);
    return 0;
}
```

> **注意**：`fscanf` 以空白字符（空格、换行、制表符）分隔数据，对于字符串中不能有空格的名字，这没有问题。如果名字可能包含空格，需要用其他方式处理（如 `fgets` + 手动解析）。

### 4. 二进制读写：`fread` 和 `fwrite`

前面三种方式处理的都是文本数据，生成的文件人类可以直接阅读和编辑。但有时我们想把结构体等内存数据直接按字节写入文件，不经过格式转换——这就是**二进制读写**。

- **优点**：速度更快，文件更紧凑
- **代价**：生成的文件不再具有可读性，且跨平台兼容性较差（不同系统可能字节序不同、结构体对齐不同）

#### 4.1 `fwrite` —— 按块写入

```c
size_t fwrite(const void *ptr, size_t size, size_t count, FILE *stream);
```

- `ptr`：要写入的数据的地址。
- `size`：每个数据块的大小（字节）。
- `count`：数据块的个数。
- 返回实际写入的完整块数。

#### 4.2 `fread` —— 按块读取

```c
size_t fread(void *ptr, size_t size, size_t count, FILE *stream);
```

参数含义类似，返回实际读到的完整块数。

#### 4.3 示例：二进制存储和读取结构体数组

```c
#include <stdio.h>

struct Student
{
    char name[20];
    int age;
    float score;
};

int main(void)
{
    struct Student list[2] = {
        {"小明", 18, 92.5},
        {"小红", 19, 88.0}
    };

    // 写入二进制文件
    FILE *fp = fopen("students.dat", "wb");  // "b" 表示二进制模式
    if (fp == NULL) return 1;
    if (fwrite(list, sizeof(struct Student), 2, fp) != 2)
    {
        fprintf(stderr, "写入文件失败\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    // 读取二进制文件
    struct Student readList[2];
    fp = fopen("students.dat", "rb");
    if (fp == NULL) return 1;
    if (fread(readList, sizeof(struct Student), 2, fp) != 2)
    {
        fprintf(stderr, "文件数据不完整或读取失败\n");
        fclose(fp);
        return 1;
    }
    fclose(fp);

    for (int i = 0; i < 2; i++)
        printf("%s %d %.1f\n", readList[i].name, readList[i].age, readList[i].score);

    return 0;
}
```

---

## 三、高级主题

掌握了文件的打开、关闭以及四组基本的读写方法之后，你已经可以完成大多数文件处理任务。但在实际开发中，还会遇到一些进阶需求：

- 如何在文件中跳转到任意位置进行**随机访问**？
- 如何处理读写过程中的各种**错误**？
- 程序启动时自动获得的三个**标准流**又是什么？

这些内容将帮助你写出更健壮、更灵活的文件处理代码。

### 1. 文件定位：`fseek`、`ftell`、`rewind`

文件读写有一个**当前位置指示器**，类似于光标——顺序读取或写入后，它会自动后移。但某些场景下需要跳跃访问，比如直接跳到文件末尾获取文件大小、或者回到开头重新读取。C语言提供了三个函数来操控这个位置指示器。

#### 1.1 `fseek` —— 移动位置指示器

```c
int fseek(FILE *stream, long offset, int whence);
```

- `offset`：位置偏移。对二进制流通常可以按字节理解；文本流只保证 `0` 或先前由 `ftell` 返回的位置值等用法可移植。
- `whence`：起始点。
  - `SEEK_SET`：文件开头
  - `SEEK_CUR`：当前位置
  - `SEEK_END`：文件末尾

#### 1.2 `ftell` —— 获取当前位置

```c
long ftell(FILE *stream);
```

返回当前位置的表示，失败时返回 `-1L`。对二进制流，它通常可作为从文件开头计算的字节位置；文本流的返回值主要用于稍后交还给 `fseek`，不应总当作真实字节数。

#### 1.3 `rewind` —— 回到文件开头

```c
void rewind(FILE *stream);
```

位置移动效果类似 `fseek(stream, 0L, SEEK_SET)`，但 `rewind` 还会清除该流的文件结束标志和错误标志，而且自身没有返回值可供检查。因此二者并不完全等价。

#### 1.4 示例：获取文件大小

```c
#include <stdio.h>

int main(void)
{
    FILE *fp = fopen("data.txt", "rb");
    if (fp == NULL) return 1;

    if (fseek(fp, 0, SEEK_END) != 0) { fclose(fp); return 1; }
    long size = ftell(fp);      // 二进制模式下通常可用作字节数
    if (size < 0) { fclose(fp); return 1; }
    printf("文件大小：%ld 字节\n", size);

    rewind(fp);  // 回到开头继续操作
    fclose(fp);
    return 0;
}
```

> 注意：用 `ftell` 计算文件字节数时，建议用二进制模式 `"rb"` 打开文件。文本模式下，某些系统可能会进行换行转换，位置值不一定等同于真实字节数。

### 2. 错误处理

文件操作可能出现各种错误：**文件不存在**、**权限不足**、**磁盘已满**等等。除了检查 `fopen` 的返回值是否为 `NULL` 之外，C 标准库还提供了一组专门的函数来探测和清理错误状态。

#### 2.1 `feof` —— 是否到达文件末尾

```c
int feof(FILE *stream);
```

需要注意的是，只有在尝试读取**失败之后**，`feof` 才返回真。如果刚刚读完最后有效数据，位置指示器在文件尾，但没有越界读取，`feof` 依然返回假。

> **推荐做法**：使用 `while (fgets(...) != NULL)` 来循环读取，**而不是** `while (!feof(fp))`——后者会因为判断时机的滞后导致多处理一次空数据。

#### 2.2 `ferror` —— 是否发生错误

```c
int ferror(FILE *stream);
```

#### 2.3 `clearerr` —— 清除错误和文件结束标志

```c
void clearerr(FILE *stream);
```

### 3. 标准流：`stdin`、`stdout`、`stderr`

在宿主环境中，C 运行时会在程序启动时预先提供三个标准文本流。它们以 `FILE *` 形式暴露给程序，默认连接到哪里取决于启动方式和重定向设置，并不一定真的是键盘或屏幕。

| 流         | 含义         | 对应的设备                 |
| ---------- | ------------ | -------------------------- |
| `stdin`  | 标准输入     | 键盘                       |
| `stdout` | 标准输出     | 屏幕                       |
| `stderr` | 标准错误输出 | 屏幕（常用于输出错误信息） |

现在可以解释一个早该说破的事实：我们之前一直使用的 `printf` 实际上就是 `fprintf(stdout, ...)`，而 `scanf` 就是 `fscanf(stdin, ...)`。理解这一点之后，你也可以把文件函数用在标准流上——例如将错误信息输出到 `stderr`，使其与正常的程序输出分开处理：

```c
fprintf(stderr, "发生错误！\n");  // 输出到错误流
```

---

## 四、动手练习

```c
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    // 练习1：统计文件中的字符数、单词数、行数
    FILE *fp = fopen("text.txt", "r");
    if (fp == NULL) { printf("文件不存在\n"); return 1; }

    int chars = 0, words = 0, lines = 0;
    int inWord = 0;
    int lastChar = '\n';
    int ch;
    while ((ch = fgetc(fp)) != EOF)
    {
        chars++;
        if (ch == '\n') lines++;
        lastChar = ch;
        if (ch == ' ' || ch == '\n' || ch == '\t')
            inWord = 0;
        else if (inWord == 0)
        {
            inWord = 1;
            words++;
        }
    }
    fclose(fp);
    if (chars > 0 && lastChar != '\n') lines++;
    printf("字符数：%d\n单词数：%d\n行数：%d\n", chars, words, lines);

    return 0;
}
```
