#ifndef MAIN_SIGNAL_POOL_H_
#define MAIN_SIGNAL_POOL_H_

#include <memory>
#include <vector>

#include <systemc>

namespace sc_util {

/** 
 * Pool of SystemC signals.
 *
 * This class implements a pool of signals so that connecting ports between
 * modules becomes easier. The data type in the signal is generic, as well as
 * the signal type itself. For instance, sc_buffer can be used instead of
 * sc_signal.
 */
template<typename T, class signal_type = sc_core::sc_signal<T>>
class signal_pool {
public:
  /**
   * Creates a signal.
   *
   * @param args Arguments to pass to the signal constructor.
   * @return A reference to the new signal.
   */
  template<typename... Args>
  static signal_type& create_signal(Args&&... args) {
    signals_.emplace_back(
        std::make_unique<signal_type>(std::forward<Args>(args)...));
    return *signals_.back();
  }

private:
  // Signal pointer.
  typedef std::unique_ptr<signal_type> signal_ptr;

  // Vector containing all the signals.
  static std::vector<signal_ptr> signals_;
};

template<typename T, class signal_type>
std::vector<typename signal_pool<T, signal_type>::signal_ptr>
  signal_pool<T, signal_type>::signals_;

} // namespace

#endif // MAIN_SIGNAL_POOL_H

