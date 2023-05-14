// Collatz.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <chrono>
#include <map>
#include <string>

using namespace std::chrono_literals;

class Collatz
{
public:

    /// <summary>
    /// Calculates the number of iterations of the collatz map that are required to iterate back to 1.
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    std::uint64_t operator()(std::uint64_t n) const
    {
        return calculate_collatz(n);
    }

private:
    mutable std::map<std::uint64_t, std::uint64_t> m_cache;

#define CACHE

    std::uint64_t calculate_collatz(std::uint64_t n) const
    {
        if (n == 1)
        {
            return 0;
        }

#ifdef CACHE
        auto const it = m_cache.find(n);
        if (it != std::end(m_cache))
        {
            return it->second;
        }

        auto const count = 1 + calculate_collatz(collatz_iterate(n));
        m_cache[n] = count;
        return count;

#else // ^^^^^^^ CACHE ^^^^^^^ / vvvvvvv !CACHE vvvvvvv
        auto const count = 1 + calculate_collatz(collatz_iterate(n));
        return count;
#endif // CACHE
    }

    constexpr std::uint64_t collatz_iterate(std::uint64_t n) const
    {
        return (n % 2 == 0) ? (n / 2) : (3 * n + 1);
    }
};

using Clock = std::chrono::steady_clock;

int main(int argc, char* argv[])
{
    /* const auto start_time = Clock::now();
    auto collatz = Collatz{};
    for (auto n = 1; n < 1000; ++n)
    {
        std::cout << "Collatz(" << n << ") = " << collatz(n) << std::endl;
    }
    auto end_time = Clock::now();
    auto duration = end_time - start_time;
    auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    std::cout << "\n"
        "Elapsed Time (us) = " << micros << std::endl; */

    if (argc < 2)
    {
        std::cout << "Usage: Collatz <n>" << std::endl;
        return 1;
    }

    auto n = std::stoull(argv[1]);
    std::cout << Collatz{}(n) << std::endl;
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
