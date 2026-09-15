#include "clicker.hpp"

malashenko::Clicker::Clicker():
  start_(std::chrono::high_resolution_clock::now())
{}

double malashenko::Clicker::millisec() const
{
  using std::chrono::high_resolution_clock;
  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  auto t = high_resolution_clock::now();
  return duration_cast< milliseconds >(t - start_).count();
}