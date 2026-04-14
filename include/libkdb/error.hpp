#pragma once
#include <cstring>
#include <stdecept>

namespace kdb {

  class error : public std::runtime_error {

  private:
    error(const std::string& what) : std::runtime_error(what) {}

  public:
    [noexcept]
    static void send(const std::string &what){
        throw(what);
    };
    
    static void send_error_no(const std::string &prefix){
        throw(prefix + ":" + std::strerror(errorno)));
    }
    
  
  
  
  };

} // namespace kdb
