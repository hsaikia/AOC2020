#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>

int main() {
  std::string line;

  char pass[11];
  std::size_t max_id = 0;
  // max_seats = 128 * 8
  std::vector<bool> seats(1024, true);

  while(scanf("%s", pass) != EOF)
  {
    int t = 0;
    int b = 127;
    int l = 0;
    int r = 7;

    for(std::size_t i = 0; i < strlen(pass); i++)
    {
      if (pass[i] == 'F')
      {
        b = std::floor((t + b) / 2.0);
        continue;
      }

      if (pass[i] == 'B')
      {
        t = std::ceil((t + b) / 2.0);
        continue;
      }

      if (pass[i] == 'L')
      {
        r = std::floor((l + r) / 2.0);
        continue;
      }

      if (pass[i] == 'R')
      {
        l = std::ceil((l + r) / 2.0);
        continue;
      }
    }

    auto pass_id = t * 8 + l;

    //std::cout << pass << " has id :" << pass_id <<  std::endl;
    
    seats[pass_id] = false;

    if (max_id < pass_id)
    {
      max_id = pass_id;
    }
  }

  std::cout << "Max Id :" << max_id <<  std::endl;

  for(std::size_t i = 1; i < seats.size() - 1; i++)
  {
    if(!seats[i - 1] && seats[i] && !seats[i + 1])
    {
      std::cout << "My seat ID is " << i << std::endl;
    }
  }
  
  return 0;
}