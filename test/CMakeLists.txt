add_executable(tests tests.cpp)

add_subdirectory("targets")
target_link_libraries(tests
    PRIVATE
        kdb::libkdb
        Catch2::Catch2WithMain
)
include(Catch)
catch_discover_tests(tests)