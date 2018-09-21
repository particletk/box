# particletk/box

A wrapper for a mutex and a smart pointer for thread-safe data manipulation. 

## Install

```cpp
#include <particlepm.hpp>

// ...

PPM_PACKAGE(p) {
  // ...

  PPM::GitHubPtr ptk_box = p->github_repo("particletk", "box");

  // ...

  target->cpp_flags(flagcat({
    // ...
    ("-I" + ptk_box->dir()),
    // ...
  }));

  // ...
}

```

## Usage

```cpp
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
  
  return 0;
}
```

`use` function is atomic across all same box instances, so you can freely use the box in a multithreaded environment.
