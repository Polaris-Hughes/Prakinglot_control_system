#ifndef DATA_C
#define DATA_C

#define District 5
#define Spacenum_Max 5
#define Empty 0
#define Occupied 1
#define CarNum_Max 11//中文占三个字符
#define CarType_Max 10

#include <string.h>
#include <stdio.h>
int Dis_Count[District]={0};
// char Car_Type[5][CarType_Max]={"小型车","中型车","大型车","摩托车","新能源车"};
char Dis_Name[District+1]={'0','A','B','C','D','E'};

typedef struct parking
{
    int district;
    int space_num;
    int status;
    int enter_time;
    char car_num[CarNum_Max];
    char car_type[CarType_Max];
} PARK;

PARK parkinglot[District][Spacenum_Max];

#endif // DATA_H
