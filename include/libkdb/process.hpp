#pragma once

#include <filesystem>
#include <memory>
#include <sys/types.h>

namespace kdb {

  enum class process_state { stopped, terminated, running, exited };

  class stop_reason {

  public:
    std::uint8_t info;
    process_state reason;
    stop_reason(int wait_reason);
  };

  class process {

  private:
    pid_t pid_{};
    bool terminate_on_end = true;
    process_state state_ = process_state::stopped;
    bool is_attached = true;
    process(pid_t pid, bool terminate_on_end, bool is_attached)
        : pid_(pid), terminate_on_end(terminate_on_end), is_attached(is_attached) {}

  public:
    process() = delete;
    process(const process &) = delete;
    process &operator=(const process &) = delete;

    ~process();
    static std::unique_ptr<process> launch(std::filesystem::path path, bool debug = true);
    static std::unique_ptr<process> attach(pid_t pid);

    pid_t pid() const { return pid_; }
    process_state state() const { return state_; }
    void resume();
    stop_reason wait_on_signal();
  };

} // namespace kdb
