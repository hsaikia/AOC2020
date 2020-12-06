#include <cstdint>
#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <set>
#include <map>

std::map<std::string, std::string> keys;
std::size_t num_valid = 0;
std::size_t idx = 1;

void reset()
{
  keys["byr"] = "";
  keys["iyr"] = "";
  keys["eyr"] = "";
  keys["hgt"] = "";
  keys["hcl"] = "";
  keys["ecl"] = "";
  keys["pid"] = "";
  idx++;
}

bool check_validity()
{
  bool valid = true;
  for(const auto& [k, v] : keys)
  {
    if(v == "")
    {
      return false;
    }
  }

  return true;
}

bool check_year(std::string year_str, int mi, int mx)
{
  std::string::size_type sz;
  int year = stoi(year_str, &sz);
  if(year >= mi && year <= mx)
  {
    return true;
  }
  return false;
}

bool check_height(std::string str)
{
  std::string::size_type sz;
  int num = stoi(str, &sz);
  std::string type = str.substr(sz);

  if(type == "cm")
  {
    if(num >= 150 && num <= 193)
    {
      return true;
    }
  }

  if(type == "in")
  {
    if(num >= 59 && num <= 76)
    {
      return true;
    }
  }
  
  return false;
}

bool check_hcolor(std::string str)
{
  if(str.size() != 7)
  {
    return false;
  }

  if (str[0] != '#')
  {
    return false;
  }

  for(std::size_t i = 1; i < 7; i++)
  {
    if(!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')))
    {
      return false;
    }
  }
  return true;
}

bool check_ecolor(std::string str)
{
  if (str == "amb" || str == "blu" || str == "brn" || str == "gry" ||
  str == "grn" || str == "hzl" || str == "oth" )
  {
    return true;
  }
  return false;
}

bool check_pid(std::string str)
{
  if(str.size() != 9)
  {
    return false;
  }

  for(std::size_t i = 0; i < 9; i++)
  {
    if(!(str[i] >= '0' && str[i] <= '9'))
    {
      return false;
    }
  }
  return true;
}

void check_validity1()
{
  if (!check_validity())
  {
    return;
  }
    
  num_valid++; 
}

void check_validity2()
{

  if (!check_validity())
  {
    return;
  }

  bool valid = true;
  for(const auto& [k, v] : keys)
  {
    if (k == "byr")
    {
      if (!check_year(v, 1920, 2002))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
    else if(k == "iyr")
    {
      if (!check_year(v, 2010, 2020))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
    else if(k == "eyr")
    {
      if (!check_year(v, 2020, 2030))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
    else if(k == "hgt")
    {
      if (!check_height(v))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
    else if (k == "hcl")
    {
      if (!check_hcolor(v))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
    else if (k == "ecl")
    {
      if (!check_ecolor(v))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
    else if (k == "pid")
    {
      if (!check_pid(v))
      {
        valid = false;
        std::cout << "Passport #" << idx << " has invalid " << k << "\n";
        break;
      }
    }
  }

  if (valid)
  {
    std::cout << "Passport #" << idx << "has all valid fields!\n";
    num_valid++;
  }
}

int main() {
  std::string line;

  while(std::getline(std::cin, line))
  {
    if (line == "")
    {
      //check_validity1();
      check_validity2();
      reset();
    }
    else 
    {
      //std::cout << "Now Checking Passport #" << idx << "\n";
      auto iss = std::istringstream{line};
      auto keyvalue = std::string{};
      auto key = std::string{};
      auto value = std::string{};

      while (iss >> keyvalue) {

        auto d = keyvalue.find(":");
        key = keyvalue.substr(0, d);
        value = keyvalue.substr(d + 1);
        //std::cout << "Key " << key << "->" << value << "\n";
        keys[key] = value;
      }  
    }
  }

  // last one
  //check_validity1();
  check_validity2();

  std::cout << num_valid << " passports are valid\n";  
  return 0;
}