#include <catch2/catch_test_macros.hpp>
#include <VExercise4.h>
#include <cstdint>

// I completely overcomplicated exercise 4 when I first did it
// I only need to check that the decoder works no matter the input

void test_cs(VExercise4& model) {
  model.cs = 0;
  for (model.sel = 0; model.sel < 4; ++model.sel) {
    model.eval();
    REQUIRE(model.out == 0);
  }
}

void test_sel(VExercise4& model) {
  model.cs = 1;
  model.alpha = 2;
  model.beta = 3;
  model.gamma = 4;
  for (model.sel = 0; model.sel < 3; ++model.sel){
    model.eval();
    REQUIRE(model.out == (model.sel + 2));
  }
  model.eval();
  REQUIRE(model.out == 2);
}

TEST_CASE("Exercise 4") {
  VExercise4 model;
  test_cs(model);
  test_sel(model);

}
