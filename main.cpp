#include <iostream>
#include <vector>

#include "solution.cpp"

int main()
{
  int cources;
  std::cin >> cources;
  std::vector<Course> depend(cources);
  for (int i = 0; i < cources; ++i) {
    Course cource;
    std::cin >> cource;
    depend.push_back(cource);
  }
  std::vector<int> choice(4);
  for (int i = 0; i < 4; ++i) {
    std::cin >> choice[i];
  }
  Solver solver(depend);
  return 0;
}