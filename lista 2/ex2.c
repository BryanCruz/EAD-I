#include <stdio.h>

int main() {
    char *s1   = "Linguagem C";
    char s2[ ] = "Linguagem C";
    printf("%s\n", s1); printf("%s\n", s2);
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%s\n", s1+2);
    printf("%c\n", *(s1+2));
    printf("%p\n", &s2[2]); //=&(*(s2+2))
    printf(s2+2);
    printf(s2[2]);
    printf(s1[2]);
    s1 +=4;
    s1++;
    s2 +=4;
    s2++;

    char *s3 = "Linguagem", s4[ ], s5[20];
    s3 = s4;
    s2 = s5;
    s5 = "Linguagem C";
    s5 = s3;

    return 0;
}
