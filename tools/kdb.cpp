#include <algorithm>
#include <cstdio>
#include <libkdb/error.hpp>
#include <iostream>
#include <readline/history.h>
#include <readline/readline.h>
#include <libkdb/process.hpp>
#include <sstream>
#include <string>
#include <string_view>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <vector>

namespace {

  std::vector<std::string> split(std::string_view str, char delimiter) {
    std::vector<std::string> out{};
    std::stringstream ss(std::string{str});
    std::string word;

    while (std::getline(ss, word, delimiter)) {
      out.push_back(word);
    }
    return out;
  }

  bool is_prefix(std::string_view prefix, std::string_view of) {
    if (prefix.length() > of.length())
      return false;
    return std::equal(prefix.begin(), prefix.end(), of.begin());
  }

  void print_stop_reason(const kdb::stop_reason reason,
                         const kdb::process &process) {
    std::cout << "Process" << ": " << process.pid();
    std::cout << std::endl;

    switch (reason.reason) {
    case kdb::process_state::exited:
      std::cout << "exited with status" << static_cast<int>(reason.info);
      break;

    case kdb::process_state::terminated:
      std::cout << "Terminated with status" << strsignal(reason.info);
      break;

    case kdb::process_state::stopped:
      std::cout << "Stopped with status" << strsignal(reason.info);
      break;
    }
    std::cout << std::endl;
  }

  void handle_command(std::unique_ptr<kdb::process> &proc,
                      std::string_view line) {

    auto args = split(line, ' ');
    auto command = args[0];

    /*This function will check for prefix compared to given user command, for eg
     * - c, cont and continue should do the same thing */
    if (is_prefix(command, "continue")) {
      proc->resume();
      kdb::stop_reason reason = proc->wait_on_signal();
      print_stop_reason(reason, *proc);
    } else {
      kdb::error::send("Unknown Commands\n");
    }
  }

  /* Call the libkdb kdb::attach if the process already exist otherwise
  kdb::launch, Abstraction control */

  std::unique_ptr<kdb::process> attach(int argc, const char **argv) {
    pid_t pid{};

    if (argc == 3 && std::string_view(argv[1]) == "-p") {
      pid = std::atoi(argv[2]);
      return kdb::process::attach(pid);
    } else {
      const char *program_path = argv[1];
      return kdb::process::launch(program_path);
    }
  }
  void main_loop(std::unique_ptr<kdb::process> &process) {
    char *line = nullptr;
    while ((line = readline("kdb> ")) != nullptr) {

      std::string line_str(line);

      if (line == std::string_view("")) {
        if (history_length > 0) {
          line_str = history_list()[history_length - 1]->line;
        }
      } else {
        line_str = line;
        add_history(line);
      }
      free(line);
      if (!line_str.empty()) {
        try {
          handle_command(process, line_str);
        } catch (const kdb::error &what) {
          std::cout << what.what() << std::endl;
        }
      }
    }
  }
} // namespace

int main(int argc, const char **argv) {
  if (argc == 1) {
    std::cerr << "No error given\n";
    return -1;
  }
  try {
    auto process = attach(argc, argv);
  } catch (const kdb::error &err) {
    std::cout << err.what() << '\n';
  }

  return 0;
}
