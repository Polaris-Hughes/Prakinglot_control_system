#ifndef FUNC_C
#define FUNC_C


#include "data.h"
#include <ctype.h>

int Find_MinDis(int dis_count[District])
{
    int min = dis_count[0];
    int min_index = 0;
    for (int i = 1; i < District; i++)
    {
        if (dis_count[i] < min)
        {
            min = dis_count[i];
            min_index = i;
        }
    }
    if (min_index == Spacenum_Max)
    {
        min_index = -1;
    }
    return min_index;
}

int Pricing(int time)
{
    int price = 0;
    if (time <= 30)
    {
        price = 0;
    }
    else if (time <= 60)
    {
        price = 5;
    }
    else if (time <= 120)
    {
        price = 10;
    }
    else
    {
        price = 10 + (time - 120) / 60 * 5;
    }
    return price;
}

int is_carnum_valid(char* car_num)
{
    // 检查车牌长度
    int len = strlen(car_num);
    // printf("%d %s\n", len, car_num);
    if (!(len == CarNum_Max-1 || len == CarNum_Max-2))
    {
        return 0; // 车牌长度不正确
    }

    if (!isupper(car_num[3]))
    {
        return 0; // 第二位不是大写字母
    }

    if (len==CarNum_Max-1)//新能源车牌
    {
        if (car_num[4]!='D' && car_num[4]!='F')
        {
            return 0; // 第三位不是D或F
        }
        
    }

    for (int i = 4; i < len; i++)
    {
        if (!isalnum(car_num[i]) || islower(car_num[i]))
        {
            return 0; // 剩余字符不是数字或大写字母
        }
    }

    return 1; // 车牌合法
}


void Enter_Report(char car_num[CarNum_Max], char car_type[CarType_Max], int enter_time, int dis, int space)
{
    printf("车牌号为 %s的%s车辆在%d时%d分进入停车场,停在%c区%d号车位\n", car_num, car_type, enter_time/60,enter_time%60,Dis_Name[dis], space);
}

void Leave_Report(char car_num[CarNum_Max], char car_type[CarType_Max], int enter_time, int leave_time,int Occ_time, int price, int dis, int space)
{
    printf("车牌号为 %s的%s车辆在%d时%d分进入停车场,停在%c区%d号车位,%d时%d分离开,共停留%d分钟,应缴费%d元\n", car_num, car_type,  enter_time/60,enter_time%60,  Dis_Name[dis], space, leave_time/60,leave_time%60,Occ_time, price);
}

void Park_Car(char car_num[CarNum_Max], char car_type[CarType_Max], int enter_time)
{
    // illegal situation slove
    
    // int flag = is_carnum_valid(car_num);
    // if (flag == 0)
    // {
    //     printf("车牌号不合法\n");
    //     return;
    // }
    int min_index = Find_MinDis(Dis_Count);
    if (min_index == -1)
    {
        printf("停车场已满\n");
        return;
    }
    // finding space
    int min = Dis_Count[min_index];
    int min_space = 0;
    for (int i = 0; i < Spacenum_Max; i++)
    {
        if (parkinglot[min_index][i].status == Empty)
        {
            min_space = i;
            break;
        }
    }
    // parking
    parkinglot[min_index][min_space].status = Occupied;
    parkinglot[min_index][min_space].enter_time = enter_time;
    strcpy(parkinglot[min_index][min_space].car_num, car_num);
    strcpy(parkinglot[min_index][min_space].car_type, car_type);
    Dis_Count[min_index]++;
    Enter_Report(car_num, car_type, enter_time, min_index+1, min_space + 1);
}

void Leave_Car(char car_num[CarNum_Max], int leave_time)
{
    int Occ_time, price;
    for (int i = 0; i < District; i++)
    {
        for (int j = 0; j < Spacenum_Max; j++)
        {
            if (strcmp(parkinglot[i][j].car_num, car_num) == 0)
            {
                // report and charge
                Occ_time = leave_time - parkinglot[i][j].enter_time;
                while(Occ_time<0)
                {
                    Occ_time+=24*60;
                }
                price = Pricing(Occ_time);
                Leave_Report(car_num, parkinglot[i][j].car_type, parkinglot[i][j].enter_time, leave_time,Occ_time, price, i + 1, j + 1);
                // leaving
                parkinglot[i][j].status = Empty;
                parkinglot[i][j].enter_time = -1;
                strcpy(parkinglot[i][j].car_num, "");
                strcpy(parkinglot[i][j].car_type, "");
                Dis_Count[i]--;
                break;
            }
        }
    }
}

void check_empty_space()
{
    for (int i = 0; i < District; i++)
    {
        int empty_count=0;
        for (int j = 0; j < Spacenum_Max; j++)
        {
            
            if (parkinglot[i][j].status == Empty)
            {
                printf("位于%c区域, 编号为%d的停车位为空\n",Dis_Name[i+1], j+1);
                empty_count++;
            }
            
        }
        printf("%c区域还有%d个空位\n", Dis_Name[i+1], empty_count);
    }
}

void search_carnum(char car_num[CarNum_Max])
{
    for (int i = 0; i < District; i++)
    {
        for (int j = 0; j < Spacenum_Max; j++)
        {
            if (strcmp(parkinglot[i][j].car_num, car_num) == 0)
            {
                printf("车牌号为 %s的车辆停在%c区域, 编号为%d的停车位\n", car_num, Dis_Name[i+1], j + 1);
                return;
            }
        }
    }
    printf("未找到车牌号为 %s的车辆\n", car_num);
}

void search_cartype(char car_type[CarType_Max])
{
    for (int i = 0; i < District; i++)
    {
        for (int j = 0; j < Spacenum_Max; j++)
        {
            if (strcmp(parkinglot[i][j].car_type, car_type) == 0)
            {
                printf("有一辆车型为 %s的车停在%c区域, 编号为%d的停车位\n", car_type, Dis_Name[i+1], j + 1);
                return;
            }
        }
    }
    printf("未找到车型为 %s的车辆\n", car_type);
}



void Init_Parking(int district, int spacenum_max)
{
    for (int i = 0; i < district; i++)
    {
        for (int j = 0; j < spacenum_max; j++)
        {
            parkinglot[i][j].district = i + 1;    // 例如，使用区号作为区域编号
            parkinglot[i][j].space_num = j + 1;   // 假设空间编号是连续的
            parkinglot[i][j].status = Empty;      // 假设0表示空闲
            parkinglot[i][j].enter_time = -1;     // 初始化进入时间为0
            strcpy(parkinglot[i][j].car_num, ""); // 初始化车牌号为空字符串
            strcpy(parkinglot[i][j].car_type, "");
        }
    }
}

#endif