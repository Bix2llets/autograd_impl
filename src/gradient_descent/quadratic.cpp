#include "gradient_descent/quadratic.hpp"
#include <format>
#include <iostream>

std::pair<double, double> computeValue(double x) {
  // 3x^2 + 2x + 10
  BackPropVariable xBackprop(x);
  BackPropVariable xSquare = xBackprop * xBackprop;
  BackPropVariable threeXSquare = 3.0 * xSquare;
  BackPropVariable twoX = 2.0 * xBackprop;
  BackPropVariable sum1 = threeXSquare + twoX;
  BackPropVariable sum2 = sum1 + 10.0;
  sum2.setBackPropValue(1.0);
  sum2.trigger_back_propagation();
  return std::make_pair(sum2.getValue(), xBackprop.getGradient());
}
int main() {
  auto result = computeValue(0);
  std::cout << std::format("result is {}", result.first);
}
