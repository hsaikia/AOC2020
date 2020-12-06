#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <numeric>

std::vector<int> m(26, 0);
int num = 0;

void reset()
{
  num = 0;
  m.clear();
  m.resize(26, 0);
}

int count1()
{
  return std::accumulate(std::begin(m), std::end(m), 0, [](int s, int e) { 
    s += e > 0 ? 1 : 0; return s;
    });
}

int count2(int num)
{
  return std::accumulate(std::begin(m), std::end(m), 0, [&num](int s, int e) { 
    s += e == num ? 1 : 0; return s;
    });
}

int main() {
std::string line;
int ret = 0;

  while(std::getline(std::cin, line))
  {
    if (line == "")
    {
      //ret += count1();
      ret += count2(num);
      reset();
    }
    else 
    {
      auto iss = std::istringstream{line};
      auto answers = std::string{};
      
      while (iss >> answers) {
        num++;
        for(std::size_t i = 0; i < answers.size(); i++)
        {
          m[answers[i] - 'a']++;
        }
      }  
    }
  }

  //ret += count1();
  ret += count2(num);
  std::cout << ret << std::endl;
  
  return 0;
}