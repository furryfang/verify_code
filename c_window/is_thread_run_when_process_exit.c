#include<windows.h>
#include<stdio.h>

/* 
编译器：MinGW
语言：c
系统：windows11
作用：验证当主进程退出后子线程是否会退出。
结论：会退出
 */
DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter);

int iIndx = 0;
int iTickets = 100;

int main()
{
	HANDLE hThread1;
    int count = 0;

	hThread1 = CreateThread(NULL, 0, Fun1Proc, NULL, 0, NULL);
	CloseHandle(hThread1);
    scanf("%d",&count);
	system("pause");
    return 0;
}

DWORD WINAPI Fun1Proc(__in  LPVOID lpParameter)
{
    FILE *file;
    int i = 0;
    char str[25] = { 0 };

	while (1)
	{
		printf("running\n");
		Sleep(2000);

        itoa(i, str, 10);
        
        file = fopen(str, "w");
        if (file == NULL) {
            perror("Error opening file");
            return EXIT_FAILURE; 
        }
    
        fprintf(file, "Hello, World!");
        fclose(file);
        i++;
	}

	return 0;
}
