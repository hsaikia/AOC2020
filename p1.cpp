#include <cstdio>
#include <algorithm>
#include <vector>

int64_t solve(const std::vector<int64_t>& sorted, const int64_t x, std::size_t l, std::size_t r)
{
  while(l < r)
  {
    const auto& a = sorted[l];
    const auto& b = sorted[r];

    if (a + b < x)
    {
      l++;
    }
    else if (a + b > x)
    {
      r--;
    }
    else
    {
      return a * b;
    }
  }
  return 0;
}

void solve_2(const std::vector<int64_t>& sorted)
{
  constexpr int64_t x = 2020;

  auto ret = solve(sorted, x, 0, sorted.size() - 1);

  if (ret != 0)
  {
    printf("%ld\n", ret);
  }
}

void solve_3(const std::vector<int64_t>& sorted)
{
  constexpr int64_t x = 2020;

  for(std::size_t i = 0; i < sorted.size() - 2; i++)
  {
    auto ret = solve(sorted, x - sorted[i], i + 1, sorted.size() - 1);  
    if (ret != 0)
    {
      printf("%ld\n", sorted[i] * ret);
      break;
    }
  }
}

int main() {
  
  std::vector<int64_t> numbers;

  int64_t num;
  while(scanf("%ld", &num) != EOF)
  {
    numbers.emplace_back(num);
  }

  std::sort(std::begin(numbers), std::end(numbers));

  solve_3(numbers);
  
  return 0;
}