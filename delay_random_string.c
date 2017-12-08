#include<stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

static char *rand_string(char *str, size_t size)
{
  const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJK...";
  for (size_t n = 0; n <= size; n++) {
    int key = rand() % (int) (sizeof charset - 1);
    str[n] = charset[key];
  }
  str[size] = '\0';
  return str;
}

int main(int argc, char**argv)
{
  useconds_t mult_factor=0, delay;
  if (argc<2){
    fprintf(stderr,"%s <delay factor (in milli-seconds)>:\n\techo different random strings infinitely after a pre-set random delay\n",argv[0]);
    exit(1);
  }
  mult_factor=atol(argv[1]);
  /* seed random number generator with the time */
  srand(((unsigned int)time(NULL))%RAND_MAX); 
  delay = (rand() / (1.0 + RAND_MAX)) * mult_factor * 1000;

  while(1) {
    int str_size = (rand() / (1.0 + RAND_MAX)) * mult_factor;
    /* allocate string */
    char *s = malloc(str_size + 1);
    if (s && str_size) {
      fprintf(stdout, "%s\n", rand_string(s, str_size));
    }
    free(s);
    usleep(delay);
  }
}
