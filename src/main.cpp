#include "BackPropVariable.hpp"
#include <format>
#include <iostream>

int main(int argc, char **argv) {
  BackPropVariable a(2);
  BackPropVariable b(4);
  BackPropVariable c = a / b;
  c.trigger_back_propagation();
  std::cerr << std::format("Test result: {} {} {}", a.getValue(), b.getValue(),
                           c.getValue());
}
