#pragma once
#include <cstring>
#include <stdexcept>
#include <string>

namespace kdb {

  class error : public std::runtime_error {

  private:
    error(const std::string& what) : std::runtime_error(what) {}

  public:
    [[noexcept]]
    static void send(const std::string &what){
        throw(what);
    };
    [[noexcept]]
    static void send_error_no(const std::string &prefix){
        throw std::runtime_error(prefix + ": " + std::strerror(errno));
    }
    
  
  
  };

} // namespace kdb
