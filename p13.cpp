#define _USE_MATH_DEFINES
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

UI closest(UI query_time, UI bus_id)
{
    if (query_time % bus_id == 0)
    {
        return 0;
    }

    UI q = query_time / bus_id;
    return (q + 1) * bus_id - query_time;
}

struct Eq
{
    I a;
    I n;
};

int main()
{
    std::ifstream file;
    file.open("sample_input.txt");
    //file.open("input.txt");

    UI ts;
    file >> ts;

    std::string line{};
    std::string token;

    UI latest_bus_time = 10000000;
    UI bus_id = 0;

    std::vector<Eq> eqs;

    while (std::getline(file, line))
    {
        auto iss = std::istringstream{line};
        I pos = 0;
        while (std::getline(iss, token, ','))
        {
            if (token == "x")
            {
                pos++;
                continue;
            }

            I N = std::stoi(token);

            Eq new_eq;
            // The Chinese remainder theorem
            // requires a modular equation
            // to be of the form
            // X := A mod N
            // Since here X = Nm - pos, m \in I
            // => X := (N - (pos mod N)) mod N
            new_eq.a = (N - (pos % N)) % N;
            new_eq.n = N;
            eqs.emplace_back(new_eq);
            pos++;

            auto next_bus_time = closest(ts, N);

            if (latest_bus_time > next_bus_time)
            {
                latest_bus_time = next_bus_time;
                bus_id = N;
            }
        }
    }

    file.close();

    // sorting the modular equations for maixmum efficiency
    // https://en.wikipedia.org/wiki/Chinese_remainder_theorem 
    std::sort(eqs.begin(), eqs.end(), [](Eq &a, Eq &b) {
        return a.n > b.n;
    });

    // We start with the largest divisor
    I step = eqs[0].n; // main divisor
    I idx = eqs[0].a; // running index

    // And test on the next largest one
    UI i = 1;

    while (i < eqs.size())
    {
        // If the running index matches with
        // the current modular equation
        // incorporate the current divisor
        // into the main divisor
        if (idx % eqs[i].n == eqs[i].a)
        {
            step *= eqs[i].n;
            i++;
        } 
        else
        {
          // else increment the running index
          idx += step;
        }  
    }

    P("Part 1 ", latest_bus_time * bus_id);
    P("Part 2 ", idx);

    return 0;
}