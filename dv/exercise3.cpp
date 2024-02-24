#include <catch2/catch_test_macros.hpp>
#include <VExercise3.h>
#include <cstdint>
#include <random>

uint8_t mystery1(uint8_t a, uint8_t b, uint8_t c) {
  switch (a) {
    case 0: return ((b & 0x7) << 3) | (c & 0x7);
    case 1: return (1 << 6) | ((c & 0x7) << 3) | (b & 0x7);
    case 2: return b;
    default: return c;
  }
}

struct Mystery2 {
  uint16_t count = 0;
  uint16_t out;

  uint16_t reset(uint8_t a_in, uint8_t b_in) {
    out = b_in << 8 | a_in;
    count = 0;
    return out;
  }

  uint16_t step(uint8_t a_in, uint8_t b_in) {
    count %= 5;
    switch(count++) {
      case 0: out = a_in << 8 | (out & 0xFF);
      break;
      case 1: out = (out & 0xFF00) | b_in;
      break;
      case 2: out = out << 8 | out >> 8;
      break;
      case 3: out = (out << 12) | ((out & 0xF0) << 4) | ((out >> 4) & 0xF0) | (out >> 12);
      break;
      default: out = (std::popcount(out)) & 1;
    }
    return out;
  }
};

struct Exercise3_Sim {
  Mystery2 state;

  uint16_t reset(uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in = mystery1(a & 0x3, b & 0xFF, c & 0xFF);
    uint8_t b_in = mystery1(a >> 2, b >> 8, c >> 8);
    return state.reset(a_in, b_in);
  }

  uint16_t step (uint8_t a, uint16_t b, uint16_t c) {
    uint8_t a_in = mystery1(a & 0x3, b & 0xFF, c & 0xFF);
    uint8_t b_in = mystery1(a >> 2, b >> 8, c >> 8);
    return state.step(a_in, b_in);
  }
};

void step(VExercise3& model) {
  model.clk = 1;
  model.eval();
  model.clk = 0;
  model.eval();
}

TEST_CASE("Exercise 3") {
  VExercise3 model;
  Exercise3_Sim sim;
  for (int num_test = 1; num_test < 100; ++num_test){
    model.a = rand() & 0xF;
    model.b = rand() & 0xFFFF;
    model.c = rand() & 0xFFFF;
    model.reset = 1;
    step(model);
    REQUIRE(model.out == sim.reset(model.a, model.b, model.c));
    model.reset = 0;
    for (int cycles = 0; cycles < 100; ++cycles) {
      uint16_t expected = sim.step(model.a, model.b, model.c);
      step(model);
      REQUIRE(model.out == expected);
    }
  }
}
