#include <catch2/catch_test_macros.hpp>
#include <fstream>
#include <libkdb/error.hpp>
#include <libkdb/process.hpp>
#include <signal.h>
#include <sys/types.h>

namespace {
  bool process_exist(pid_t pid) {
    auto sig = kill(pid, 0);
    return (sig != -1 && errno != ESRCH);
  }

  char get_process_status(pid_t pid) {
    std::ifstream stat("/proc/" + std::to_string(pid) + "/stat");
    std::string data;
    std::getline(stat, data);
    /*file structure for /proc/pid/stat/  is something like 1 (init) S 0 1 1 ..
     * We generally care about the third value (S) which tells us the state of
     * given process, here 1 means the pid, (init) means the process name
     */

    auto index_of_last_paranthesis = data.rfind(')');
    auto index_of_state = index_of_last_paranthesis + 2;
    return data[index_of_state];
  }
} // namespace

TEST_CASE("process::launch success", "[process]") {
  auto proc = kdb::process::launch("yes");
  REQUIRE(process_exist(proc->pid()));
}

TEST_CASE("process::launc no_such_program", "[process]") {
  REQUIRE_THROWS_AS(kdb::process::launch("this_should_not_work"), kdb::error);
}

TEST_CASE("process::attach success", "[process]") {
  auto target = kdb::process::launch("targets/run_endlessely", false);
  auto proc = kdb::process::attach(target->pid());
  REQUIRE(get_process_status(target->pid()) == 't');
}

TEST_CASE("process::attach invalid PID", "[process]") {
  REQUIRE_THROWS_AS(kdb::process::attach(0), kdb::error);
}

TEST_CASE("process::resume success", "[process]") {
  auto proc = kdb::process::launch("target/run_endlessly");
  proc->resume();
  auto status = get_process_status(proc->pid());
  auto success = (status == 'R') || (status == 'S');
  REQUIRE(success);
}
