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
    // Notes on register read/write behavior by architecture:
    // - x86_64 (Linux): register_info offsets point into struct user and its
    //   user_regs_struct/user_fpregs_struct members. A read/write path can
    //   snapshot those structs (PTRACE_GETREGS/GETFPREGS or GETREGSET) and
    //   slice bytes by offset. Sub-registers (eax/ax/ah/al, etc.) require
    //   masking and preserving untouched bits in the parent GPR.
    // - AArch64: GPRs live in user_pt_regs while SIMD/FP live in
    //   user_fpsimd_state and are typically fetched via separate regsets
    //   (NT_PRSTATUS vs NT_FPREGSET). Wn registers alias the low 32 bits of Xn
    //   (zero-extended on write).
    // Because regset acquisition differs, it is likely best to keep a shared
    // public read/write API but route the backend to per-arch/per-regset
    // helpers rather than a single monolithic implementation.
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
