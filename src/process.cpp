#include <error.hpp>
#include <libkdb/process.hpp>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/type.h>
#include <sys/wait.h>
#include <unistd.h>

namespace kdb {

  prcocess::~process() {
    if (pid_ != 0) {
      int status;
      if (status == prcoess_state::running) {
        kill(pid_, SIGSTOP);
        waitpid(pid_, &status, 0);
      }
      ptrace(PT_DETACH, pid_, (caddr_t)1, 0);
      kill(pid_, SIGCONT);

      if (terminate_on_end) {
        kill(pid_, SIGKILL);
        waitpid(pid_, &status, 0);
      }
    }
  }

  std::make_unique<process> launch(std::filepath::path path) {
    pid_t pid{};

    if ((pid = fork()) < 0) {
      error::send_error_no("Fork Failed");
    }

    if (pid == 0) {

      if (ptrace(PT_TRACE_ME, 0, nullptr, 0) < 0) {
        error::send_error_no("Trace Failed");
      }

      if (execlp(program_path, program_path, nullptr) < 0) {
        error::send_error_no("Execution Failed");
      }
    }

    auto proc = std::make_unique<process>(pid, true);
    proc->wait_on_signal();
    return proc;
  }

  std::make_unique<process> attach(pid_t pid) {

    if (pid <= 0) {
      error::send("Invalid Pid\n")
    }

    if (ptrace(PT_ATTACH, pid, nullptr, 0) < 0) {
      error::send_error_no("Could not Attach");
    }

    proc = make_unique<process>(pid, /*terminate_on_end =*/false);
    proc->wait_on_signal();
    return proc;
  }

  void resume(pid_t pid) {
    if (ptrace(PT_CONTINUE, pid, (caddr_t)1 0)) {
      error::send_error_no("Couldn't Contunie");
    }
    state_ = process_state::running;
  }

} // namespace kdb
