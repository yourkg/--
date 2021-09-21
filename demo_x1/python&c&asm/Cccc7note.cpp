/*
//编程语言补课复习必备 http://c.biancheng.net/view/3294.html
//两种风味汇编的对比 https://www.cnblogs.com/hdk1993/p/4820353.html 
//笔记1:写好这个文件后，绝对不会再从windows上用AT&T格式。。。参考http://cn.voidcc.com/question/p-kytnucnp-ds.html 撞墙了，对于windows，DOS，INT 21N, BIOS, INT  10N理解欠缺  
//笔记2:以下为windwos下基本没bug的一种妥协写法，linux估计通用，需要时参考上面的风味对比重写，修改一下即可。 总之在32位下安全性 > 64位 ; 回调c方式 > INT 21N(理论OK) > INT 10N(未知) 
//笔记3：https://blog.csdn.net/FreeeLinux/article/details/85042687 [32v 64v]      https://www.cnblogs.com/pingf/archive/2011/03/09/1978263.html [int 10n]
//
//后记1：有空的时候用纯DOS,各种系统包括windos再测试一下 ，编译器&纯INTER格式等 
//后记2:附属产物强大的汇编操作之寄存器间接寻址https://blog.csdn.net/m0_37806112/article/details/80549927  https://blog.csdn.net/dlh0313/article/details/52204071
//后记3:内联学习https://www.cnblogs.com/pengdonglin137/p/3329501.html#_lab2_1_6  https://www.cnblogs.com/lyukashin/articles/1302400.html
*/

//以下demo代码以为注释部分为准，如果只回顾python调c函数的用法请看隔壁day7.py文件的资料

#include<stdio.h>


extern "C" {//括号里的按照c风味编译 https://www.cnblogs.com/night-ride-depart/p/4907613.html
int main(){
char *a = (char *)"Hello, world.", *b = (char *)"ASM print：";

//const char *c=(const char *)"number is %d ";
int cn=123;
int *cb=&cn;
printf("C print：%s\n",a);
int cm=456;
printf("\n cm is ，%d,%x\n\n",cm,&cm);
/* 
__asm__ __volatile__(
"value : .int 10\n\t"
"movl $value, %ecx;"
"movl %1, %%eax;"
"movl %%eax, %0;"
:"=m"(b)                                //如果往寄存器里装入   参考 https://blog.csdn.net/neuq_jtxw007/article/details/78112672
:"m"(a)                                 // 64位系统下就会报错 40 ... Error: unsupported instruction `mov' 改成"m"往内存里放可以避免。或者改编译器指定32位 
:"%eax"
);
printf("Result: %s, %s\n", a, b);*/ 
//printf("\n%s，%s\n\n",a,b);
__asm__ __volatile__(
//"abc: .int 10\n\t"
//"movl abc, %edi\n\t"
//"movl saved_sp,%%edi\n\t"  //       参考https://www.it1352.com/298141.html  真折腾 依然有问题，暂时搁置 
//"movl 4(%%edi),%%ebx\n\t"
//"pushl %%ebx\n\t" 
//"call _printf\n\t"
//"addl $8,%%esp\n\t"
//".code32\n\t"                                  //.code 16 gcc     https://www.cnblogs.com/youxia/p/linux008.html
//"subq %0,%%rsp\n\t"
//"movq %%rbp,(%%rsp)\n\t"     //https://www.cnblogs.com/czw52460183/p/10018295.html  push l q w b 
//"push %0\n\t"
//"addl $8,%%esp\n\t"                               
//"call _printf\n\t"              //x64 call 问题？  http://www.masm32.com/board/index.php?topic=3101.0
//"pop %1\n\t" //"或者 操作addl $4,%%esp\n\t"
                    //pushl在64位的时候也出问题！ 
//"movl $0, %%eax\n\t"
//"cpuid\n\t"
//
//"movl %1, %%edi\n\t"

//
//"pushl %1\n\t"      //  终极: https://www.cnblogs.com/fqwCpp/p/5643963.html
//"push $1\n\t"      //https://blog.csdn.net/feng_zh/article/details/7075986?utm_medium=distribute.pc_relevant.none-task-blog-OPENSEARCH-1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-OPENSEARCH-1

/*
"movq %0, %%rax\n\t"    //注意先后 每一个操作都会移动栈顶，观察上是 
"subq $8, %%rsp\n\t"         //https://www.it610.com/article/4891069.htm
"movq %%rax,(%%rsp)\n\t"     //这三句相当于pushl %0  
*/

//"movl %0, %%eax\n\t"     //https://www.it610.com/article/4891069.htm
//"subl $4, %%esp\n\t"      //
//"movl %%eax,(%%esp)\n\t" 

//"pushl %0\n\t"
//"movl %0,%%ebp\n\t"
//"movl %0,%%ebx\n\t"
//"add $0,%rsp\n\t"
//"movq %0,%%rbx\n\t"
//"movq %%rbx,(%%rsp)\n\t"
//"subl $12,%%esp\n\t"
//"movl %%ebx,(%%esp)\n\t"                     // https://blog.csdn.net/wang010366/article/details/52015264
//"call puts\n\t"            //puts()https://blog.csdn.net/wuff1988/article/details/9312559   https://blog.csdn.net/qq_31155883/article/details/105884907
//"subq %8, %%rsp\n\t"
//"movq %%rip, %%rsp\n\t"
//"movq %%rax ,%%rsi\n\t"
//"movq %%rax ,%%rdi\n\t"
//"movq $0 ,%%rax\n\t"
/*
"subq $0x20, %%rsp\n\t"  
"call puts"
*/

//"subl $8, %%esp\n\t"  
//"call _puts"

//"pushq %%eip\n\t"
//"movq _puts, %%eip\n\t"   //https://comp.lang.asm.x86.narkive.com/Rnoa0LiQ/bad-register-name-eip 终极终极 
//"addl $8,%%esp\n\t"
//"pushl $0\n\t"
//"call _exit"
//".code16\n\t"
//"mov $'G', %%bl\n\t"        //别人家的汇编 http://www.myexception.cn/assembly-language/201870.html  DEVC就一个沙雕 
//"push %%dx\n\t"
//"push %%ax\n\t"
//"mov $0x02,%%ah\n\t"       //MS -DOS就是个沙雕！ 
//"mov %%al,%%dl\n\t"
//"int $0x10\n\t"
//"pop %%ax\n\t"
//"pop %%dx\n\t"
//"movl $6, %0" 


                                //https://blog.csdn.net/c5113620/article/details/84928512 
//"movl $0x09, %%eax;"
//"int $0x21"
"movq %2 ,%%rbx\n\r"
"addq $3,(%%rbx)\n\r"
"movq %1 ,%%rax\n\r"
"addq $3, %%rax\n\r"
"movq %%rax ,%0\n\r"
:"=m"(cm)                                //如果往寄存器里装入   参考 https://blog.csdn.net/neuq_jtxw007/article/details/78112672
:"m"(cn),"m"(cb)                               // 64位系统下就会报错 40 ... Error: unsupported instruction `mov' 改成"m"往内存里放可以避免。或者改编译器指定32位 
:"%rax"
);
if(cm==129)
printf("\n%s %s，%d,%x\n\n",b,a,cm,&cm);

return 0;
}
}
