#pragma once

#include <libkdb/register_info.hpp>
#include <libkdb/types.hpp>
#include <sys/user.h>

namespace kdb {
  class process;
  class registers {
  private:
    friend process;
    registers(process &proc) : proc_(&proc) {}
    user data_ : process *proc_;

  public:
    registers() = delete;
    registers(const registers &) = delete;
    registers &operator=(const registers &) = delete;
    using value = std::variant;

    using value = std::variant<std::uint8_t, std::uint16_t, std::uint32_t,
                               std::uint64_t, std::uint128_t, byte64, byte128,
                               float, double, long double>
        // TODO(arm64): wire up register read/write for AArch64 using per-regset
        // backends (NT_PRSTATUS/NT_FPREGSET) and Wn/Xn aliasing behavior.
        value read(const register_info &info) const;
    value write(const register_info &info, value val);

    template <typename T> T read_by_id(register_id id) {
      return std::get<T>(read(register_info_by_id(id)));
    }

    template <typename T> T write_by_id(register_id, value val) {
        write(register_info_by_id(id), val));
    }
  };

} // namespace kdb
