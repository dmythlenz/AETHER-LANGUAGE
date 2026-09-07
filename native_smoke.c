#include <stdio.h>
long add(long,long); long square(long); long compare(long,long);
int main(void){
  if(add(20,22)!=42) return 1;
  if(square(9)!=81) return 2;
  if(compare(10,7)!=1) return 3;
  puts("native backend: PASS"); return 0;
}
