#include <iostream>

#include <gtest/gtest.h>

#include <signal_pool.h>
#include <test_func.h>

#include "simple_sink.h"
#include "simple_source.h"

using namespace sc_core;
using namespace sc_util;

class test_sink : public simple_sink {
public:
  test_sink(const sc_module_name& name)
    : simple_sink(name)
  {}

private:
  mutable int expected_value_ { 1 };

  void receive(int value) const {
    EXPECT_EQ(value, expected_value_);
    ++expected_value_;
  }
};

void common_test() {
  simple_source src("source");
  test_sink sink("sink");
  auto& signal = signal_pool<int>::create_signal("wire");

  src.out(signal);
  sink.in(signal);

  sc_start();
}

SYSTEMC_TEST(signal_pool_test, simple1) {
  common_test();
}

SYSTEMC_TEST(signal_pool_test, simple2) {
  common_test();
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

