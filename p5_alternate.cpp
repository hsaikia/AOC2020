#include <cmath>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>

int main() {
  char pass[10];
  std::size_t max_id = 0;
  // max_seats = 128 * 8
  std::vector<bool> is_seat_free(1024, true);

  while(std::cin >> pass)
  {
    std::string binary_row{}, binary_col{};
    
    for(std::size_t i = 0; i < 7; i++)
    {
      binary_row += ((pass[i] == 'B') ? '1' : '0');
    }

    for(std::size_t i = 7; i < 10; i++)
    {
      binary_col += ((pass[i] == 'R') ? '1' : '0');
    }

    std::size_t sz1, sz2;
    std::size_t pass_id = 8 * std::stoi(binary_row, &sz1, 2) + std::stoi(binary_col, &sz2, 2);

    //std::cout << pass << " has id :" << pass_id <<  std::endl;
    
    is_seat_free[pass_id] = false;
    max_id = std::max(max_id, pass_id);
  }

  std::cout << "Max Id :" << max_id <<  std::endl;

  for(std::size_t i = 1; i < is_seat_free.size() - 1; i++)
  {
    if(!is_seat_free[i - 1] && is_seat_free[i] && !is_seat_free[i + 1])
    {
      std::cout << "My seat ID is " << i << std::endl;
      break;
    }
  }
  
  return 0;
}