#include <cstddef>
#include <vector>

namespace kdb {
  class pipe {
  private:
    static constexpr unsigned fd_read = 0;
    static constexpr unsigned fd_write = 1;
    int fds_[2];

  public:
    explicit pipe(bool close_on_exec);
    ~pipe();

    int get_read() const { return fds_[fd_read]; }
    int get_write() const { return fds_[fd_write]; }
    int release_read();
    int release_write();
    void close_read();
    void close_write();

    std::vector<std::byte> read();
    void write(std::byte *from, std::size_t bytes);
  };

} // namespace kdb