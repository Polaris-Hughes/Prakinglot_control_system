#ifndef MENU_C
#define MENU_C

#include <stdio.h>
#include <windows.h>

#include "data.h" // 确保这里包含了所有需要的数据结构和变量的定义

// 声明您之前定义的函数
int Find_MinDis(int dis_count[]);
int Pricing(int time);
int is_carnum_valid(char car_num[]);
void Leave_Report(char car_num[], char car_type[], int enter_time, int leave_time, int price, int dis, int space);
void Park_Car(char car_num[], char car_type[], int enter_time);
void Leave_Car(char car_num[], int leave_time);
void check_empty_space();
void search_carnum(char car_num[]);
void search_cartype(char car_type[]);
void Init_Parking(int district, int spacenum_max);

void clear_input_buffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ; // 读取并丢弃直到换行符或文件结束
}

int GBKToUTF8(char *lpGBKStr, char *lpUTF8Str, int nUTF8StrLen)
{
    // 获取转换到宽字符（UTF-16）所需的缓冲区大小
    int nWideCharLen = MultiByteToWideChar(CP_ACP, 0, lpGBKStr, -1, NULL, 0);
    if (nWideCharLen <= 0)
        return -1;

    // 分配宽字符缓冲区
    WCHAR *lpWideCharStr = (WCHAR *)malloc(nWideCharLen * sizeof(WCHAR));
    if (lpWideCharStr == NULL)
        return -1;

    // GBK转宽字符（UTF-16）
    MultiByteToWideChar(CP_ACP, 0, lpGBKStr, -1, lpWideCharStr, nWideCharLen);

    // 获取转换到UTF-8所需的缓冲区大小
    int nUTF8CharLen = WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, -1, NULL, 0, NULL, NULL);
    if (nUTF8CharLen > nUTF8StrLen)
    {
        free(lpWideCharStr);
        return -1;
    }

    // 宽字符（UTF-16）转UTF-8
    WideCharToMultiByte(CP_UTF8, 0, lpWideCharStr, -1, lpUTF8Str, nUTF8CharLen, NULL, NULL);

    // 释放宽字符缓冲区
    free(lpWideCharStr);

    return nUTF8CharLen;
}

void scanf_c(char *car_num, int len)
{
    scanf("%s", car_num);
    GBKToUTF8(car_num, car_num, len);
}

void display_menu()
{
    int choice;
    char car_num[CarNum_Max];
    char car_type[CarType_Max];
    int enter_time_h, enter_time_m, leave_time_h, leave_time_m;
    printf("\n欢迎来到停车场管理系统\n");

    while (1)
    {
        printf("\n1. 停车\n");
        printf("2. 离开\n");
        printf("3. 检查空位\n");
        printf("4. 查找车辆位置\n");
        printf("5. 查找车型\n");
        printf("6. 初始化停车场\n");
        printf("7. 退出\n");
        printf("请选择操作（输入1-7）: ");

        scanf("%d", &choice);
        clear_input_buffer();

        switch (choice)
        {
        case 1:
            printf("请输入车牌号: ");
            scanf_c(car_num, CarNum_Max);
            //illegal carnum detact
            int flag = is_carnum_valid(car_num);
            if (flag == 0)
            {
                printf("车牌号不合法\n");
                break;
            }
            // printf_s("%s\n", car_num);
            printf("请输入车型: ");
            scanf("%s", car_type);
            printf("请输入进入时间: ");
            scanf("%d:%d", &enter_time_h, &enter_time_m);
            Park_Car(car_num, car_type, enter_time_h * 60 + enter_time_m);
            break;
        case 2:
            printf("请输入车牌号: ");
            scanf_c(car_num, CarNum_Max);
            printf("请输入离开时间: ");
            scanf("%d:%d", &leave_time_h, &leave_time_m);
            Leave_Car(car_num, leave_time_h * 60 + leave_time_m);
            break;
        case 3:
            check_empty_space();
            break;
        case 4:
            printf("请输入车牌号: ");
            scanf_c(car_num, CarNum_Max);
            search_carnum(car_num);
            break;
        case 5:
            printf("请输入车型: ");
            scanf("%s", car_type);
            search_cartype(car_type);
            break;
        case 6:
            Init_Parking(District, Spacenum_Max);
            printf("停车场初始化完成。\n");
            break;
        case 7:
            printf("退出系统。\n");
            return;
        default:
            printf("无效选择,请输入1-7之间的数字。\n");
            break;
        }
    }
}

#endif