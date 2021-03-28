#include <stdio.h>
#include <stdlib.h>

#include "type.h"

int erfunc(char *s, int val)
{
  fprintf(stderr, "%s %d\n", s, val);
  exit(1);
}

void struct_cp(char *to, char *from, int size)
{
  int s;
  s = size;
  while(s--)
    *to++ = *from++;
}

