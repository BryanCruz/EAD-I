#include<stdio.h>
//Quais são os valores de x, y, z, p e pp ao nal da função abaixo?
void f(){
  int x, y, z, *p, **pp;

  y = 0;
  p = &y;       //*p = Y
  pp= &p;       //*pp = p
  x = *p;       //x = y = 0

  x += 4;       //x = 0 + 4 = 4

  (*p)++;       //y = 0++ = 1

  --x;          //x = --4 = 3

  (*p) += x;    //y = 1+3 = 4

  p--;          //p = &x
  (*p) += x;    //x = 3+3 = 6

  p++;          //p = &y

  (**pp) += 3*x;//y += 4+3*6 = 22

                //z=0

  printf("x=%d y=%d z=%d p=%p &x=%p &y=%p &z=%p *p=%d\n", x, y, z, p, &x, &y, &z, *p);
}

int main(void){
  f();
  return 0;
}
