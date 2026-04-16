#include <vector>
class ParentNode;
enum class Operator : int {
  Add,
  Subtract,
  Multiply,
  Divide,
  Init, // For the case of initialization
  // Temporarity four operators, will extend it to all binary and unary
};
class BackPropVariable {

private:
  double value;

private:
  BackPropVariable *parent1; // This can be a nullptr if the variable is
                             // initialized and not calculated
  BackPropVariable *parent2; // This can be a nullptr if the operator is unary
  Operator parentRelation;

public:
  BackPropVariable(double value) : value{value} {}
  inline double getValue() { return value; }
  void trigger_back_propagation();

  BackPropVariable operator+(const BackPropVariable &rhs);
  BackPropVariable operator-(const BackPropVariable &rhs);
  BackPropVariable operator*(const BackPropVariable &rhs);
  BackPropVariable operator/(const BackPropVariable &rhs);

private:
  BackPropVariable createBinaryResult(const BackPropVariable *operand1,
                                      const BackPropVariable *operand2);

  BackPropVariable createUnaryResult(const BackPropVariable *operand);
};
