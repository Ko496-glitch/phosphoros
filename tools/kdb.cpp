#include <algorithm>
#include <cstdio>
#include <iostream>
#include <readline/history.h>
#include <readline/readline.h>
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
      if(prefix.length() > of.length())return false;
      return std::equal(prefix.begin(), prefix.end(), of.begin());
  }
  
  void resume(pid_t pid) {
      if(ptrace(PT_CONTINUE,pid,(caddr_t)1, 0) < 0){
          std::perror("Couldn't Continue");
          std::exit(-1);
      }
          
  }
  
  void wait_on_signal(pid_t pid) {
      int wait_status{};
      int options{};
      if(waitpid(pid, &wait_status,options) < 0){
          std::perror("Blocking/ waitpid failed");
          std::exit(-1);
      }
      
  }

  void handle_command(pid_t pid, std::string_view line) {

    auto args = split(line, ' ');
    auto command = args[0];

    /*This function will check for prefix compared to given user command, for eg
     * - c, cont and continue should do the same thing */
    if (is_prefix(command, "continue")) {
      resume(pid);
      wait_on_signal(pid);
    } else {
      std::cerr << "Unknown Commands\n";
    }
  }

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
          _exit(-1);
        }

        if (execlp(program_path, program_path, nullptr) < 0) {
          std::perror("Execution failed");
          _exit(-1);
        }
      }
    }

    return pid;
  }
} // namespace

int main(int argc, const char **argv) {
  if (argc == 1) {
    std::cerr << "No error given\n";
    return -1;
  }
  pid_t pid = attach(argc, argv);
  int wait_status{}, options{};
  if (waitpid(pid, &wait_status, options) < 0) {
    std::perror("waitpid failed");
    return -1;
  }
  char *line = nullptr;
  while ((line = readline("kdb> ")) != nullptr) {

    std::string line_str(line);
    
    if (line == std::string_view("")) {
      if (history_length > 0) {
        line_str = history_list()[history_length - 1]->line;
      } 
    }
    else {
      line_str = line;
      add_history(line);
    }
    free(line);
    if (!line_str.empty()) {
      handle_command(pid, line_str);
      free(line);
    }
  }
  return 0;
}
