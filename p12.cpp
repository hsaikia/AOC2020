
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
#define FOR(i, b) for (UI(i) = 0; i < (b); i++)
#define P(s, c) std::cout << s << c << "\n"

constexpr double PI = 3.14159;
constexpr double eps = 1e-6;
std::vector<std::string> instructions;

void rotate_around_origin(double &x, double &y, double angle_rad)
{
  auto tmp_dx = x * cos(angle_rad) - y * sin(angle_rad);
  auto tmp_dy = x * sin(angle_rad) + y * cos(angle_rad);
  x = std::abs(tmp_dx) < eps ? 0 : tmp_dx;
  y = std::abs(tmp_dy) < eps ? 0 : tmp_dy;
}

int main()
{
  std::ifstream file;
  //file.open("sample_input.txt");
  file.open("input.txt");

  std::string line;
  while (std::getline(file, line))
  {
    instructions.emplace_back(line);
  }

  // part 1
  // double rx = 1, ry = 0;
  // part 2
  double rx = 10, ry = 1;
  double x = 0, y = 0;

  FOR(i, instructions.size())
  {
    char d = instructions[i][0];
    I val = std::stoi(instructions[i].substr(1));

    if (d == 'N')
    {
      // part 1
      // y += val;
      // part 2
      ry += val;
      continue;
    }
    if (d == 'S')
    {
      // part 1
      // y -= val;
      // part 2
      ry -= val;
      continue;
    }
    if (d == 'E')
    {
      // part 1
      // x += val;
      // part 2
      rx += val;
      continue;
    }
    if (d == 'W')
    {
      // part 1
      // x -= val;
      // part 2
      rx -= val;
      continue;
    }
    if (d == 'F')
    {
      x += val * rx;
      y += val * ry;
      continue;
    }
    if (d == 'L')
    {
      const double vald = (PI / 180) * val;
      rotate_around_origin(rx, ry, vald);
      continue;
    }
    if (d == 'R')
    {
      const double vald = -(PI / 180) * val;
      rotate_around_origin(rx, ry, vald);
      continue;
    }
  }

  P("Ans ", std::abs(x) + std::abs(y));

  file.close();
  return 0;
}