#include <iostream>
#include <vector>

class Course {
 public:
  Course() = default;
  Course(const std::vector<std::vector<int>>& depend) : depend_(depend) {}

  friend std::istream& operator>>(std::istream& in, Course& cource);

  friend class Solver;

 private:

  std::vector<std::vector<int>> depend_;
  std::vector<std::vector<bool>> variants_;
};

std::istream& operator>>(std::istream& in, Course& cource) {
  int dependencies;
  in >> dependencies;
  for (int j = 0; j < dependencies; ++j) {
    int choice;
    in >> choice;
    cource.depend_.push_back(std::vector<int>());
    for (int k = 0; k < choice; ++k) {
      int x;
      in >> x;
      cource.depend_[j].push_back(x);
    }
  }
  return in;
}