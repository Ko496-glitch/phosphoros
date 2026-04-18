#include <catch2/catch_test_macros.hpp>
#include<libkdb/process.hpp>
#include<signal.h>
#include<sys/types.h>
#include<libkdb/error.hpp>

namespace{
    bool process_exist(pid_t pid){
        auto sig = kill(pid,0);
        return (sig != -1 && errno != ESRCH);
    }
}//namespace

TEST_CASE("process::launch success", "[process]"){
    auto proc =  kdb::process::launch("yes");
    REQUIRE(process_exist(proc->pid()));
}

TEST_CASE("process::launc no_such_program", "[process]"){
    REQUIRE_THROWS_AS(kdb::process::launch("this_should_not_work"), kdb::error);
}
