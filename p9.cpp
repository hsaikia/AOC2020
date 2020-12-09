
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

std::vector<std::size_t> numbers;

// part2
void find_range(const std::size_t invalid)
{
  std::vector<std::size_t> sums = numbers;
  for(std::size_t list_size = 2; list_size < numbers.size(); list_size++)
  {
    for(std::size_t i = 0; i <= numbers.size() - list_size; i++)
    {
      sums[i] = sums[i] + numbers[i + list_size - 1];
      if(sums[i] == invalid)
      {
        auto [mi, mx] = std::minmax_element(std::begin(numbers) + i, std::begin(numbers) + i + list_size);

        auto sum = *mi + *mx;
        std::cout << "Sum of min and max of range " << sum << "\n";
        return;
      }
    }
  }
}

// part1
std::size_t find_invalid(const std::size_t preamble_idx)
{
  for(std::size_t i = preamble_idx; i < numbers.size(); i++)
  {
    const auto& n = numbers[i];
    bool found = false;
    for(std::size_t j = i - preamble_idx; j < i; j++)
    {
      const auto& n1 = numbers[j];
      for(std::size_t k = j + 1; k < i; k++)
      {
        const auto& n2 = numbers[k];
        if(n1 + n2 == n)
        {
          found = true;
          break;
        }
      }

      if(found)
      {
        break;
      }
    }

    if(!found)
    {
      std::cout << numbers[i] << " is faulty!\n";
      return numbers[i];
    }
  }
  return 0;
}

int main() {

  std::size_t num;
  
  std::ifstream file;
  //file.open("sample_input.txt");
  //std::size_t preamble_idx = 5;
  file.open("input.txt");
  std::size_t preamble_idx = 25;

  while(file >> num)
  {
    numbers.emplace_back(num);
  }

  file.close();

  //part1
  auto invalid_number = find_invalid(preamble_idx);

  //part2
  find_range(invalid_number);

  return 0;
}