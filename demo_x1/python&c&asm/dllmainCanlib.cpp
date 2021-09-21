/* Replace "dll.h" with the name of your header */
#include "dll.h"
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
DLLIMPORT void HelloWorld();
#if 1
#define DLL_API __declspec(dllexport)
#else
#define DLL_API __declspec(dllimport)
#endif



// Point 
struct Point
{
    float x, y;
};

static Point* position = NULL;

extern "C" {

    DLL_API int add(int a, int b)
    {
        return a + b;
    }

    DLL_API float addf(float a, float b)
    {
        return a + b;
    }

    DLL_API void print_point(Point* p)
    {
        if (p)
            printf("position x %f y %f", p->x, p->y);
    }
}

extern "C" {
DLL_API int asmp(){
char *a = (char *)"Hello, world.", *b = (char *)"ASM print£º";


int cn=123;
int *cb=&cn;
printf("C print£º%s\n",a);
int cm=456;
printf("\n cm is £¬%d,%x\n\n",cm,&cm);

__asm__ __volatile__(

"movq %2 ,%%rbx\n\r"
"addq $3,(%%rbx)\n\r"
"movq %1 ,%%rax\n\r"
"addq $3, %%rax\n\r"
"movq %%rax ,%0\n\r"
:"=m"(cm)                               
:"m"(cn),"m"(cb)                        
:"%rax"
);
if(cm==129)
printf("\n%s %s£¬%d,%x\n\n",b,a,cm,&cm);

return 0;
}
}

DLLIMPORT void HelloWorld()
{
	MessageBox(0, "Hello World from DLL!\n","Hi",MB_ICONINFORMATION);
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	switch(fdwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			break;
		}
		case DLL_PROCESS_DETACH:
		{
			break;
		}
		case DLL_THREAD_ATTACH:
		{
			break;
		}
		case DLL_THREAD_DETACH:
		{
			break;
		}
	}
	
	/* Return TRUE on success, FALSE on failure */
	return TRUE;
}
