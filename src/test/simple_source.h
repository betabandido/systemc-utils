#ifndef TEST_SIMPLE_SOURCE_H_
#define TEST_SIMPLE_SOURCE_H_

#include <systemc>

namespace sc_util {

/** Simple source with a single output port.
 * 
 * This source sends the sequence 1 to 10.
 * Values are sent 1 ns apart.
 */
class simple_source : public sc_core::sc_module {
  SC_HAS_PROCESS(simple_source);

public:
  sc_core::sc_out<int> out;

  simple_source(const sc_core::sc_module_name& name) {
    SC_THREAD(send);
  }

private:
  void send() {
    for (int i = 1; i <= 10; ++i) {
      out.write(i);
      wait(sc_core::sc_time(1, sc_core::SC_NS));
    }
  }
};

} // namespace

#endif // TEST_SIMPLE_SOURCE_H_

