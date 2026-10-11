#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

/* ================= 公共输入工具 ================= */

/* 读入一个整数：成功返回 1；输入非法返回 0（可重试）；输入结束返回 -1 */
static int read_int(const char *prompt, int *out)
{
    int ch;

    printf("%s", prompt);

    if (scanf("%d", out) == 1)
    {
        /* 吃掉这一行剩下的字符，避免影响下一次读取 */
        while ((ch = getchar()) != '\n' && ch != EOF)
        {
            ;
        }
        return 1;
    }

    if (feof(stdin))
    {
        return -1;
    }

    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        ;
    }
    printf("输入无效，请输入一个整数。\n");
    return 0;
}

/* ================= 1. 创建与初始化 ================= */

/*
 * 必背：数组是一组相同类型元素的集合，元素个数不能为 0
 * 重点：不完全初始化剩余补 0；大小可省（由初值个数决定）
 */
static void arr_init_demo(void)
{
    int arr1[5] = { 1, 2, 3, 4, 5 };   /* 完全初始化 */
    int arr2[6] = { 1 };               /* 不完全初始化：剩余自动补 0 */
    int arr3[] = { 1, 2, 3 };          /* 省大小：长度由初值个数决定 */
    /* int arr4[3] = { 1, 2, 3, 4 };   错误：初始化项太多 */
    int i;

    printf("---------- 1. 创建与初始化 ----------\n");

    printf("arr1[5] = {1,2,3,4,5}  完全初始化：");
    for (i = 0; i < 5; i++)
    {
        printf("%d ", arr1[i]);
    }
    printf("\n");

    printf("arr2[6] = {1}          不完全初始化：");
    for (i = 0; i < 6; i++)
    {
        printf("%d ", arr2[i]);
    }
    printf("（剩余元素自动补 0）\n");

    printf("arr3[]  = {1,2,3}      省大小：");
    for (i = 0; i < 3; i++)
    {
        printf("%d ", arr3[i]);
    }
    printf("（长度由初值个数决定）\n");

    printf("元素个数 = sizeof(arr1) / sizeof(arr1[0]) = %d\n",
           (int)(sizeof(arr1) / sizeof(arr1[0])));
    printf("数组类型：int arr1[5] 的类型是 int[5]（去掉名字剩下的部分）。\n");
}

/* ================= 2. 一维数组：输入与遍历 ================= */

/* 下标从 0 开始；遍历时长度别写死，用 sizeof 算 */
static void arr_1d_demo(void)
{
    int arr[10];
    int sz;
    int i;
    char prompt[32];

    printf("---------- 2. 一维数组：输入与遍历 ----------\n");
    for (i = 0; i < 10; i++)
    {
        snprintf(prompt, sizeof(prompt), "请输入第 %d 个数>: ", i + 1);
        if (read_int(prompt, &arr[i]) != 1)
        {
            printf("本题结束。\n");
            return;
        }
    }

    sz = (int)(sizeof(arr) / sizeof(arr[0]));
    printf("你输入的 %d 个数：", sz);
    for (i = 0; i < sz; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n长度 = sizeof(arr) / sizeof(arr[0]) = %d\n", sz);
    printf("下标从 0 开始，最后一个元素是 arr[%d]。\n", sz - 1);
}

/* ================= 3. 内存布局：连续存放 ================= */

static void arr_memory_demo(void)
{
    int arr[5] = { 1, 2, 3, 4, 5 };
    char ch[5] = { 'a', 'b', 'c', 'd', 'e' };
    int i;

    printf("---------- 3. 内存布局：连续存放 ----------\n");

    printf("int 数组（相邻两个元素相差 sizeof(int) = %d 字节）：\n", (int)sizeof(int));
    for (i = 0; i < 5; i++)
    {
        printf("  &arr[%d] = %p\n", i, (void *)&arr[i]);
    }
    printf("  &arr[1] 和 &arr[0] 的差 = %d 字节\n",
           (int)((char *)&arr[1] - (char *)&arr[0]));

    printf("char 数组（相邻两个元素相差 sizeof(char) = %d 字节）：\n", (int)sizeof(char));
    for (i = 0; i < 5; i++)
    {
        printf("  &ch[%d] = %p\n", i, (void *)&ch[i]);
    }
    printf("  &ch[1] 和 &ch[0] 的差 = %d 字节\n",
           (int)((char *)&ch[1] - (char *)&ch[0]));

    printf("结论：地址随下标递增，差值永远等于元素类型的大小；\n");
    printf("      地址每次运行都不同（系统随机化），差值是固定的。\n");
}

/* ================= 4. 二维数组 ================= */

/*
 * 创建：type arr[行][列]，行列下标都从 0 开始
 * 【易错】可以省略行，不能省略列；二维数组同样连续存放（按行排成一条长队）
 */
static void arr_2d_demo(void)
{
    int arr[3][5] = { 1, 2, 3, 4, 5, 2, 3, 4, 5, 6, 3, 4, 5, 6, 7 };
    int a3[3][5] = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    int a4[][5] = { 1, 2, 3, 4, 5, 6, 7 };
    int i;
    int j;

    printf("---------- 4. 二维数组 ----------\n");

    printf("arr[3][5] 完全初始化，按行打印：\n");
    for (i = 0; i < 3; i++)
    {
        printf("  第 %d 行：", i);
        for (j = 0; j < 5; j++)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
    printf("arr[2][4] = %d（arr[2][4] 就是博客里的 7）\n", arr[2][4]);

    printf("a3[3][5] = {{1,2},{3,4},{5,6}} 按行初始化：\n");
    for (i = 0; i < 3; i++)
    {
        printf("  第 %d 行：", i);
        for (j = 0; j < 5; j++)
        {
            printf("%d ", a3[i][j]);
        }
        printf("\n");
    }

    printf("a4[][5] = {1,2,3,4,5,6,7} 省略行（列不能省），实际有 2 行：\n");
    for (i = 0; i < 2; i++)
    {
        printf("  第 %d 行：", i);
        for (j = 0; j < 5; j++)
        {
            printf("%d ", a4[i][j]);
        }
        printf("\n");
    }

    printf("二维数组也是连续存放：arr[0][4] 和 arr[1][0] 的地址相差 %d 字节。\n",
           (int)((char *)&arr[1][0] - (char *)&arr[0][4]));
}

/* ================= 5. 经典题 1：字符从两端向中间汇聚 ================= */

/*
 * 思路：left、right 两个下标从两端往中间走，每步把 arr1 的字符抄进 arr2
 * Sleep(1000) 只是让动画慢一点，去掉不影响结果（需要 <windows.h>）
 */
static void gather_chars_demo(void)
{
    char arr1[] = "welcome to bit...";
    char arr2[20];
    int left = 0;
    int right = (int)strlen(arr1) - 1;

    memset(arr2, '#', strlen(arr1));   /* 和博客一样：先用 17 个 '#' 占位 */
    arr2[strlen(arr1)] = '\0';

    printf("---------- 5. 经典题 1：字符从两端向中间汇聚 ----------\n");
    printf("原文：%s（长度 %d）\n\n", arr1, right + 1);

    while (left <= right)
    {
        arr2[left] = arr1[left];
        arr2[right] = arr1[right];
        printf("%s\n", arr2);
        Sleep(1000);
        left++;
        right--;
    }
}

/* ================= 6. 经典题 2：二分查找 ================= */

/*
 * 前提：数组有序；每比一次范围减半
 * mid 用 left + (right - left) / 2 的防溢出写法
 */
static void binary_search_demo(void)
{
    int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    int key = 0;
    int left = 0;
    int right = (int)(sizeof(arr) / sizeof(arr[0])) - 1;
    int find = 0;
    int count = 0;

    printf("---------- 6. 经典题 2：二分查找 ----------\n");
    printf("有序数组：1 2 3 4 5 6 7 8 9 10\n");
    if (read_int("请输入要查找的 key>: ", &key) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    while (left <= right)
    {
        int mid = left + (right - left) / 2;

        count++;
        printf("第 %d 次：left = %2d, right = %2d, mid = %d, arr[mid] = %2d",
               count, left, right, mid, arr[mid]);

        if (arr[mid] > key)
        {
            printf(" > %d，往左找\n", key);
            right = mid - 1;
        }
        else if (arr[mid] < key)
        {
            printf(" < %d，往右找\n", key);
            left = mid + 1;
        }
        else
        {
            printf(" == %d，找到了，下标是 %d\n", key, mid);
            find = 1;
            break;
        }
    }

    if (!find)
    {
        printf("找不到 %d（循环因为 left > right 结束，区间为空）\n", key);
    }
    printf("一共比较 %d 次。\n", count);
}

/* ================= 7. 变长数组说明 ================= */

/*
 * C99 允许用变量指定数组大小（VLA），例如（gcc 可用，VS2022 不支持）：
 *     int n = 0;
 *     scanf("%d", &n);   运行时才确定大小
 *     int arr[n];
 */
static void vla_info_demo(void)
{
    printf("---------- 7. 变长数组（VLA，了解） ----------\n");
    printf("C99 允许用变量指定数组大小，gcc 示例：\n");
    printf("    int n = 0;\n");
    printf("    scanf(\"%%d\", &n);   /* 运行时才确定大小 */\n");
    printf("    int arr[n];\n\n");
    printf("【易错】\n");
    printf("  1. “变长”是指大小可以在运行时用变量指定，不是大小可变；\n");
    printf("  2. 变长数组不能初始化；\n");
    printf("  3. VS2022 不支持变长数组，想试要在 gcc 上。\n");
    printf("日常写代码：数组大小尽量用常量；确实需要“按输入决定大小”且编译器支持时，再考虑 VLA。\n");
}

/* ================= 菜单 ================= */

static void menu(void)
{
    printf("\n====== C语言复习：数组（第 5 讲） ======\n");
    printf(" 1. 数组创建与初始化演示\n");
    printf(" 2. 一维数组：输入 10 个数并遍历打印\n");
    printf(" 3. 内存布局：打印相邻元素地址（int / char）\n");
    printf(" 4. 二维数组：初始化与双重循环遍历\n");
    printf(" 5. 经典题 1：字符从两端向中间汇聚\n");
    printf(" 6. 经典题 2：二分查找\n");
    printf(" 7. 变长数组说明（VS2022 不支持）\n");
    printf(" 0. 退出\n");
    printf("======================================\n");
}

int main(void)
{
    int input = -1;

    do
    {
        menu();

        {
            int ret = read_int("请选择>: ", &input);
            if (ret < 0)
            {
                printf("\n输入结束，退出程序。\n");
                break;
            }

            if (ret == 1)
            {
                switch (input)
                {
                case 1:
                    arr_init_demo();
                    break;
                case 2:
                    arr_1d_demo();
                    break;
                case 3:
                    arr_memory_demo();
                    break;
                case 4:
                    arr_2d_demo();
                    break;
                case 5:
                    gather_chars_demo();
                    break;
                case 6:
                    binary_search_demo();
                    break;
                case 7:
                    vla_info_demo();
                    break;
                case 0:
                    printf("退出程序，数组复习愉快。\n");
                    break;
                default:
                    printf("选择无效，请输入 0~7。\n");
                    break;
                }
            }
        }
    } while (input != 0);

    return 0;
}
