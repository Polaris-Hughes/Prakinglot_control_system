#include "func.h"
#include "menu.h"
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "zh_CN.UTF-8");
    SetConsoleCP(936);
    SetConsoleOutputCP(65001);

    Init_Parking(District, Spacenum_Max);
    //printf("%d", strlen("这A66666"));
    display_menu();
    return 0;
}
// AAAB6666 SUV 12:30 这A66666