#ifndef MAIN_TEST_FUNC_H_
#define MAIN_TEST_FUNC_H_

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <cstdlib>
#include <stdexcept>

#include <boost/format.hpp>
#include <gtest/gtest.h>

namespace sc_util {

/**
 * Runs a test in a different process.
 *
 * @param func A function containing the test.
 */
template<typename test_function>
void run_test(test_function func) {
  auto pid = fork();
  switch (pid) {
  case -1:
    throw std::runtime_error("Error forking process");
  case 0:
    try { func(); }
    catch (const std::exception& e) {
      std::cout << boost::format("Exception caught %1%\n") % e.what();
      exit(1);
    }
    catch (...) { exit(1); }
    exit(0);
  default:
    {
      int status;
      waitpid(pid, &status, 0);
      if (!WIFEXITED(status))
        throw std::runtime_error("Test process ended unexpectedly");
      if (WEXITSTATUS(status))
        FAIL();
    }
    break;
  }
}

} // namespace

/** Declares a SystemC test. */
#define SYSTEMC_TEST(test_case_name, test_name) \
  void name##_impl();                           \
  TEST(test_case_name, test_name) {             \
    sc_util::run_test(name##_impl);             \
  }                                             \
  void name##_impl()

#endif // MAIN_TEST_FUNC_H_

