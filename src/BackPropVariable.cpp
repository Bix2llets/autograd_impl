
#include "BackPropVariable.hpp"
#include <format>
#include <iostream>
#include <stdexcept>

int BackPropVariable::creationCount = 0;
BackPropVariable::BackPropVariable(double value)
    : forwardValue{value}, backwardValue(0), parent1{nullptr},
      parent2{nullptr} {
  creationCount++;
  id = creationCount;
};
void BackPropVariable::trigger_back_propagation() {
  if (backwardDependencies.size() == 0) {
    this->backwardValue = 1;
  }
  // Calculation goes here
  switch (parentRelation) {
  case Operator::Init:
    break;
  case Operator::Add:
    parent1->backwardValue += this->backwardValue;
    parent2->backwardValue += this->backwardValue;
    break;
  case Operator::Subtract:
    parent1->backwardValue += this->backwardValue;
    parent2->backwardValue -= this->backwardValue;
    break;
  case Operator::Multiply:
    parent1->backwardValue += this->backwardValue * parent2->forwardValue;
    parent2->backwardValue += this->backwardValue * parent1->forwardValue;

    break;
  case Operator::Divide:
    parent1->backwardValue += this->backwardValue * 1.0 / parent2->forwardValue;
    parent2->backwardValue -= this->backwardValue * parent1->forwardValue /
                              (parent2->forwardValue * parent2->forwardValue);
    break;
  default:
    break;
  }

  if (parent1)
    parent1->trigger_back_propagation();
  if (parent2)
    parent2->trigger_back_propagation();
}
BackPropVariable
BackPropVariable::createBinaryResult(BackPropVariable *operand1,
                                     BackPropVariable *operand2) {
  BackPropVariable result(0);
  operand1->backwardDependencies.insert({result.id, false});
  operand2->backwardDependencies.insert({result.id, false});
  result.parent1 = operand1;
  result.parent2 = operand2;
  return std::move(result);
}

BackPropVariable BackPropVariable::operator+(BackPropVariable &rhs) {
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.forwardValue = this->forwardValue + rhs.forwardValue;
  result.parentRelation = Operator::Add;

  return std::move(result);
}
BackPropVariable BackPropVariable::operator-(BackPropVariable &rhs) {
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.forwardValue = this->forwardValue - rhs.forwardValue;
  result.parentRelation = Operator::Subtract;
  return std::move(result);
}
BackPropVariable BackPropVariable::operator*(BackPropVariable &rhs) {
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.forwardValue = this->forwardValue * rhs.forwardValue;
  result.parentRelation = Operator::Multiply;
  return std::move(result);
}
BackPropVariable BackPropVariable::operator/(BackPropVariable &rhs) {
  if (rhs.forwardValue == 0.0)
    throw std::logic_error("Division by zero for a value");
  BackPropVariable result = createBinaryResult(this, &rhs);
  result.forwardValue = this->forwardValue / rhs.forwardValue;
  result.parentRelation = Operator::Divide;
  return std::move(result);
}
