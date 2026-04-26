#include "ksyscall.hpp"
#include <cstring>
#include <iostream>
#include <stdexcept>


namespace kdb {

  void ktrace(ptrace_args &args) {
#ifdef __linux__
    args.result = ptrace(args.req, args.pid, args.args.addr, args.data);

#elif defined(__APPLE__)
    args.result = ptrace(args.req, args.pid, args.addr, args.data);
#endif
  }

} // namespace kdb