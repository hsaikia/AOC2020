
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector< std::size_t >> contains(1000, std::vector<std::size_t>(1000, 0));
std::map<std::string, std::size_t> color_idx_map;

void add_color_to_map(const std::string& color)
{
    if(color_idx_map.find(color) == color_idx_map.end())
    {
      auto idx = color_idx_map.size();
      color_idx_map[color] = idx;
    }
}

// part 1
std::size_t count_ancestors(const std::size_t search_idx)
{
  std::set<std::size_t> idxs;
  std::queue<std::size_t> q;

  q.push(search_idx);
  while(!q.empty())
  {
    auto idx = q.front();
    idxs.insert(idx);
    q.pop();

    for(std::size_t i = 0; i < color_idx_map.size(); i++)
    {
      if(contains[i][idx] > 0)
      {
        q.push(i);
      }
    }
  }

  return idxs.size() - 1;
}

// part2
std::map<std::size_t, std::size_t> children_count_map;
std::size_t count_num_children(const std::size_t search_idx)
{

  if(children_count_map.find(search_idx) != children_count_map.end())
  {
    return children_count_map[search_idx];
  }

  // counting self (since nested boxes need to be counted)
  // final answer would be +1
  std::size_t ret = 1;
  for(std::size_t i = 0; i < color_idx_map.size(); i++)
  {
    const auto num_bags = contains[search_idx][i];
    if(num_bags > 0)
    {
      ret += num_bags * count_num_children(i);
    }
  }
  children_count_map[search_idx] = ret;
  return ret;
}

int main() {
  std::string line;
  while(std::getline(std::cin, line))
  {
      auto iss = std::istringstream{line};
      std::vector<std::string> answers;
      std::string ans{};
      
      while (iss >> ans) {
        //std::cout << ans << std::endl;
        answers.emplace_back(ans);
      }  

      auto big_bag = answers[0] + "_" + answers[1];
      add_color_to_map(big_bag);
      auto big_bag_idx = color_idx_map[big_bag];

      for(std::size_t idx = 5; idx < answers.size() - 2; idx += 4 )
      {
        auto small_bag = answers[idx] + "_" + answers[idx + 1];
        add_color_to_map(small_bag);
        auto small_bag_idx = color_idx_map[small_bag];
        // 1 big bag contains 'answers[idx - 1]' many small bags
        contains[big_bag_idx][small_bag_idx] = std::stoi(answers[idx - 1]);
      }
      
  }

  auto search_idx = color_idx_map["shiny_gold"];
  std::cout << " Part 1 : " << count_ancestors(search_idx) << "\n";
  std::cout << " Part 2 : " << count_num_children(search_idx) - 1 << "\n";

  return 0;
}