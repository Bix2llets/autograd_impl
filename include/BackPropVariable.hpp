#include <unordered_map>
#include <utility>
#include <vector>
class ParentNode;
enum class Operator : int {
  Add,
  Subtract,
  Multiply,
  Divide,
  Init, // For the case of initialization
  Power,
  LogarithmE, // Natural logarithm
  LogarithmN, // Other logarithm
  Sin,
  Cos,

  // Temporarity four operators, will extend it to all binary and unary
};
class BackPropVariable {

private:
  double forwardValue;
  double backwardValue;
  int id;

private:
  BackPropVariable *parent1; // This can be a nullptr if the variable is
  BackPropVariable *parent2; // This can be a nullptr if the operator is unary
  Operator parentRelation;
  std::unordered_map<int, bool> backwardDependencies;

  static int creationCount;

public:
  BackPropVariable(double value);
  inline double getValue() { return backwardValue; }
  void trigger_back_propagation();

  BackPropVariable operator+(BackPropVariable &rhs);
  BackPropVariable operator-(BackPropVariable &rhs);
  BackPropVariable operator*(BackPropVariable &rhs);
  BackPropVariable operator/(BackPropVariable &rhs);

  void markComplete();

private:
  BackPropVariable createBinaryResult(BackPropVariable *operand1,
                                      BackPropVariable *operand2);

  BackPropVariable createUnaryResult(BackPropVariable *operand);
};
