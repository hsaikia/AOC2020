
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>

struct Instruction{
  std::string code;
  int value;
  std::size_t runs{0};
  // dirty flag
  bool dirty{false};

  Instruction(const std::string& code_, const int& value_)
  {
    code = code_;
    value = value_;
  }
};

std::vector<Instruction> program;

void reset_runs()
{
  for(auto& ins : program)
  {
    ins.runs = 0;
  }
}

int runAcc(int loc, int& acc_res)
{
  acc_res += program[loc].value;
  program[loc].runs++;
  return loc + 1;
}

int runJmp(int loc)
{
  program[loc].runs++;
  return loc + program[loc].value;
}

int runNop(int loc)
{
  program[loc].runs++;
  return loc + 1;
}

bool run()
{
  int ret = 0;
  int loc = 0;
  bool success = true;

  // allow looping only twice
  while(program[loc].runs < 2)
  {
    if(program[loc].runs >= 1 || loc < 0)
    {
      // looping or invalid access
      success = false;
      break;
    }

    if (loc > program.size() - 1)
    {
      //success
      break;
    }

    if(program[loc].code == "acc")
    {
      loc = runAcc(loc, ret);
      continue;
    }

    if(program[loc].code == "nop")
    {
      loc = program[loc].dirty ? runJmp(loc) : runNop(loc);
      continue;
    }

    if(program[loc].code == "jmp")
    {
      loc = program[loc].dirty ? runNop(loc) : runJmp(loc);
    }
  }

  if (success)
  {
    std::cout << "Terminated successfully!\n";
  }

  std::cout << "Res " << ret << "\n";

  return success;
}

void part1()
{
  run();
}

void part2()
{
  for(std::size_t loc = 0; loc < program.size(); loc++)
  {
    if (program[loc].code == "nop" || program[loc].code == "jmp")
    {
      program[loc].dirty = true;

      auto res = run();

      if(res)
      {
        break;
      }
      else 
      {
        program[loc].dirty = false;
        reset_runs();
      }
    }
  }
}

int main() {
  std::string line;
  while(std::getline(std::cin, line))
  {
    auto iss = std::istringstream{line};
    std::vector<std::string> tokens;
    std::string token{};
    
    while (iss >> token) {
      tokens.emplace_back(token);
    }  

    program.emplace_back(Instruction(tokens[0], std::stoi(tokens[1])));
  }

  //part1();
  part2();
  
  return 0;
}