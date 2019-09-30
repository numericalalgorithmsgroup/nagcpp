#ifndef NAGCPP_UTILITY_OPTIONAL_HPP
#define NAGCPP_UTILITY_OPTIONAL_HPP

#include "nagcpp_error_handler.hpp"
#include "nagcpp_iomanager.hpp"

namespace nagcpp {
  namespace utility {
    enum IsSet { Yes, No, Default };
    class Optional {
    public:
      error_handler::ErrorHandler fail;
      std::shared_ptr<iomanager::IOManagerBase> iomanager;
      bool default_to_col_major;
      Optional()
        : fail(error_handler::GLOBAL_ERROR_HANDLER_CONTROL),
          iomanager(iomanager::GLOBAL_IOMANAGER), default_to_col_major(true) {}
      virtual ~Optional() {}
    };
  }
}
#endif
