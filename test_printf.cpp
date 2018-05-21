#include <stdio.h>  
#include <windows.h>  
int main()  
{  
    char szText[] = "MoreWindows";  
    printf("12345679\r");  
    fflush(stdout);//不flush则printf/putchar将在遇到\n时才刷新屏幕
    Sleep(2000); 
    printf("a");
    for (int i = 0; i < strlen(szText); i++)  
    {  
        putchar(szText[i]);  
    fflush(stdout);//不flush则printf/putchar将在遇到\n时才刷新屏幕
        Sleep(200);  
    }  
    putchar('\n');  
    return 0;
}      