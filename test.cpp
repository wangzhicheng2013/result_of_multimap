#include "range.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <tuple>
struct person {
    std::string name;
    int age;
    std::string city;
};

template <typename Tuple, std::size_t N>
struct printer {
    static void print(const Tuple &t) {
        printer<Tuple, N - 1>::print(t);
        std::cout << ", " << std::get<N - 1>(t);
    }
};

template <typename Tuple>
struct printer<Tuple, 1> {
    static void print(const Tuple &t) {
        std::cout << std::get<0>(t);
    }
};
template <typename... Args>
void PrintTuple(const std::tuple<Args...> &t) {
    std::cout << "(";
    printer<decltype(t), sizeof...(Args)>::print(t);
    std::cout << ")\n";
}

int main() {
    typedef std::vector<person> R;
    R vec{{"aa", 18, "bb"}, {"cc", 28, "dd"}, {"ahj", 12, "12dd"}};
    range<R>r(vec);
    auto mm = r.group_by([](const person& _person) { return std::tie(_person.name, _person.age); },
                         [](const person& _person){ return std::tie(_person.city); });
    
    for (auto &e: mm) {
        std::cout << "first==============" << std::endl;
        PrintTuple(e.first);
        std::cout << "second==============" << std::endl;
        PrintTuple(e.second);
    }

    auto mm1 = r.group_by([](const person& _person) { return std::tie(_person.age); },
                         [](const person& _person){ return std::tie(_person.name, _person.city); });
    
    std::cout << "===========================" << std::endl;
    for (auto &e: mm1) {
        std::cout << "first==============" << std::endl;
        PrintTuple(e.first);
        std::cout << "second==============" << std::endl;
        PrintTuple(e.second);
    }

    return 0;
}