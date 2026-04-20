#include <fcntl.h>
#include <libkdb/error.hpp>
#include <libkdb/pipe.hpp>
#include <libkdb/process.hpp>
#include <unistd.h>
#include <utility>

namespace kdb {

  /* pipe2(pipe, flags) we will close the pipe when exec passes, Note - there is
   * no need but if we fail then we pass the error message to parent process */
  pipe::pipe(bool close_on_exec) {
    if (::pipe(fds_) < 0) {
      error::send_error_no("Pipe Creation Failed");
    }

    if (close_on_exec) {
      if (fcntl(fds_[fd_read], F_SETFD, O_CLOEXEC) < 0 ||
          fcntl(fds_[fd_write], F_SETFD, O_CLOEXEC) < 0) {
        error::send_error_no("Failed to close the pipe(O_CLOEXC)");
      }
    }
  }

  pipe::~pipe() {
    close_read();
    close_write();
  }

  int pipe::release_read() { return std::exchange(fds_[fd_read], -1); }

  int pipe::release_write() { return std::exchange(fds_[fd_write], -1); }

  void pipe::close_read() {
    if (fds_[fd_read] != -1) {
      close(fds_[fd_read]);
      fds_[fd_read] = -1;
    }
  }

  void pipe::close_write() {
    if (fds_[fd_write] != -1) {
      ::close(fds_[fd_write]);
      fds_[fd_write] = -1;
    }
  }
  
  std::vector<std::byte> pipe::read() {
    char buf[1024];
    int chars_read{};
    if ((chars_read = ::read(fds_[fd_read], buf, sizeof(1024))) < 1) {
      error::send_error_no("Could not read from the buffer");
    }
    // dont confuse yourself this is just reinterpret_cast<std::bytes>(buf);
    auto bytes = static_cast<std::byte*>(static_cast<void *>(buf));
    return std::vector<std::byte>(bytes, bytes + chars_read);
  }
  void pipe::write(std::byte &from, std::size_t bytes) {
    if (::read(fds_[fd_write], &from, bytes) < 0) {
      error::send_error_no("Write in Pipe failed");
    }
  }
} // namespace kdb