#pragma once

#include <filesystem>
#include <memory>
#include <sys/types.h>

namespace kdb {

  enum class process_state { stopped, terminated, running, exited };

  class process {

  private:
    pid_t pid_{};
    bool terminate_on_end = true;
    process_state state_ = process_state::stopped;
    process(pid_t pid, bool terminate_on_end)
        : pid_(pid) : terminate_on_end(terminate_on_end) {}

  public:
    process() = delete;
    process(const process &) = delete;
    process &operator=(const process &) = delete;

    ~process();

    static std::make_unique<process> launch(std::filepath::path path);
    static std::make_unique<process> attach(pid_t pid);

    pid_t pid() const { return pid_; }
    process_state state() const { return state_; }
    void resume();
  };

} // namespace kdb
