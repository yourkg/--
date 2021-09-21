// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#define  _WIN32_WINNT 0x0400
#include  <stdio.h>
#include  <stdlib.h>
#include  <windows.h>
#pragma  comment(lib, "User32.lib")


DWORD g_tid = 0;
HHOOK g_hook = 0;


BOOL CALLBACK con_handler(DWORD g_tid)
{
    PostThreadMessage(g_tid, WM_QUIT, 0, 0);
    return  TRUE;
}

VOID KeyClick(const char* str) {
    puts(str);
    system(str);
    return ;
}


LRESULT CALLBACK kb_proc(int code, WPARAM w, LPARAM l)
{
    PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)l;
    if (((w == WM_KEYDOWN) && ((GetKeyState(VK_CAPITAL) & 1) || (GetKeyState(VK_SHIFT) & 1)))
        && (((p->vkCode > 64) && (p->vkCode < 91)) || ((p->vkCode > 47) && (p->vkCode < 58)))) {
        printf(" 1You press %c ", p->vkCode);
        int knum = p->vkCode - 48;
        printf("%d\n", knum);
        switch (knum)
        {
        case 0:
            KeyClick("python xxx.py --midiKey 0");
            break;
        case 1:
            KeyClick("python xxx.py --midiKey 1");
            break;
        case 2:
            KeyClick("python xxx.py --midiKey 2");
            break;
        case 3:
            KeyClick("python xxx.py --midiKey 3");
            break;
        case 4:
            KeyClick("python xxx.py --midiKey 4");
            break;
        case 5:
            KeyClick("python xxx.py --midiKey 5");
            break;
        case 6:
            KeyClick("python xxx.py --midiKey 6");
            break;
        case 7:
            KeyClick("python xxx.py --midiKey 7");
            break;
        case 8:
            KeyClick("python xxx.py --midiKey 8");
            break;
        case 9:
            KeyClick("python xxx.py --midiKey 9");
            break;
        default:
            break;
        }
    }
    else   if ((w == WM_KEYDOWN) && ((p->vkCode > 64) && (p->vkCode < 91))) {
        printf(" 2You press %c ", p->vkCode + 32);
    }
    else   if ((w == WM_KEYDOWN) && ((p->vkCode > 47) && (p->vkCode < 58))) {
        printf(" 3You press %c ", p->vkCode);
        int knum = p->vkCode - 48;
        printf("%d\n", knum);
        switch (knum)
        {
        case 0:
            KeyClick("python xxx.py --midiKey 0");
            break;
        case 1:
            KeyClick("python xxx.py --midiKey 1");
            break;
        case 2:
            KeyClick("python xxx.py --midiKey 2");
            break;
        case 3:
            KeyClick("python xxx.py --midiKey 3");
            break;
        case 4:
            KeyClick("python xxx.py --midiKey 4");
            break;
        case 5:
            KeyClick("python xxx.py --midiKey 5");
            break;
        case 6:
            KeyClick("python xxx.py --midiKey 6");
            break;
        case 7:
            KeyClick("python xxx.py --midiKey 7");
            break;
        case 8:
            KeyClick("python xxx.py --midiKey 8");
            break;
        case 9:
            KeyClick("python xxx.py --midiKey 9");
            break;
        default:
            break;
        }
    }
    return  CallNextHookEx(g_hook, code, w, l);
}

int  main(void)
{
    MSG msg;
    g_tid = GetCurrentThreadId();
    SetConsoleCtrlHandler(&con_handler, TRUE);
    g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, &kb_proc, GetModuleHandle(NULL), 0);
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    UnhookWindowsHookEx(g_hook);
    return   0;
}

/*
int main()
{
    std::cout << "Hello World!\n";
}
*/
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
