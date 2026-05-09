#include <unordered_map>
#include <utility>
#include <vector>
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

/*
 * @brief This structure represent the single variable on which automatic
 * differentiation can be performed
 * This class currently only support single operations, that is, derivative of
 * operations that require multiple calculation (tan, log with arbitrary base,
 * etc...) would not be supported.
 * Planned to improve this in the future
 */
class BackPropVariable {

private:
  double forwardValue;
  double backwardValue;
  int id;

private:
  /// This will be nullptr if the variable is intialized
  BackPropVariable *parent1;
  /// This will be nullptr if the variable is intialized or the operation that
  /// return this operator is unary
  BackPropVariable *parent2;
  Operator parentRelation;
  std::unordered_map<int, bool> backwardDependencies;

  static int creationCount;
  /// Calling this would mark the dependency 'id' in the called object as

  /// completed.
  void notifyCompletion(int id);

public:
  BackPropVariable(double value);
  inline double getValue() { return backwardValue; }
  /// The actual back propagation would not be triggered unless all
  /// dependencies's differentation are compoleted. There is a check for
  /// completion. Expect rewrite to reduce checking cost
  void trigger_back_propagation();

  BackPropVariable operator+(BackPropVariable &rhs);
  BackPropVariable operator-(BackPropVariable &rhs);
  BackPropVariable operator*(BackPropVariable &rhs);
  BackPropVariable operator/(BackPropVariable &rhs);

  void markComplete();

private:
  /**
   * @brief Helper function to establish DAG connections for binary operations.
   * @param operand1 Pointer to the left-hand operand.
   * @param operand2 Pointer to the right-hand operand.
   * @return The resulting node with established parent linkages.
   */
  static BackPropVariable createBinaryResult(BackPropVariable *operand1,
                                             BackPropVariable *operand2);

  /**
   * @brief Helper function to establish DAG connections for unary operations.
   * @param operand Pointer to the single operand.
   * @return The resulting node with established parent linkages.
   */
  static BackPropVariable createUnaryResult(BackPropVariable *operand);
  friend BackPropVariable sin(BackPropVariable &x);
  friend BackPropVariable cos(BackPropVariable &x);
  friend BackPropVariable log(BackPropVariable &base, BackPropVariable &x);
  friend BackPropVariable log(BackPropVariable &x);
  friend BackPropVariable pow(BackPropVariable &lhs, BackPropVariable &rhs);
};

extern BackPropVariable sin(BackPropVariable &x);
extern BackPropVariable cos(BackPropVariable &x);
extern BackPropVariable log(BackPropVariable &base, BackPropVariable &x);
extern BackPropVariable log(BackPropVariable &x);
extern BackPropVariable pow(BackPropVariable &base, BackPropVariable &power);
