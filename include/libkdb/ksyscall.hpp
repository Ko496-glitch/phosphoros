#pragma once
#include <sys/ptrace.h>

namespace kdb {
  /*
   * This library creates an abstraction for the syscalls.
   * Usage should be simple, just call the abstracted syscall and it will figure
   * out based on OS which one to call.
   */

#ifdef __linux__
  /*
   *  long ptrace(enum __ptrace_request op, pid_t pid,
                     void *addr, void *data);
   */
  struct ptrace_args {
    enum __ptrace__req;
    pid_t pid;
    void *addr;
    void *data;
    long result;
  };

#elif defined(__APPLE__)
  /*
   *int
        ptrace(int request, pid_t pid, caddr_t addr, int data);
   */
  struct ptrace_args {
    int req;
    pid_t pid;
    caddr_t addr;
    int data;
    int result;
  };
#endif

  struct pip_args {
    inn

  }

  void
  ptrace(ptrace_args &args);
} // namespace kdb
