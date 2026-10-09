#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

/* ================= 经典习题 1~10 ================= */

/* 1. 判奇数/偶数（n % 2 != 0 对负数也成立） */
static void ex_odd_even(void)
{
    int n;

    if (read_int("请输入一个整数>: ", &n) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    if (n % 2 != 0)
        printf("%d 是奇数\n", n);
    else
        printf("%d 是偶数\n", n);
}

/* 2. 成年判断 */
static void ex_adult(void)
{
    int age;

    if (read_int("请输入年龄>: ", &age) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    if (age >= 18)
        printf("%d 岁：成年了\n", age);
    else
        printf("%d 岁：还没成年\n", age);
}

/* 3. 正负零 */
static void ex_sign(void)
{
    int n;

    if (read_int("请输入一个整数>: ", &n) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    if (n > 0)
        printf("%d 是正数\n", n);
    else if (n < 0)
        printf("%d 是负数\n", n);
    else
        printf("输入的是零\n");
}

/* 4. 嵌套判断奇偶 */
static void ex_nested_odd_even(void)
{
    int n;

    if (read_int("请输入一个整数>: ", &n) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    if (n >= 0)
    {
        if (n % 2 == 0)
            printf("%d 是非负偶数\n", n);
        else
            printf("%d 是正奇数\n", n);
    }
    else
    {
        if (n % 2 == 0)
            printf("%d 是负偶数\n", n);
        else
            printf("%d 是负奇数\n", n);
    }
}

/* 5. 年龄段：<18 少年 / 18~44 青年 / 45~59 中老年 / 60~89 老年 / >=90 老寿星 */
static void ex_age_stage(void)
{
    int age;

    if (read_int("请输入年龄>: ", &age) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    if (age < 0)
        printf("年龄不能为负数\n");
    else if (age < 18)
        printf("%d 岁：少年\n", age);
    else if (age <= 44)
        printf("%d 岁：青年\n", age);
    else if (age <= 59)
        printf("%d 岁：中老年\n", age);
    else if (age <= 89)
        printf("%d 岁：老年\n", age);
    else
        printf("%d 岁：老寿星\n", age);
}

/* 6. 闰年判断 */
static void ex_leap_year(void)
{
    int year;

    if (read_int("请输入年份>: ", &year) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        printf("%d 是闰年\n", year);
    else
        printf("%d 不是闰年\n", year);
}

/* 7. 1~100 之间 3 的倍数之和（i += 3 优化写法 + 逐个验证） */
static void ex_sum_3(void)
{
    int i;
    int sum = 0;
    int sum2 = 0;

    for (i = 3; i <= 100; i += 3)
    {
        sum += i;
    }

    for (i = 1; i <= 100; i++)
    {
        if (i % 3 == 0)
        {
            sum2 += i;
        }
    }

    printf("优化写法（i = 3; i <= 100; i += 3）：%d\n", sum);
    printf("逐个验证（i %% 3 == 0）：%d\n", sum2);
    printf("两种写法结果一致：%s\n", sum == sum2 ? "是" : "否");
}

/* 8. 逆序打印整数每一位（%10 取末位，/10 去掉末位） */
static void ex_reverse_digits(void)
{
    int n;

    if (read_int("请输入一个整数>: ", &n) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    printf("%d 逆序打印：", n);
    if (n < 0)
    {
        printf("-");
        n = -n;
    }

    if (n == 0)
    {
        printf("0");
    }

    while (n > 0)
    {
        printf("%d ", n % 10);
        n = n / 10;
    }
    printf("\n");
}

/* 9. 计算整数位数（do-while 很合适，0 也能数成 1 位） */
static void ex_digit_count(void)
{
    int n;
    int tmp;
    int cnt = 0;

    if (read_int("请输入一个整数>: ", &n) != 1)
    {
        printf("本题结束。\n");
        return;
    }

    tmp = (n < 0) ? -n : n;

    do
    {
        cnt++;
        tmp = tmp / 10;
    } while (tmp);

    printf("%d 共有 %d 位\n", n, cnt);
}

/* 10. 100~200 之间的素数：外层产生数，内层 2~i-1 试除，flag 标记 + break */
static void ex_primes(void)
{
    int i;
    int j;
    int count = 0;

    printf("100~200 之间的素数：\n");
    for (i = 100; i <= 200; i++)
    {
        int is_prime = 1;

        for (j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                is_prime = 0;
                break;
            }
        }

        if (is_prime)
        {
            printf("%d ", i);
            count++;
            if (count % 10 == 0)
            {
                printf("\n");
            }
        }
    }
    if (count % 10 != 0)
    {
        printf("\n");
    }
    printf("共 %d 个素数。\n", count);
}

/* ================= 11~12 猜数字游戏 ================= */

/* 11. 基础版：1~100 随机数（rand() % 100 + 1），反复猜，猜对结束 */
static void guess_game_basic(void)
{
    int r = rand() % 100 + 1;
    int guess = 0;

    printf("\n--- 猜数字（基础版）：电脑已生成 1~100 的数 ---\n");
    while (1)
    {
        int ret = read_int("请猜数字>: ", &guess);
        if (ret < 0)
        {
            printf("输入结束，本局结束。\n");
            break;
        }
        if (ret == 0)
        {
            continue;
        }

        if (guess < r)
            printf("猜小了\n");
        else if (guess > r)
            printf("猜大了\n");
        else
        {
            printf("恭喜你，猜对了\n");
            break;
        }
    }
}

/* 12. 限 5 次机会：猜错一次 count--，循环结束 count == 0 就公布正确答案 */
static void guess_game_limited(void)
{
    int r = rand() % 100 + 1;
    int guess = 0;
    int count = 5;
    int win = 0;

    printf("\n--- 猜数字（限 5 次机会）：1~100 ---\n");
    while (count)
    {
        int ret = read_int("请猜数字>: ", &guess);
        if (ret < 0)
        {
            printf("输入结束，本局结束。\n");
            break;
        }
        if (ret == 0)
        {
            continue;
        }

        if (guess < r)
        {
            printf("猜小了\n");
            count--;
        }
        else if (guess > r)
        {
            printf("猜大了\n");
            count--;
        }
        else
        {
            printf("恭喜你，猜对了\n");
            win = 1;
            break;
        }

        if (count > 0)
        {
            printf("还剩 %d 次机会\n", count);
        }
    }

    if (!win && count == 0)
    {
        printf("你失败了，正确值是 %d\n", r);
    }
}

/* ================= 菜单 ================= */

static void menu(void)
{
    printf("\n====== C语言复习：分支和循环 经典习题 ======\n");
    printf(" 1. 判奇数/偶数          2. 成年判断\n");
    printf(" 3. 正负零               4. 嵌套判断奇偶\n");
    printf(" 5. 年龄段               6. 闰年判断\n");
    printf(" 7. 3 的倍数之和         8. 逆序打印整数每一位\n");
    printf(" 9. 计算整数位数        10. 100~200 之间的素数\n");
    printf("11. 猜数字（基础版）    12. 猜数字（限 5 次）\n");
    printf(" 0. 退出\n");
    printf("==========================================\n");
}

int main(void)
{
    int input = -1;

    /* 伪随机三件套：srand 播一次种、rand 负责取数、time 当种子（别放在循环里） */
    srand((unsigned int)time(NULL));

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
                    ex_odd_even();
                    break;
                case 2:
                    ex_adult();
                    break;
                case 3:
                    ex_sign();
                    break;
                case 4:
                    ex_nested_odd_even();
                    break;
                case 5:
                    ex_age_stage();
                    break;
                case 6:
                    ex_leap_year();
                    break;
                case 7:
                    ex_sum_3();
                    break;
                case 8:
                    ex_reverse_digits();
                    break;
                case 9:
                    ex_digit_count();
                    break;
                case 10:
                    ex_primes();
                    break;
                case 11:
                    guess_game_basic();
                    break;
                case 12:
                    guess_game_limited();
                    break;
                case 0:
                    printf("退出程序，分支和循环复习愉快。\n");
                    break;
                default:
                    printf("选择无效，请输入 0~12。\n");
                    break;
                }
            }
        }
    } while (input != 0);

    return 0;
}
