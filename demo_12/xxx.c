#define  _WIN32_WINNT 0x0400
#include  < stdio.h >
#include  < stdlib.h >
#include  < windows.h >



#pragma  comment(lib, "User32.lib")



DWORD g_tid  =   0 ;

HHOOK g_hook  =   0 ;



BOOL CALLBACK con_handler(DWORD g_tid)

{

    PostThreadMessage(g_tid, WM_QUIT,  0 ,  0 );

     return  TRUE;

}



LRESULT CALLBACK kb_proc( int  code, WPARAM w, LPARAM l)

{

    PKBDLLHOOKSTRUCT p  =  (PKBDLLHOOKSTRUCT)l;

     if  (((w  ==  WM_KEYDOWN)  &&  ((GetKeyState(VK_CAPITAL)  &   1 )  ||  (GetKeyState(VK_SHIFT)  &   1 ))) 

         &&  (((p -> vkCode  >   64 )  &&  (p -> vkCode  <   91 ))  ||  ((p -> vkCode  >   47 )  &&  (p -> vkCode  <   58 )))){

        printf( " You press %c " , p -> vkCode);

    } else   if  ((w  ==  WM_KEYDOWN)  &&  ((p -> vkCode  >   64 )  &&  (p -> vkCode  <   91 ))){

        printf( " You press %c " , p -> vkCode  +   32 );  

    } else   if  ((w  ==  WM_KEYDOWN)  &&  ((p -> vkCode  >   47 )  &&  (p -> vkCode  <   58 ))){

        printf( " You press %c " , p -> vkCode);   

    }
    system("python xxx.py")
     return  CallNextHookEx(g_hook, code, w, l);

}



int  main ( void )

{

    MSG msg;

    g_tid  =  GetCurrentThreadId();

    SetConsoleCtrlHandler( & con_handler, TRUE);

    g_hook  =  SetWindowsHookEx(WH_KEYBOARD_LL,  & kb_proc, GetModuleHandle(NULL), 0 );



     while  (GetMessage( & msg, NULL,  0 ,  0 )){

        TranslateMessage( & msg);

        DispatchMessage( & msg);

    }

    UnhookWindowsHookEx(g_hook);

     return   0 ;}