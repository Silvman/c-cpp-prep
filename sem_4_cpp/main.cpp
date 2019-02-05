#include <iostream>
#include "set.hpp"
#include "mystring.hpp"

int main () {
    std::cout << "The set of integer" << std::endl;
    set<int> a;
    try {
      a.insert(10);
      a.insert(5);
      std::cout << "Now the size is: " << a.size() << std::endl;
      std::cout << "Let's add int 1" << std::endl;
      a.insert(1);
      std::cout << "Now the size is: " << a.size() << std::endl;
      std::cout << "Let's add is again!" << std::endl;
      a.insert(1);
      std::cout << "Now the size is: " << a.size() << std::endl;
      std::cout << std::endl;

      a.insert(7);
      a.insert(19);
      a.insert(14);
      std::cout << "Let's add int 21" << std::endl;
      a.insert(21);
      std::cout << "Now the size is: " << a.size() << std::endl;
    } catch(std::bad_alloc& ba) {
      std::cout << "An error with allocation: "<<  ba.what() << std::endl;
    }

    std::cout << "Earsing 21" << std::endl;
    a.erase(21);
    std::cout << "Now the size is: " << a.size() << std::endl;
    a.erase(21);
    std::cout << "Earsing again" << std::endl;
    std::cout << "Now the size is: " << a.size() << std::endl;

    try {
      a.find(0);
    } catch (const std::invalid_argument &a) {
      std::cout << a.what() << std::endl;
    }
    std::cout << "All the set:" << std::endl;
    a.print();

    a.clear();

    std::cout << "\n~~~~~~~~~~~~~~\nAn exapmle of using set" << std::endl;

    set<double> b;

    std::cout << "Sorting of doubles" << std::endl;

    double arr[10] = { 4.3, 99.0, 1.2, 4.5, 0.111, 10.5, 45.01, 0.06, 0.456, 9.887 };

    for (int i = 0; i < 10; i++)
      b.insert(arr[i]);

    b.print();

    auto el = b.find(4.3);
    std::cout << *el << std::endl;

    std::cout << "\n~~~~~~~~~~~~~~\nAn exapmle of using mystring" << std::endl;
    mystring str1;
    mystring str2("fir-fir-fir");
    str1 = "myah";
    std::cout << "str1 = " << str1 << std::endl;
    std::cout << "str2 = " << str2 << std::endl;
    str1 = str1 + str2;
    std::cout << "str1 + str2 = " << str1 << std::endl;

    return 0;
}
