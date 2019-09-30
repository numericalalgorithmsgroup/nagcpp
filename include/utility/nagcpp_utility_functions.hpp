#ifndef NAGCPP_UTILITY_FUNCTIONS_HPP
#define NAGCPP_UTILITY_FUNCTIONS_HPP

#include <algorithm>
#include <cctype>
#include <sstream>
#include <string>

namespace nagcpp {
  namespace utility {
    std::string str_toupper(const std::string &s) {
      // return string s as upper case
      std::string ts = s;
      std::transform(ts.begin(), ts.end(), ts.begin(),
                     [](unsigned char c) -> unsigned char {
                       return static_cast<unsigned char>(std::toupper(c));
                     });
      return ts;
    }
    bool streq(const std::string &s1, const std::string &s2) {
      // return true if s1 == s2, ignoring case
      return (utility::str_toupper(s1).compare(utility::str_toupper(s2)) == 0);
    }
    bool streq(const std::string &s1, const std::string &s2,
               const std::size_t len) {
      // return true if the first len characters of s1 == first len characters
      // of s2 ignoring case
      return (utility::str_toupper(s1).compare(0, len, utility::str_toupper(s2),
                                               0, len) == 0);
    }
    std::string strip_namespace(const std::string &rname) {
      // return the routine name, rname, with any namespaces information removed
      std::size_t pos = rname.rfind("::");
      if (pos == std::string::npos) {
        return rname;
      } else {
        return rname.substr(pos + 2);
      }
    }
    bool rname_eq(const std::string &rname1, const std::string &rname2) {
      return streq(strip_namespace(rname1), strip_namespace(rname2));
    }
    std::string set_optstr(const std::string &opt) { return opt; }
    template <typename T>
    std::string set_optstr(const std::string &opt, const T value) {
      std::ostringstream strs;
      strs << opt << " = " << value;
      return strs.str();
    }

    // return true if a callback has been supplied, false otherwise
    template <typename V>
    inline bool callbackSupplied(V callback) {
      return true;
    }
    template <>
    inline bool callbackSupplied<std::nullptr_t>(std::nullptr_t callback) {
      return false;
    }
  }
}
#endif
