#include <cstdint>
#include <cstdio>
#include <cstring>
#include <vector>

std::size_t solve(std::size_t right, std::size_t down, std::vector<std::vector<bool>>& map)
{
  std::size_t count = 0;
  std::size_t j = right;
  for(std::size_t i = down; i < map.size(); i += down)
  {
    if (map[i][j])
    {
      count++;
    }
    j = (j + right) % map[i].size();
  }

  return count;
}

int main() {
  
  char pattern[2048];
  std::vector<std::vector<bool>> map;
  while(scanf("%s", pattern) != EOF)
  {
    std::vector<bool> lane;
    for(std::size_t i = 0; i < strlen(pattern); i++)
    {
      if (pattern[i] == '.')
      {
        lane.emplace_back(false);
      }
      else
      {
        lane.emplace_back(true);
      }
    }
    map.emplace_back(lane);
  }

  std::size_t ret = 1;
  ret *= solve(1, 1, map);
  ret *= solve(3, 1, map);
  ret *= solve(5, 1, map);
  ret *= solve(7, 1, map);
  ret *= solve(1, 2, map);


  printf("%ld", ret);

  return 0;
}