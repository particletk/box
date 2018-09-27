#include <particlepm.hpp>

using namespace PPM::Utils;

PPM_PACKAGE(p) {
  p->name("box");
  p->version(PPM::Version("v0.1.2"));
  p->description("A wrapper for a mutex and a smart pointer for thread-safe data manipulation. ");
  p->github(PPM::GitHub("particletk", "box"));
  p->license(PPM::License("MIT", "https://github.com/particletk/box/blob/master/LICENSE.txt"));

  if (PPM::dev) {
    PPM::TargetPtr demo = p->executable("ptk-box-demo");
    demo->cpp("c++11");
    demo->cpp_files({
      "demo.cpp"
    });
    demo->cpp_flags(flagcat({
      ("-I" + p->pkg_dir())
    }));
  }
}
