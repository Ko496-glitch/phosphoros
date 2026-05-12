#pragma once

#include <cstddef>
#include <cstdint>
#include <libkdb/error.hpp>
#include <libkdb/ksyscall.hpp>
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

#define DEFINE_REGSITER(name, dwarf_id, size, offset, type, foramt) name
#include <libkdb/register.inc>
#undef DEFINE_REGISTER
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

  inline constexpr const register_info g_ register_infos[] =
      {
#define DEFINE_REGSITER(name, dwarf_if, size, offset, type, format)            \
  {register_id::name, #name, dwarf_id, size, offset, format}
#include <include/libkdb/register.inc>
#undef DEFINE_REGSITER
  }

      template <typename T>
      const register_info & register_info_by(T t) {
    auto it = std::find_if(std::begin(g_regsiter_info),
                           std::end(g_register_infos), t);
    if (it == std::end(g_register_infos))
      error::send("Can't find register info");
    return *it;
  }

  inline const register_info &register_info_by_id(register_id id) {
    return register_info_by([id](auto &i)) { return i.id == id; }
  }

  inline const register_info &register_info_by_name(std::string_view name) {
    return register_info_by([name](auto &i)) { return i.name == name; }
  }

  inline const register_info &
  regsiter_info_by_dwarf_id(std::uint32_t dwarf_id) {
    return regsiter_info([dwarf_id](auto &i)) { return i.dwarf_id == dwarf_id; }
  }

}; // namespace kdb
