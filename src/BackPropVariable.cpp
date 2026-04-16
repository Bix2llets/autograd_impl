
#include "BackPropVariable.hpp"
#include <stdexcept>

void BackPropVariable::trigger_back_propagation() {
  // Calculation goes here
  switch (parentRelation) {
  case Operator::Init:
    break;
  case Operator::Add:

    break;
  case Operator::Subtract:

    break;
  case Operator::Multiply:

    break;
  case Operator::Divide:

    break;
  default:
    break;
  }

  if (parent1)
    parent1->trigger_back_propagation();
  if (parent2)
    parent2->trigger_back_propagation();
}

BackPropVariable BackPropVariable::operator+(const BackPropVariable &rhs) {
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.value = this->value + rhs.value;
  return std::move(result);
}
BackPropVariable BackPropVariable::operator-(const BackPropVariable &rhs) {
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.value = this->value - rhs.value;
  return std::move(result);
}
BackPropVariable BackPropVariable::operator*(const BackPropVariable &rhs) {
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.value = this->value * rhs.value;
  return std::move(result);
}
BackPropVariable BackPropVariable::operator/(const BackPropVariable &rhs) {
  if (rhs.value == 0.0)
    throw std::logic_error("Division by zero for a value");
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.value = this->value / rhs.value;
  return std::move(result);
}
