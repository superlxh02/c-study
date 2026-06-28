/**
 * =====================================================
 * 文件名: 05_struct_return.c
 * 所属章节: 第五章
 * 对应小节: 二-2.2 用结构体作返回值
 * 演示内容: 函数如何返回一个结构体变量；
 *          结构体不仅可以作为参数传入，也可以作为返回值传出
 * =====================================================
 */

#include <stdio.h>

// 定义 Student 结构体类型
struct Student
{
    char name[20];    // 姓名
    int age;          // 年龄
    float score;      // 成绩
};

/*
 * 函数：打印学生信息（接收结构体参数）
 * 跟 04_struct_to_function.c 中的函数一样
 */
void printStudent(struct Student stu)
{
    printf("姓名：%s，年龄：%d，成绩：%.1f\n",
           stu.name, stu.age, stu.score);
}

/*
 * 函数：创建一个学生并返回
 * 返回类型：struct Student —— 返回一个完整的结构体
 *
 * 函数内部创建了一个局部结构体变量 newStu，
 * 然后用 return 把它返回给调用者。
 * 注意：返回的也是副本——newStu 本身在函数结束时销毁，
 * 但它的值被复制到了调用者的接收变量中。
 */
struct Student createStudent(void)
{
    struct Student newStu = {"新同学", 18, 80.0};
    return newStu;  // 返回一个结构体（按值返回，调用者收到副本）
}

int main(void)
{
    // 调用函数获取一个结构体
    struct Student stu = createStudent();

    // 打印获取到的结构体内容
    printStudent(stu);

    return 0;
}

/*
 * =====================================================
 * 预期输出:
 * =====================================================
 * 姓名：新同学，年龄：18，成绩：80.0
 * =====================================================
 */
