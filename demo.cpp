#include <particletk/box.hpp>

#include <iostream>
#include <string>

int main(int argc, char** argv) {
  std::function<void(int*, std::string)> show = [] (int* i, std::string str) {
    std::cout << str << *i << std::endl;
  };
  
  std::function<void(int*, int)> add = [] (int* i, int n) {
    *i += n;
  };
  
  PTK::Box<int> b1(new int(10));
  b1.use<void, std::string>(show, std::string("b1: "));
  
  PTK::Box<int> b2(b1);
  b2.use(add, 10);
  b2.use(show, std::string("b2: "));
  b2.use(add, -20);
  
  PTK::Box<int> b3(b2);
  b3.use(show, std::string("b3: "));
 
  PTK::TBox<int, std::unique_ptr> b4(new int(123));
  b4.use(show, std::string("b4: "));

  PTK::Box<int> b5(std::shared_ptr<int>(new int(12345)));
  b5.use(show, std::string("b5: "));

  return 0;
}
