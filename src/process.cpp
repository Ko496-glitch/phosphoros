#include <libkdb/process.hpp>
#include <sys/ptrace.h>
#include <sys/type.h>
#include <sys/wait.h>
#include <unistd.h>

namespace kdb {

  std::make_unique<process> launch(std::filepath::path path) {
    pid_t pid{};

    if ((pid = fork()) < 0) {
      std::cerr << "Fork failed\n";
      return -1;
    }

    if (pid == 0) {

      if (ptrace(PT_TRACE_ME, 0, nullptr, 0) < 0) {
        std::perror("Trace failed");
        _exit(-1);
      }

      if (execlp(program_path, program_path, nullptr) < 0) {
        std::perror("Execution failed");
        _exit(-1);
      }
    }

    auto proc = std::make_unique<process>(pid, true);
    proc->wait_on_signal();
    return proc;
  }

  std::make_unique<process> attach(pid_t pid) {
      
      if (pid <= 0) {
        std::cerr << "Invalid PID\n";
      }
      
      if (ptrace(PT_ATTACH, pid, nullptr, 0) < 0) {
          error::send_errno("Could not attach");
      }
      int wait_status{}, options{};
    
      if (waitpid(pid, &wait_status, options) < 0) {
          
          std::perror("waitpid failed");
          return -1;
      }
    
      proc = make_unique<process>(pid, false);
      proc->wait_on_signal();
      return proc;
  }

} // namespace kdb
