#include <optional>
#include <vector>

#include "cource.cpp"

class Solver {
 public:
  Solver(const std::vector<Course>& depend) : courses_(depend) {
    FindVariants();
  }

  std::optional<std::vector<int>> SolveStudent(const std::vector<int>& choice) {
    std::vector<bool> current(courses_.size());
    std::optional<std::vector<bool>> optimal;
    RComposeChoiceVariants(current, 0, choice, optimal);
    if (!optimal) {
      return std::nullopt;
    } else {
      std::vector<int> result;
      std::vector<bool> result_bool = optimal.value();
      for (int i = 0; i < result_bool.size(); ++i) {
        if (result_bool[i]) {
          result.push_back(i);
        }
      }
      return result;
    }
  }

 private:
  std::vector<Course> courses_;

  // Проверка, что вариант подходит под распределение по семестрам и
  // более оптимальный, чем current_optimal
  bool MoreOptimal(std::vector<bool>& current,
                   std::optional<std::vector<bool>>& current_optimal) const;

  void RComposeChoiceVariants(std::vector<bool>& current_variant,
                              int num_choice, const std::vector<int>& choices,
                              std::optional<std::vector<bool>>& optimal) const;

  void FindVariants();
  void RComposeVariants(int num_course, std::vector<bool>& variant,
                        int num_depend);
  std::vector<bool> Choose(int num_course);
};

void Unite(std::vector<bool>& first, const std::vector<bool>& second) {
  for (int i = 0; i < first.size(); ++i) {
    first[i] = first[i] | second[i];
  }
}

void Solver::RComposeChoiceVariants(
    std::vector<bool>& current_variant, int num_choice,
    const std::vector<int>& choices,
    std::optional<std::vector<bool>>& optimal) const {
  if (num_choice >= choices.size()) {
    if (MoreOptimal(current_variant, optimal)) {
      optimal = current_variant;
    }
  }
  std::vector<bool> copy;
  for (const auto& variant : courses_[choices[num_choice]].variants_) {
    copy = current_variant;
    Unite(copy, variant);
    RComposeChoiceVariants(copy, num_choice + 1, choices, optimal);
  }
}

void Solver::FindVariants() {
  for (int i = 0; i < courses_.size(); ++i) {
    std::vector<bool> variant(courses_.size());
    RComposeVariants(i, variant, 0);
  }
}

void Solver::RComposeVariants(int num_course, std::vector<bool>& variant,
                              int num_depend) {
  if (num_depend >= courses_[num_course].depend_.size()) {
    courses_[num_course].variants_.push_back(variant);
    return;
  }
  std::vector<bool> copy;
  for (int choice : courses_[num_course].depend_[num_depend]) {
    for (auto& child_variant : courses_[choice].variants_) {
      copy = variant;
      Unite(copy, child_variant);
      RComposeVariants(num_course, copy, num_depend + 1);
    }
  }
}