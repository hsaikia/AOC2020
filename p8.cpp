
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

struct Instruction{
  std::string code;
  int value;
  bool has_run{false};
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
    ins.has_run = false;
  }
}

int runAcc(int loc, int& acc_res)
{
  acc_res += program[loc].value;
  program[loc].has_run = true;
  return loc + 1;
}

int runJmp(int loc)
{
  program[loc].has_run = true;
  return loc + program[loc].value;
}

int runNop(int loc)
{
  program[loc].has_run = true;
  return loc + 1;
}

bool run()
{
  int ret = 0;
  int loc = 0;
  bool success = false;

  // do not allow looping
  while(!program[loc].has_run)
  {
    if(program[loc].code == "acc")
    {
      loc = runAcc(loc, ret);
    
    }
    else if(program[loc].code == "nop")
    {
      loc = program[loc].dirty ? runJmp(loc) : runNop(loc);
    }
    else if(program[loc].code == "jmp")
    {
      loc = program[loc].dirty ? runNop(loc) : runJmp(loc);
    }

    if(loc < 0)
    {
      // invalid access
      break;
    }
    if (loc > program.size() - 1)
    {
      //success
      success = true;
      break;
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

  std::ifstream file;
  //file.open("sample_input.txt");
  file.open("input.txt");

  std::string line;
  while(std::getline(file, line))
  {
    auto iss = std::istringstream{line};
    std::vector<std::string> tokens;
    std::string token{};
    
    while (iss >> token) {
      tokens.emplace_back(token);
    }  

    program.emplace_back(Instruction(tokens[0], std::stoi(tokens[1])));
  }

  file.close();

  //part1();
  part2();
  
  return 0;
}