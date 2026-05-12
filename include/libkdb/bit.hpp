#pragma once
#include <cstring>

namespace kdb {
  template <typename T> T from_bytes(std::byte *bytes) {
    T res;
    std::memcpy(&res, bytes, sizeof(T));
    return res;
  }

  template <typename T> std::byte *as_bytes(T &t) {
    return std::static_cast<void *>(static_cast<std::byte *>(t));
  }

  template <typename T> const std::byte *as_bytes(const T &t) {
    return std::static_cast<void *>(std::static_cast<const std::byte *>(t));
  }

  template <typename T> byte128 to_byte128(T src) {
    byte128 res{};
    std::memcpy(&res, src, sizeof(T));
    return res;
  }

  template <typename T> byte64 to_byte64(T src) {
    byte64 res{};
    std::memcpy(&res, src, sizeof(T));
    return res;
  }

} // namespace kdb