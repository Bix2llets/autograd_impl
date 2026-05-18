#include "BackPropModules/BackPropVariable.hpp"
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

TEST(mixedtype, var_plus_double) {
  BackPropVariable a(5);
  BackPropVariable b = a + 3.0;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), 1.0);
}

TEST(mixedtype, double_plus_var) {
  BackPropVariable a(5);
  BackPropVariable b = 3.0 + a;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), 1.0);
}

TEST(mixedtype, var_times_double) {
  BackPropVariable a(5);
  BackPropVariable b = a * 3.0;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), 3.0);
}

TEST(mixedtype, double_times_var) {
  BackPropVariable a(5);
  BackPropVariable b = 3.0 * a;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), 3.0);
}

TEST(mixedtype, var_minus_double) {
  BackPropVariable a(5);
  BackPropVariable b = a - 3.0;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), 1.0);
}

TEST(mixedtype, double_minus_var) {
  BackPropVariable a(5);
  BackPropVariable b = 3.0 - a;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), -1.0);
}

TEST(mixedtype, var_divided_by_double) {
  BackPropVariable a(10);
  BackPropVariable b = a / 2.0;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), 0.5);
}

TEST(mixedtype, double_divided_by_var) {
  BackPropVariable a(2.0);
  BackPropVariable b = 10.0 / a;
  b.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(a.getGradient(), -2.5);
}

TEST(mixedtype, chain_with_constants) {
  BackPropVariable x(2);
  BackPropVariable xSq = x * x;
  BackPropVariable threeXSq = 3.0 * xSq;
  BackPropVariable twoX = 2.0 * x;
  BackPropVariable sum1 = threeXSq + twoX;
  BackPropVariable y = sum1 + 10.0;
  y.trigger_back_propagation();
  ASSERT_DOUBLE_EQ(x.getGradient(), 14.0);
}
