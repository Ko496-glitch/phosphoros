#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>
#include <sys/user.h>
/*
 * This file defines the enum we will use for the register. We will abstract in
 * a way that enum fields will be populated according to operating system.
 */

namespace kdb {

  /*
   * This should contain the definition of both ARM(MACOS) and X86(linux)
   * regsiters Note some of the registers work similar but other differ widely,
   * for example the debug register in X86 is 8 (d*) whereas ARM64 has a pack of
   * more than 15
   */
  enum class register_id {

    // ---------------------------
    // X86-64 bit registers
    // ---------------------------

    /* For more info on X86 registers, please visit
      https://math.hws.edu/eck/cs220/f22/registers.html */

    /* rax - rsp  && r8 - r15 are all GPRs */
    rax,
    rbx,
    rcx,
    rdx,
    rsi,
    rdi,
    rbp,
    rsp,
    r8,
    r9,
    r10,
    r11,
    r12,
    r13,
    r14,
    r15

        /*Instruction pointer */
        rip,

    /*Flags */
    rflags,

    /* SIMD (SSE/ AVX ) */
    xmm0,
    xmm1,
    xmm2,
    xmm3,
    xmm4,
    xmm5,
    xmm6,
    xmm7

        /* debug register */
        dr0,
    dr1,
    dr2,
    dr3,
    dr4,
    dr6,
    dr7
        // ---------------------------
        // ARM-64 bit registers
        // ---------------------------

        /*For more info on ARM64 registers, please visit
            https://cybersandeep.gitbook.io/arm64basicguide/chapter-2-understanding-arm64-registers
         */
        /*x0 - x7 (calle saved) used for paramter and result */
        x0,
    x1,
    x2,
    x3,
    x4,
    x5,
    x6,
    x7,
    /*  used for syscall number. */
    x8,

    /* X9 - X15 are caller based register and are used for temp or intermediate
       calcualtion. Use and throw away terminilogy  */
    x9,
    x10,
    x11,
    x12,
    x13,
    x14,
    x15,

    /* x16 and x17 are special register (IPO/ IP1) and used during function
       calls, jmp, goto stmts */
    x16,
    x17,
    x18,
    /* x19 - x28 Callee saved register must be presereved across function calls.
       Function using these regsiters should save the original state and then
       overwrite. */
    x19,
    x20,
    x21,
    x22,
    x23,
    x24,
    x25,
    x26,
    x26,
    x27,
    x28,
    /* X29 - Frame pointer points to starting of the stack frame of a function.
     */
    x29,
    /*x30 is useed to hold the return address when a func call is made */
    x30,
    /*SP points to top of the stack */
    SP,
    /*PC points to address of next instruction */
    PC
  };

  enum class register_type {
    gpr,
    sub_gpr,
    ip,
    flags,
    fpr,
    vector,
    segment,
    debug
  };

  enum class register_format { uint, long_double, double_float, vector; };

  enum class register_info {
    register_id id; std::string_view name; std::int32_t dwarf_id;
    std::size_t size;
    std::size_t offset;
    register_type type;
    register_format format;
  };

}; // namespace kdb
