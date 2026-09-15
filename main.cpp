#include <iostream>
#include <future>
#include <functional>
#include <numeric>
#include <vector>
#include "clicker.hpp"
namespace malashenko
{
  using data_t = std::vector< unsigned long long >;
  using value_t = data_t::value_type;

  value_t partitial_sum(const data_t& nums, size_t start, size_t end)
  {
    return std::accumulate(nums.begin() + start, nums.begin() + end, 0);
  }

}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    std::cerr << "Usage: ./a.out <amount of streams>\n";
    return 1;
  }

  size_t amountOfStreams{0};
  try
  {
    amountOfStreams = std::stoull(argv[1]);
  }
  catch(...)
  {
    std::cerr << "Amount of streams must be a positive number\n";
    return 1;
  }

  if (amountOfStreams == 0)
  {
    std::cerr << "Amount of streams must be greater than zero\n";
    return 1;
  }

  constexpr size_t size{1'000'000'000};
  double init{0}, total{0};
  using namespace malashenko;
  value_t sum{0};

  {
  data_t values(size, 1);
  Clicker cl;

  size_t part_size = size / amountOfStreams;
  size_t current_pos = 0;
  std::vector< std::future< value_t > > tasks;

  init = cl.millisec();

  std::cout << "Start of calculation\n";
  for (size_t i = 0; i < amountOfStreams - 1; ++i)
  {
    auto task = std::async(std::launch::async, partitial_sum, std::cref(values), current_pos, current_pos + part_size);
    current_pos += part_size;

    tasks.emplace_back(std::move(task));
  }
  auto finalTask = std::async(std::launch::async, partitial_sum, std::cref(values), current_pos, size);
  tasks.emplace_back(std::move(finalTask));

  value_t res{0};
  for (size_t i = 0; i < amountOfStreams; ++i)
  {
    res += tasks[i].get();
  }

  total = cl.millisec();
  std::cout << "End of calculation. Time: " << total << '\n';
  }
}
