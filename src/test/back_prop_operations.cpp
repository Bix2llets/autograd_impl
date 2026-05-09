#include "BackPropVariable.hpp"
#include <gtest/gtest.h>

TEST(basicvariablepropagation, diamondshapedtwobranches) {
  BackPropVariable a(2);
  BackPropVariable b(4);
  BackPropVariable c = a / b;
  BackPropVariable d = a * b;
  BackPropVariable e = c * d;
  e.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getValue(), 4.0);
  ASSERT_DOUBLE_EQ(b.getValue(), 0.0);
  ASSERT_DOUBLE_EQ(c.getValue(), 8.0);
  ASSERT_DOUBLE_EQ(d.getValue(), 0.5);
  ASSERT_DOUBLE_EQ(e.getValue(), 1.0);
  return;
}
TEST(propagation, linear) {
  BackPropVariable a(1);
  BackPropVariable b(3);
  return;
}
