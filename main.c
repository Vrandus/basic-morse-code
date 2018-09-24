#include <stdio.h>
#include <stdlib.h>
#include "morsecode.h"

int main(int argc, char *argv[])
{
  char *p;
  if(argc != 2) {
    fprintf(stderr,"usage: %s text\n", argv[0]);
    exit(1);
  }
  init_morse();
  play_buzzer(500);
  wait_word();
  p = argv[1];
  while(*p) {
    if(*p == ' ')
      wait_word();
    else {
      char *v = char2morse(*p);
      printf("character %c translates to %s\n", *p, v);
      while(*v) {
        switch(*v) {
        case '*' : send_dot(); break;
        case '=' : send_dash(); break;
        default:
          /*NOTREACHED*/
          fprintf(stderr,"internal logic error\n");
          exit(1);
        }
        if(*(v+1) != '\0')
          wait_dot();
        else if(*(p+1) == ' ')
          wait_word();
        else if(*(p+1) != '\0')
          wait_letter();
        v++;
      }
    }
    p++;
  }
  return 0;
}
