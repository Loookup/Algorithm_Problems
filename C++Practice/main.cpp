#include "Person.h"

auto make_person(){
    std::string name; size_t age; size_t salary;
    std::cin >> name; std::cin >> age; std::cin >> salary;
    return std::pair(Person{name, age}, salary);
}

int main() {
    std::map<Person, size_t>  payroll;
    int N;
    std::cin >> N;
    for (int i=0; i < N; i++)
        payroll.insert(make_person());

    std::cout << "Sort By ID" << std::endl;
    for (const auto& [person, salary] : payroll)
        std::cout << person << " " << salary << std::endl;

    std::vector<std::pair<Person, size_t>> v_payroll(std::begin(payroll), std::end(payroll));

    std::cout << "Sort By Age" << std::endl;
    std::sort(std::begin(v_payroll), std::end(v_payroll),
              [](const auto& lhs, const auto& rhs) {
                  auto Comparator = Person::ComparatorByAge();
                  return Comparator(lhs.first, rhs.first);
              });
    for(const auto& [person, salary] : v_payroll)
        std::cout << person<< " " << salary << std::endl;

    std::cout << "Sort By Name" << std::endl;
    std::sort(std::begin(v_payroll), std::end(v_payroll),
              [](const auto& lhs, const auto& rhs) {
                  auto Comparator = Person::ComparatorByName();
                  return Comparator(lhs.first, rhs.first);
              });
    for(const auto& [person, salary] : v_payroll)
        std::cout << person<< " " << salary << std::endl;

    std::cout << "Sort By Salary" << std::endl;
    std::sort(std::begin(v_payroll), std::end(v_payroll),
              [](const auto& lhs, const auto& rhs){
                  return lhs.second < rhs.second;
              });
    for(const auto& [person, salary] : v_payroll)
        std::cout << person<< " " << salary << std::endl;

    return 0;
}