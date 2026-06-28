/**
 * =====================================================
 * 文件名: 26_guessing_game.c
 * 所属章节: 第一章 - C语言核心基础语法
 * 对应小节: 十、2. 综合练习：猜数游戏
 * 演示内容: 综合运用第一章所有知识点——
 *           变量、数据类型、运算符、判断、循环、
 *           函数、头文件、标准输入输出
 *           完成一个完整的猜数游戏
 * =====================================================
 */

/* =============================================
 * 猜数游戏
 * 功能：程序随机生成 1-100 的整数，玩家猜数字
 * 知识点：变量、类型、运算符、判断、循环、函数、
 *         头文件、标准输入输出
 * ============================================= */

#include <stdio.h>     /* 标准输入输出函数：printf, scanf */
#include <stdlib.h>    /* 标准库函数：rand, srand */
#include <time.h>      /* 时间函数：time */

/* ---------- 函数声明 ---------- */

/* 生成指定范围内的随机整数，包括 min 和 max
 * 参数：min —— 范围下限（包含）
 *       max —— 范围上限（包含）
 * 返回值：[min, max] 范围内的随机整数 */
int generateRandomNumber(int min, int max);

/* 获取用户的有效猜测（1-100 之间的整数）
 * 会不断提示用户输入，直到输入有效为止
 * 参数：无（void 表示不需要参数）
 * 返回值：用户输入的有效整数 */
int getValidGuess(void);

/* 根据猜测结果给出提示
 * 参数：guess  —— 用户的猜测
 *       target —— 程序生成的目标数字
 * 返回值：1 表示猜中，0 表示未猜中 */
int checkGuess(int guess, int target);

/* ---------- 主函数 ---------- */
int main(void)
{
    int targetNumber;       /* 程序生成的目标数字 */
    int userGuess;          /* 用户输入的猜测 */
    int guessCount;         /* 记录当前局猜测次数 */
    int gameCount = 0;      /* 记录当前是第几局 */
    int isCorrect;          /* 是否猜中：1 表示猜中，0 表示未猜中 */
    char playAgain;         /* 是否再来一局：'y' 表示是，'n' 表示否 */

    /* 用当前时间初始化随机数种子
     * time(NULL) 返回当前系统时间（从1970年1月1日至今的秒数）
     * (unsigned int) 将 time 的返回值强制转换为 unsigned int 类型
     * srand() 用这个不断变化的时间值来初始化随机数生成器
     * 效果：每次运行程序时生成的随机数序列都不同 */
    srand((unsigned int)time(NULL));

    /* 游戏欢迎界面 */
    printf("=================================\n");
    printf("      欢迎来到猜数游戏！\n");
    printf("=================================\n\n");

    /* 外层循环：使用 do-while 控制是否再来一局
     * 使用 do-while 确保游戏至少玩一局
     * 循环条件：只要用户输入 'y' 或 'Y'，就继续游戏 */
    do
    {
        gameCount++;        /* 开始新的一局，局数加 1 */

        /* 每局开始时初始化：
         *   1. 生成 1 到 100 之间的随机目标数
         *   2. 猜测次数清零
         *   3. 猜中状态重置为"未猜中"（0） */
        targetNumber = generateRandomNumber(1, 100);
        guessCount = 0;
        isCorrect = 0;

        printf("【第 %d 局】我已经想好了一个 1 到 100 之间的数字。\n", gameCount);
        printf("请你来猜一猜吧！\n\n");

        /* 内层循环：使用 while 不断猜测直到猜中
         * !isCorrect 的意思是"isCorrect 为 0 时继续循环"
         * 即：只要还没猜中（isCorrect == 0），就一直猜 */
        while (!isCorrect)
        {
            /* 步骤1：获取用户的有效输入 */
            userGuess = getValidGuess();
            guessCount++;   /* 猜测次数加 1 */

            /* 步骤2：判断猜测结果，将返回值赋给 isCorrect
             * checkGuess 返回 1（猜中）时，isCorrect 变为 1
             * !isCorrect 变为假，while 循环结束 */
            isCorrect = checkGuess(userGuess, targetNumber);
        }

        /* ---- 猜中后的反馈 ---- */

        /* 输出猜测次数 */
        printf("\n恭喜你猜对了！你一共猜了 %d 次。\n", guessCount);

        /* 使用 if-else if-else 根据猜测次数给出不同评价 */
        if (guessCount <= 5)
        {
            printf("评价：太厉害了，简直是猜数天才！\n");
        }
        else if (guessCount <= 10)
        {
            printf("评价：不错不错，继续加油！\n");
        }
        else
        {
            printf("评价：还可以更棒，多练习几次吧！\n");
        }

        /* 询问是否再来一局
         * %c 前面的空格用来跳过之前输入留下的换行符
         * &playAgain 前面的 & 不能忘记 */
        printf("\n想再来一局吗？(y/n)：");
        if (scanf(" %c", &playAgain) != 1)
        {
            /* 输入流关闭时按“不再继续”处理，避免读取未初始化字符。 */
            playAgain = 'n';
        }
        printf("\n");

    } while (playAgain == 'y' || playAgain == 'Y');
    /* || 是逻辑或运算符：左边或右边有一个为真即为真
     * 用户输入 'y' 或 'Y' 都表示再来一局 */

    printf("感谢游玩，再见！\n");

    return 0;
}

/* ---------- 函数定义 ---------- */

/*
 * 函数：generateRandomNumber
 * 功能：生成 [min, max] 范围内的随机整数
 * 参数：
 *   min - 范围下限（包含）
 *   max - 范围上限（包含）
 * 返回值：生成的随机整数
 *
 * 算法解析：
 *   rand() % (max - min + 1) + min
 *   第1步：rand() 生成一个大的随机整数
 *   第2步：% (max - min + 1) 取余，得到 0 到 (max-min) 之间的数
 *   第3步：+ min 把范围平移到 [min, max]
 *
 *   例如 min=1, max=100：
 *     max - min + 1 = 100
 *     rand() % 100 得到 0 到 99
 *     + 1 得到 1 到 100
 */
int generateRandomNumber(int min, int max)
{
    int randomNum = rand() % (max - min + 1) + min;
    return randomNum;
}

/*
 * 函数：getValidGuess
 * 功能：获取用户输入的有效猜测（1-100 之间的整数）
 *       如果用户输入无效（非数字、超出范围），会不断提示重新输入
 * 参数：无
 * 返回值：用户输入的有效整数
 *
 * 输入验证机制：
 *   1. scanf("%d", &guess) 的返回值表示成功读取了几个值
 *      如果用户输入的不是数字（如 "abc"），返回 0
 *      如果成功读取了一个整数，返回 1
 *   2. getchar() 循环丢弃当前行剩余输入，并同时检查 EOF
 *      如果 scanf 读取失败，错误的输入还留在缓冲区
 *      必须把它们读走，否则下次 scanf 又会读到它们
 *   3. 检查数值范围：guess < 1 或 guess > 100 也视为无效
 */
int getValidGuess(void)
{
    int guess;
    int isValid;    /* 输入是否有效：1 表示有效，0 表示无效 */

    /* do-while 确保至少提示一次输入
     * 只要 !isValid 为真（输入无效），就继续循环 */
    do
    {
        printf("请输入你的猜测（1-100）：");
        isValid = scanf("%d", &guess);  /* scanf 返回成功读取的项数 */
        if (isValid == EOF)
        {
            /* 输入流已经关闭，不再无休止地重复提示。 */
            printf("\n输入已结束，游戏退出。\n");
            exit(EXIT_SUCCESS);
        }

        /* 清空输入缓冲区
         * getchar() 从缓冲区读取一个字符
         * 循环直到读到换行符 '\n'（表示一行的结束）
         * 这样就能把用户输入的无效内容全部清除 */
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            /* 空循环体：不断读取，直到本行结束或输入流关闭。 */
        }

        /* 检查输入是否有效
         * isValid != 1  —— scanf 没有成功读取一个整数
         * guess < 1     —— 数字小于下限
         * guess > 100   —— 数字大于上限
         * || 是逻辑或，三个条件任一个成立即为无效 */
        if (isValid != 1 || guess < 1 || guess > 100)
        {
            printf("输入无效！请输入 1 到 100 之间的整数。\n\n");
            isValid = 0;    /* 标记为无效，使 !isValid 为真，继续循环 */
        }
    } while (!isValid);

    return guess;
}

/*
 * 函数：checkGuess
 * 功能：比较猜测值和目标值，给出提示
 * 参数：
 *   guess  - 用户的猜测
 *   target - 程序生成的目标数字
 * 返回值：
 *   0 —— 未猜中（猜大了或猜小了）
 *   1 —— 猜中了
 *
 * 判断逻辑（三种情况）：
 *   guess > target  → "猜大了"  → return 0
 *   guess < target  → "猜小了"  → return 0
 *   guess == target → "猜对了"  → return 1
 *
 * 返回值被赋给 isCorrect，用于控制内层 while 循环是否继续
 */
int checkGuess(int guess, int target)
{
    if (guess > target)
    {
        printf("  → 猜大了！再小一点试试。\n\n");
        return 0;   /* 没猜中 */
    }
    else if (guess < target)
    {
        printf("  → 猜小了！再大一点试试。\n\n");
        return 0;   /* 没猜中 */
    }
    else
    {
        printf("  → 恭喜你，猜对了！\n");
        return 1;   /* 猜中了 */
    }
}

/* ============================================================
 * 编译: clang guess_game.c -o guess_game.exe
 * 运行: guess_game.exe
 *
 * 运行示例：
 *   =================================
 *         欢迎来到猜数游戏！
 *   =================================
 *
 *   【第 1 局】我已经想好了一个 1 到 100 之间的数字。
 *   请你来猜一猜吧！
 *
 *   请输入你的猜测（1-100）：50
 *     → 猜小了！再大一点试试。
 *
 *   请输入你的猜测（1-100）：75
 *     → 猜大了！再小一点试试。
 *
 *   请输入你的猜测（1-100）：60
 *     → 猜小了！再大一点试试。
 *
 *   请输入你的猜测（1-100）：68
 *     → 恭喜你，猜对了！
 *
 *   恭喜你猜对了！你一共猜了 4 次。
 *   评价：太厉害了，简直是猜数天才！
 *
 *   想再来一局吗？(y/n)：n
 *
 *   感谢游玩，再见！
 *
 * 本程序综合运用了第一章的所有知识点：
 *   - 预处理指令 #include
 *   - main 函数程序入口
 *   - 变量声明和初始化
 *   - 数据类型 int, char
 *   - 算术运算符 +, -, %
 *   - 比较运算符 ==, !=, >, <, >=, <=
 *   - 逻辑运算符 !, ||
 *   - if / else if / else 判断
 *   - while 循环和 do-while 循环
 *   - 函数声明、定义和调用
 *   - 标准输入 scanf 和标准输出 printf
 *   - 随机数生成 rand / srand
 * ============================================================
 */
