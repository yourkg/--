/*
//������Բ��θ�ϰ�ر� http://c.biancheng.net/view/3294.html
//���ַ�ζ���ĶԱ� https://www.cnblogs.com/hdk1993/p/4820353.html 
//�ʼ�1:д������ļ��󣬾��Բ����ٴ�windows����AT&T��ʽ�������ο�http://cn.voidcc.com/question/p-kytnucnp-ds.html ײǽ�ˣ�����windows��DOS��INT 21N, BIOS, INT  10N���Ƿȱ  
//�ʼ�2:����Ϊwindwos�»���ûbug��һ����Эд����linux����ͨ�ã���Ҫʱ�ο�����ķ�ζ�Ա���д���޸�һ�¼��ɡ� ��֮��32λ�°�ȫ�� > 64λ ; �ص�c��ʽ > INT 21N(����OK) > INT 10N(δ֪) 
//�ʼ�3��https://blog.csdn.net/FreeeLinux/article/details/85042687 [32v 64v]      https://www.cnblogs.com/pingf/archive/2011/03/09/1978263.html [int 10n]
//
//���1���пյ�ʱ���ô�DOS,����ϵͳ����windos�ٲ���һ�� ��������&��INTER��ʽ�� 
//���2:��������ǿ��Ļ�����֮�Ĵ������Ѱַhttps://blog.csdn.net/m0_37806112/article/details/80549927  https://blog.csdn.net/dlh0313/article/details/52204071
//���3:����ѧϰhttps://www.cnblogs.com/pengdonglin137/p/3329501.html#_lab2_1_6  https://www.cnblogs.com/lyukashin/articles/1302400.html
*/

//����demo������Ϊע�Ͳ���Ϊ׼�����ֻ�ع�python��c�������÷��뿴����day7.py�ļ�������

#include<stdio.h>


extern "C" {//������İ���c��ζ���� https://www.cnblogs.com/night-ride-depart/p/4907613.html
int main(){
char *a = (char *)"Hello, world.", *b = (char *)"ASM print��";

//const char *c=(const char *)"number is %d ";
int cn=123;
int *cb=&cn;
printf("C print��%s\n",a);
int cm=456;
printf("\n cm is ��%d,%x\n\n",cm,&cm);
/* 
__asm__ __volatile__(
"value : .int 10\n\t"
"movl $value, %ecx;"
"movl %1, %%eax;"
"movl %%eax, %0;"
:"=m"(b)                                //������Ĵ�����װ��   �ο� https://blog.csdn.net/neuq_jtxw007/article/details/78112672
:"m"(a)                                 // 64λϵͳ�¾ͻᱨ�� 40 ... Error: unsupported instruction `mov' �ĳ�"m"���ڴ���ſ��Ա��⡣���߸ı�����ָ��32λ 
:"%eax"
);
printf("Result: %s, %s\n", a, b);*/ 
//printf("\n%s��%s\n\n",a,b);
__asm__ __volatile__(
//"abc: .int 10\n\t"
//"movl abc, %edi\n\t"
//"movl saved_sp,%%edi\n\t"  //       �ο�https://www.it1352.com/298141.html  ������ ��Ȼ�����⣬��ʱ���� 
//"movl 4(%%edi),%%ebx\n\t"
//"pushl %%ebx\n\t" 
//"call _printf\n\t"
//"addl $8,%%esp\n\t"
//".code32\n\t"                                  //.code 16 gcc     https://www.cnblogs.com/youxia/p/linux008.html
//"subq %0,%%rsp\n\t"
//"movq %%rbp,(%%rsp)\n\t"     //https://www.cnblogs.com/czw52460183/p/10018295.html  push l q w b 
//"push %0\n\t"
//"addl $8,%%esp\n\t"                               
//"call _printf\n\t"              //x64 call ���⣿  http://www.masm32.com/board/index.php?topic=3101.0
//"pop %1\n\t" //"���� ����addl $4,%%esp\n\t"
                    //pushl��64λ��ʱ��Ҳ�����⣡ 
//"movl $0, %%eax\n\t"
//"cpuid\n\t"
//
//"movl %1, %%edi\n\t"

//
//"pushl %1\n\t"      //  �ռ�: https://www.cnblogs.com/fqwCpp/p/5643963.html
//"push $1\n\t"      //https://blog.csdn.net/feng_zh/article/details/7075986?utm_medium=distribute.pc_relevant.none-task-blog-OPENSEARCH-1&depth_1-utm_source=distribute.pc_relevant.none-task-blog-OPENSEARCH-1

/*
"movq %0, %%rax\n\t"    //ע���Ⱥ� ÿһ�����������ƶ�ջ�����۲����� 
"subq $8, %%rsp\n\t"         //https://www.it610.com/article/4891069.htm
"movq %%rax,(%%rsp)\n\t"     //�������൱��pushl %0  
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
//"movq _puts, %%eip\n\t"   //https://comp.lang.asm.x86.narkive.com/Rnoa0LiQ/bad-register-name-eip �ռ��ռ� 
//"addl $8,%%esp\n\t"
//"pushl $0\n\t"
//"call _exit"
//".code16\n\t"
//"mov $'G', %%bl\n\t"        //���˼ҵĻ�� http://www.myexception.cn/assembly-language/201870.html  DEVC��һ��ɳ�� 
//"push %%dx\n\t"
//"push %%ax\n\t"
//"mov $0x02,%%ah\n\t"       //MS -DOS���Ǹ�ɳ�� 
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
:"=m"(cm)                                //������Ĵ�����װ��   �ο� https://blog.csdn.net/neuq_jtxw007/article/details/78112672
:"m"(cn),"m"(cb)                               // 64λϵͳ�¾ͻᱨ�� 40 ... Error: unsupported instruction `mov' �ĳ�"m"���ڴ���ſ��Ա��⡣���߸ı�����ָ��32λ 
:"%rax"
);
if(cm==129)
printf("\n%s %s��%d,%x\n\n",b,a,cm,&cm);

return 0;
}
}
