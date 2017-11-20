#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
  int p1[2], p2[2];
  
  pipe(p1);
  pipe(p2);

  int f = fork();

  //parent
  if(f){
    close(p1[0]); //close read 
    close(p2[1]); //close write

    int num = 12;

    write(p1[1], &num, sizeof(num));
    printf("[parent] sending: %d\n", num);

    read(p2[0], &num, sizeof(num));
    printf("[parent] received: %d\n", num);

    close(p1[1]);
    close(p2[0]);

    printf("parent has finished\n");
  }
  //child
  else{
    close(p1[1]);
    close(p2[0]);

    int num;
    
    read(p1[0], &num, sizeof(num));
    printf("child received: %d\n", num);

    printf("[child] doing some math\n");
    num *= num;

    printf("[child] sending: %d\n", num);
    write(p2[1], &num, sizeof(num));
    
    close(p1[0]); //close read 
    close(p2[1]); //close write

    printf("child has finished\n");
  }
}
