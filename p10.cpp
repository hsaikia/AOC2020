
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cmath>

#define I int64_t
#define UI std::size_t
#define FOR(i, b) for(UI i = 0; i < (b); i++)

std::vector<I> adapters;

std::map<UI, I> count_map;
I count(UI idx)
{
  if (count_map.find(idx) != count_map.end())
  {
    return count_map[idx];
  }

  if (idx == 0)
  {
    return count(1);
  }

  if(idx == adapters.size() - 1)
  {
    count_map[idx] = 1;
    return 1;
  }

  I ret = 0;
  FOR(idx, adapters.size())
  {
    if (std::abs(adapters[idx - 1] - adapters[i]) <= 3)
    {
      auto c = count(i + 1);
      ret += c;
    }
  }

  count_map[idx] = ret;
  return ret;
}

int main() {

  I num;
  
  std::ifstream file;
  //file.open("sample_input_small.txt");
  //file.open("sample_input.txt");
  file.open("input.txt");
  
  while(file >> num)
  {
    adapters.emplace_back(num);
  }

  adapters.emplace_back(0);
  std::sort(adapters.begin(), adapters.end());

  adapters.emplace_back(adapters.back() + 3);

  int diff_count[3] = {0, 0, 0};

  FOR(0, adapters.size() - 1)
  {
    auto diff = std::abs(adapters[i] - adapters[i + 1]);
    diff_count[diff - 1]++;
  }

  std::cout << "Product (part1) " << diff_count[0] * diff_count[2] << "\n";
  std::cout << "Total Count (part2) " << count(0) << "\n";

  file.close();

  
  return 0;
}