#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <time.h>

int main(){
  int READ = 0;
  int WRITE = 1;
  int f;

  int one[2];
  int two[2];
  pipe(one);
  pipe(two);
  f = fork();

  if(f){
    close(one[READ]);
    close(two[WRITE]);
    srand(time(NULL));
    int num = rand() % 10;
    printf("[parent] sending: %d\n",num);
    write(one[WRITE],&num,sizeof(num));
    
    int result;
    read(two[READ],&result,sizeof(result));
    printf("[parent] received: %d\n",result);
  }
  else{
    close(one[WRITE]);
    close(two[READ]);
    int got;
    read(one[READ],&got,sizeof(got));
    printf("[child] doing maths on: %d\n\n",got);

    int math = got * 2 + 19;  
    printf("[child] sending: %d\n",math);
    write(two[WRITE],&math,sizeof(math));
  }
}
