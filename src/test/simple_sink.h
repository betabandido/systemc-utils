#ifndef TEST_SIMPLE_SINK_H_
#define TEST_SIMPLE_SINK_H_

#include <systemc>

namespace sc_util {

/** Simple sink with a single input port.
 * 
 * The sink accepts integer values.
 * Each time a value is received, receive(int value) is called.
 */
class simple_sink : public sc_core::sc_module {
  SC_HAS_PROCESS(simple_sink);

public:
  sc_core::sc_in<int> in;

  simple_sink(const sc_core::sc_module_name& name) {
    SC_METHOD(receive);
    sensitive << in;
    dont_initialize();
  }

private:
  void receive() {
    assert(in.event());
    receive(in.read());
  }

  virtual void receive(int value) const = 0;
};

} // namespace

#endif // TEST_SIMPLE_SINK_H_

