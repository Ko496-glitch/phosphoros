#include <editline/readline.h>
#include <iostream>
#include <string>
#include <string_view>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

namespace {
pid_t attach(int argc, const char **argv) {
  pid_t pid{};

  if (argc == 3 && std::string_view(argv[1]) == "-p") {
    pid = std::atoi(argv[2]);

    if (pid <= 0) {
      std::cerr << "Invalid PID\n";
      return -1;
    }

    if (ptrace(PT_ATTACH, pid, nullptr, 0) < 0) {
      std::perror("Could not attach");
      return -1;
    }

  } else {
    const char *program_path = argv[1];

    if ((pid = fork()) < 0) {
      std::cerr << "Fork failed\n";
      return -1;
    }

    if (pid == 0) {
      // child process

      if (ptrace(PT_TRACE_ME, 0, nullptr, 0) < 0) {
        std::perror("Trace failed");
        return -1;
      }

      if (execlp(program_path, program_path, nullptr) < 0) {
        std::perror("Execution failed");
        return -1;
      }
    }
  }

  return pid;
} // namespace
} // namespace

int main(int argc, const char **argv) {
  if (argc == 1) {
    std::cerr << "No error given\n";
    return -1;
  }
  pid_t pid = attach(argc, argv);

  int wait_status, options{};
  if (waitpid(pid, &wait_status, options) < 0) {
    std::perror("waitpid failed");
    return -1;
  }
  return 0;
}
