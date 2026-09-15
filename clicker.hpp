#ifndef CLICKER_HPP
#define CLICKER_HPP
#include <chrono>

namespace malashenko
{
  class Clicker {
  public:
    Clicker();
    double millisec() const;
  private:
    std::chrono::time_point< std::chrono::steady_clock > start_;
  };
}

#endif