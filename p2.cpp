#include <cstdint>
#include <cstdio>
#include <cstring>

void first_scheme()
{
  int64_t l, h;
  char c;
  char pass[2048];
  std::size_t valid = 0;
  while(scanf("%ld-%ld %c: %s", &l, &h, &c, pass) != EOF)
  {
    int64_t num_occured = 0;
    for(std::size_t i = 0; i < strlen(pass); i++)
    {
      if (c == pass[i])
      {
        num_occured++;
      }
    }

    if (num_occured >= l && num_occured <= h)
    {
      valid++;
    }
  }

  printf("%ld Passwords Valid\n", valid);
}

void second_scheme()
{
  int64_t l, h;
  char c;
  char pass[2048];
  std::size_t valid = 0;
  while(scanf("%ld-%ld %c: %s", &l, &h, &c, pass) != EOF)
  {
    if (pass[l - 1] == c ^ pass[h - 1] == c)
    {
      valid++;
      //printf("%s is valid\n", pass);
    }
  }

  printf("%ld Passwords Valid\n", valid);
}

int main() {
  
  //first_scheme();
  second_scheme();

  return 0;
}