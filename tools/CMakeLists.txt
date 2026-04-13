# 1. Find the real GNU Readline (Homebrew path)
find_path(READLINE_INCLUDE_DIR readline/readline.h PATHS /opt/homebrew/opt/readline/include NO_DEFAULT_PATH)
find_library(READLINE_LIBRARY NAMES readline PATHS /opt/homebrew/opt/readline/lib NO_DEFAULT_PATH)

add_executable(kdb kdb.cpp)

# 2. Apply the GNU Readline paths to the target
target_include_directories(kdb PRIVATE ${READLINE_INCLUDE_DIR})

# 3. Link correctly (Removed libedit)
target_link_libraries(kdb
    PRIVATE
        kdb::libkdb
        ${READLINE_LIBRARY}
)

include(GNUInstallDirs)

install(
    TARGETS kdb
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)