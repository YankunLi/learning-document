#include <string.h>
#include <stdio.h>

int main()
{
    char *str1="aaaaakkkeeee";    //str1与str2中没有相同的字符
    char *str2="bbbcccddd"; 

    int inttemp;

    inttemp=strcspn(str1,str2);   //用strcspn函数
    printf("The first index of the character both in str1 and str2: %d  \n", inttemp);

    str1="aaaaakkkeeee";  
    str2="John,he like writing!"; 
    inttemp=strcspn(str1,str2);   //将str2中的每个字符均与str1中的匹配，如果这个字符在str1中出现过，则返回这个字符在str1中的索引值
    printf("The first index of the character both in str1 and str2: %d  \n", inttemp);
    return 0;
}
