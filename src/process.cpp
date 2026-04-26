#include <libkdb/error.hpp>
#include <libkdb/pipe.hpp>
#include <libkdb/process.hpp>
#include <signal.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
namespace kdb {

  process::~process() {
    if (pid_ != 0) {
      int status;
      if (is_attached) {
        if (state_ == process_state::running) {
          kill(pid_, SIGSTOP);
          waitpid(pid_, &status, 0);
        }
        ptrace(PT_DETACH, pid_, (caddr_t)1, 0);
        kill(pid_, SIGCONT);
      }
      if (terminate_on_end) {
        kill(pid_, SIGKILL);
        waitpid(pid_, &status, 0);
      }
    }
  }

  void exit_with_perror(pipe &channel, std::string const &prefix) {
    auto message = prefix + ": " + std::strerror(errno);

    channel.write(reinterpret_cast<std::byte *>(message.data()),
                  message.size());
    exit(-1);
  }

  std::unique_ptr<process> process::launch(std::filesystem::path path,
                                           bool debug) {
    pid_t pid{};

    pipe channel(false);
    if ((pid = fork()) < 0) {
      error::send_error_no("Fork Failed");
    }

    if (pid == 0) {
      channel.close_read();
      if (debug && ptrace(PT_TRACE_ME, 0, nullptr, 0) < 0) {
        exit_with_perror(channel, "Trace Failed");
      }

      if (execlp(path.c_str(), path.c_str(), nullptr) < 0) {
        exit_with_perror(channel, "Execution Failed");
      }
    }

    channel.close_write();
    auto data = channel.read();
    channel.close_read();

    if (data.size() > 0) {
      waitpid(pid, nullptr, 0);
      auto chars = static_cast<char *>(static_cast<void *>(data.data()));
      error::send(std::string(chars, chars + data.size()));
    }
    auto proc = std::unique_ptr<process>(new kdb::process(pid, true, debug));
    if (debug)
      proc->wait_on_signal();
    return proc;
  }

  std::unique_ptr<process> process::attach(pid_t pid) {

    if (pid <= 0) {
      error::send("Invalid Pid\n");
    }

    if (ptrace(PT_ATTACH, pid, nullptr, 0) < 0) {
      error::send_error_no("Could not Attach");
    }

    std::unique_ptr<process> proc = std::unique_ptr<process>(
        new process(pid, /*terminate_on_end =*/false, /*attached= */ true));
    proc->wait_on_signal();
    return proc;
  }

  void process::resume() {
    if (ptrace(PT_CONTINUE, pid_, (caddr_t)1, 0)) {
      error::send_error_no("Couldn't Contunie");
    }
    state_ = process_state::running;
  }

  stop_reason::stop_reason(int wait_status) {
    if (WIFEXITED(wait_status)) {
      reason = process_state::exited;
      info = WEXITSTATUS(wait_status);
    } else if (WIFSIGNALED(wait_status)) {
      reason = process_state::terminated;
      info = WTERMSIG(wait_status);
    } else if (WIFSTOPPED(wait_status)) {
      reason = process_state::stopped;
      info = WSTOPSIG(wait_status);
    }
  }

  stop_reason process::wait_on_signal() {
    int wait_status{};
    int options{};
    if (waitpid(pid_, &wait_status, options) < 0) {
      error::send_error_no("Waitpid failed\n");
    }
    stop_reason reason(wait_status);
    state_ = reason.reason;
    return reason;
  }

} // namespace kdb
