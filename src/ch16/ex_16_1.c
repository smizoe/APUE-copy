#include <arpa/inet.h>
#include <stdio.h>

int main(int argc, char const* argv[])
{
  uint16_t num;
  char str[2];
  str[0] = '\x01';
  num = ntohs((uint16_t) str);
  if(num == (uint16_t) str)
    printf("big endian\n");
  else
    printf("little endian\n");
  return 0;
}
