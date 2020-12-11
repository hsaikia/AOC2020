
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
#define FOR(i, b) for(UI (i) = 0; i < (b); i++)
#define P(s, c) std::cout << s << c << "\n"

std::vector<std::string> m;

bool flip2(I x, I y)
{
  I a[3] = {-1, 0, 1};
  I count = 0;
  FOR(i, 3)
  {
    FOR(j, 3)
    {
      if(a[i] == 0 && a[j] == 0)
      {
        continue;
      }

      auto nx = x;
      auto ny = y;

      // keep scanning in this direction
      while(true)
      {
        nx += a[i];
        ny += a[j];

        if(nx >= 0 && ny >= 0 && nx < m.size() && ny < m[0].size())
        {
          if(m[nx][ny] != '.')
          {
            count += m[nx][ny] == '#';
            break;
          }
          continue;
        }
        break;
      }      
    }
  }

  if(count == 0 && m[x][y] == 'L')
  {
    return true;
  }

  if(count >= 5 && m[x][y] == '#')
  {
    return true;
  }

  return false;
}

bool flip1(I x, I y)
{
  I a[3] = {-1, 0, 1};
  I count = 0;
  FOR(i, 3)
  {
    FOR(j, 3)
    {

      if(a[i] == 0 && a[j] == 0)
      {
        continue;
      }

      auto nx = x + a[i];
      auto ny = y + a[j];

      if(nx >= 0 && ny >= 0 && nx < m.size() && ny < m[0].size())
      {
        count += m[nx][ny] == '#';
      }
    }
  }

  if(count == 0 && m[x][y] == 'L')
  {
    return true;
  }

  if(count >= 4 && m[x][y] == '#')
  {
    return true;
  }

  return false;

}

bool sim()
{
  std::vector<std::string> m_next = m;
  FOR(i, m.size())
  {
    FOR(j, m[i].size())
    {
      if(m[i][j] == '.')
      {
        continue;
      }

      // use flip1 for part 1
      if (flip2(i, j))
      {
        m_next[i][j] = m[i][j] == '#' ? 'L' : '#';
      }
    }
  }

  bool stab = true;
  FOR(i, m.size())
  {
    if(m[i] != m_next[i])
    {
      stab = false;
    }
  }

  m = m_next;
  return stab;
}

int main() {
  
  std::ifstream file;
  //ile.open("sample_input.txt");
  file.open("input.txt");
  
  std::string line;
  while(std::getline(file, line))
  {
    m.emplace_back(line);
  }

  file.close();

  while(true)
  {
    auto stab = sim();
    if(stab)
    {
      break;
    }
  }

  I ans = 0;
  FOR(i, m.size())
  {
    FOR(j, m[i].size())
    {
      ans += m[i][j] == '#';
    }
  }

  P("Num occupied seats : ", ans);

  return 0;
}