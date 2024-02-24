#include <catch2/catch_test_macros.hpp>
#include <VExercise1.h>
#include <cstdint>

uint8_t expected(uint8_t op, uint8_t a, uint8_t b) {
  switch (op) {
    case 0: 
      return a ^ b;
    case 1: 
      if (b >= 8) return 0;
      else return a << b;
    case 2:
      if (!b) return 0;
      else return a % b;
    default: 
      return ~(a & b);
    }
}

void test_op(uint8_t op) {
  VExercise1 model;
  model.op = op;
  model.a = 0;
  model.b = 0;
  do {
    do {
      model.eval();
      REQUIRE(model.out == expected(op, model.a, model.b));
    } while (++model.b);  
  } while(++model.a);
}

TEST_CASE("Exercise 1") {
  for (uint8_t op = 0; op < 4; ++op) test_op(op);
}

// For Debugging
//
// TEST_CASE("Opcode 0, XOR") {
//   test_op(0);
// }
// TEST_CASE("Opcode 1, Left Shift") {
//   test_op(1);
// }
// TEST_CASE("Opcode 2, Modulo") {
//   test_op(2);
// }
// TEST_CASE("Opcode 3, NAND") {
//   test_op(3);
// }
