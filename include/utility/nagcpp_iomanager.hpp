#ifndef NAGCPP_IOMANAGER_HPP
#define NAGCPP_IOMANAGER_HPP

#include "nagcpp_engine_routines.hpp"
#include "nagcpp_engine_types.hpp"
#include "nagcpp_error_handler.hpp"
#include <algorithm>
#include <ios>
#include <iostream>
#include <map>
#include <mutex>
#include <vector>

namespace nagcpp {
  namespace iomanager {
    class IOManagerBase {
    protected:
      static const types::f77_integer adv_unit_number = 6;
      static const types::f77_integer err_unit_number = 7;
      // unit number supplied to NAG routines must be in the range
      // min_unit_number <= unit no <= max_unit_number
      static const types::f77_integer min_unit_number = 11;
      // 100 is an engine restriction
      static const types::f77_integer max_unit_number = 100;

    private:
      static std::once_flag have_set_adv_unit;
      static std::once_flag have_set_err_unit;

    public:
      IOManagerBase() {
        std::call_once(have_set_adv_unit, set_adv_unit_in_engine);
        std::call_once(have_set_err_unit, set_err_unit_in_engine);
      }
      virtual ~IOManagerBase() {}
      virtual void print_rec(const types::f77_integer unit_number,
                             const std::string &rec) {
        std::cout << rec << std::endl;
      }
      virtual types::f77_integer read_rec(const types::f77_integer unit_number,
                                          std::string &rec,
                                          const types::f77_integer nchar = -1) {
        return 0;
      }

      // virtual dummy methods for methods defined in IOManager derived class ...
      // done so that they can be accessed via a pointer to the base class
      virtual types::f77_integer
        register_istream(std::istream &is_to_register) {
        return 0;
      }
      virtual types::f77_integer
        register_ostream(std::ostream &os_to_register) {
        return 0;
      }
      virtual void deregister_istream(types::f77_integer unit_number) {}
      virtual void deregister_ostream(types::f77_integer unit_number) {}
      virtual void deregister_istream(std::istream &is_to_deregister) {}
      virtual void deregister_ostream(std::ostream &os_to_deregister) {}
      virtual types::f77_integer
        unit_from_istream(std::istream &is_of_interest) {
        return 0;
      }
      virtual std::istream &istream_from_unit(types::f77_integer unit_number) {
        return std::cin;
      }
      virtual types::f77_integer
        unit_from_ostream(std::ostream &os_of_interest) {
        return 0;
      }
      virtual std::ostream &ostream_from_unit(types::f77_integer unit_number) {
        return std::cout;
      }
      virtual void
        register_to_advisory_message_unit(std::ostream &os_to_register) {}
      virtual void reset_advisory_message_unit(void) {}
      virtual void
        register_to_error_message_unit(std::ostream &os_to_register) {}
      virtual void reset_error_message_unit(void) {}
      // ... virtual dummy methods for methods defined in IOManager derived class

    private:
      static void set_adv_unit_in_engine(void) {
        types::engine_data en_data;
        engine_routines::y90haan_(en_data);
        types::f77_integer iflag = 1;
        types::f77_integer nadv = adv_unit_number;
        engine_routines::x04abft_(en_data, iflag, nadv);
      }
      static void set_err_unit_in_engine(void) {
        types::engine_data en_data;
        engine_routines::y90haan_(en_data);
        types::f77_integer iflag = 1;
        types::f77_integer nerr = err_unit_number;
        engine_routines::x04aaft_(en_data, iflag, nerr);
      }
    };

    // declare the statics again
    std::once_flag IOManagerBase::have_set_adv_unit;
    std::once_flag IOManagerBase::have_set_err_unit;
    const types::f77_integer IOManagerBase::adv_unit_number;
    const types::f77_integer IOManagerBase::err_unit_number;

    // main IOManager
    class IOManager : public IOManagerBase {
    private:
      std::map<types::f77_integer, std::basic_ostream<char> *> unit_store_o;
      std::map<types::f77_integer, std::basic_istream<char> *> unit_store_i;
      types::f77_integer max_used_o;
      types::f77_integer max_used_i;
      // input streams use unit numbers [min_unit_number_i, max_unit_number_i]
      // output streams use unit numbers [min_unit_number_o, max_unit_number_o]
      const types::f77_integer min_unit_number_i = min_unit_number;
      const types::f77_integer min_unit_number_o = max_unit_number / 2;
      const types::f77_integer max_unit_number_i = min_unit_number_o - 1;
      const types::f77_integer max_unit_number_o = max_unit_number;

    public:
      IOManager() : IOManagerBase() {
        max_used_o = min_unit_number_o - 1;
        max_used_i = min_unit_number_i - 1;
        initialise_advisory_message_unit();
        initialise_error_message_unit();
      }
      ~IOManager() {}
      types::f77_integer register_istream(std::istream &is_to_register) {
        // register an input stream for use
        return register_stream(is_to_register, unit_store_i, true, max_used_i,
                               min_unit_number_i, max_unit_number_i);
      }
      types::f77_integer register_ostream(std::ostream &os_to_register) {
        // register an output stream for use
        return register_stream(os_to_register, unit_store_o, false, max_used_o,
                               min_unit_number_o, max_unit_number_o);
      }
      void deregister_istream(types::f77_integer unit_number) {
        (void)deregister_stream(unit_number, unit_store_i);
        reset_standard_channels(unit_number);
      }
      void deregister_istream(std::istream &is_to_deregister) {
        types::f77_integer unit_number =
          deregister_stream(is_to_deregister, unit_store_i);
        reset_standard_channels(unit_number);
      }
      void deregister_ostream(types::f77_integer unit_number) {
        (void)deregister_stream(unit_number, unit_store_o);
      }
      void deregister_ostream(std::ostream &os_to_deregister) {
        (void)deregister_stream(os_to_deregister, unit_store_o);
      }
      types::f77_integer unit_from_istream(std::istream &is_of_interest) {
        return unit_from_stream(is_of_interest, unit_store_i);
      }
      std::istream &istream_from_unit(types::f77_integer unit_number) {
        auto iter = unit_store_i.find(unit_number);
        if (iter == unit_store_i.end()) {
          // no stream associated with unit_number - throw exception
          throw std::ios_base::failure("No registered istream associated with "
                                       "input unit number " +
                                       std::to_string(unit_number) + ".");
        }
        return *(iter->second);
      }
      types::f77_integer unit_from_ostream(std::ostream &os_of_interest) {
        return unit_from_stream(os_of_interest, unit_store_o);
      }
      std::ostream &ostream_from_unit(types::f77_integer unit_number) {
        auto iter = unit_store_o.find(unit_number);
        if (iter == unit_store_o.end()) {
          // no stream associated with unit_number - throw exception
          throw std::ios_base::failure("No registered ostream associated with "
                                       "output unit number " +
                                       std::to_string(unit_number) + ".");
        }
        return *(iter->second);
      }
      void register_to_advisory_message_unit(std::ostream &os_to_register) {
        // register an I stream to use for advisory messages
        auto iter = unit_store_o.find(adv_unit_number);
        if (iter == unit_store_o.end()) {
          initialise_advisory_message_unit(os_to_register);
        }
        iter->second = &os_to_register;
      }
      void reset_advisory_message_unit(void) {
        // reset the stream used for advisory messages (to std::cout)
        register_to_advisory_message_unit(std::cout);
      }
      void register_to_error_message_unit(std::ostream &os_to_register) {
        // register an I stream to use for error messages
        auto iter = unit_store_o.find(err_unit_number);
        if (iter == unit_store_o.end()) {
          initialise_error_message_unit(os_to_register);
        } else {
          iter->second = &os_to_register;
        }
      }
      void reset_error_message_unit(void) {
        // reset the stream used for error messages (to std::cerr)
        register_to_error_message_unit(std::cerr);
      }
      types::f77_integer read_rec(const types::f77_integer unit_number,
                                  std::string &rec,
                                  const types::f77_integer nchar = -1) {
        // read a record (line)
        auto iter = unit_store_i.find(unit_number);
        if (iter == unit_store_i.end()) {
          // no stream associated with unit_number - throw exception
          throw std::ios_base::failure("No registered istream associated with "
                                       "input unit number " +
                                       std::to_string(unit_number) + ".");
        } else {
          if (nchar < 0) {
            // read the whole line
            std::getline(*(iter->second), rec);
            return rec.size();
          } else {
            // read in the specified number of characters
            types::f77_integer anchar = 0;
            rec = "";
            for (types::f77_integer i = 0; i < nchar; ++i) {
              char ch[1];
              (iter->second)->read(ch, 1);
              if (*ch != '\n' && *ch != '\r') {
                rec += (*ch);
                ++anchar;
              } else if (*ch == '\r' && (iter->second)->peek() == '\n') {
                // treat "\r\n" as a single character
                --i;
              } else {
                // convert all line endings to a single \n
                // do not include in the number of characters read
                rec += '\n';
              }
            }
            return anchar;
          }
        }
      }
      void print_rec(const types::f77_integer unit_number,
                     const std::string &rec) {
        // print a record (line)
        auto iter = unit_store_o.find(unit_number);
        if (iter == unit_store_o.end()) {
          // no stream associated with unit_number - throw exception
          throw std::ios_base::failure("No registered ostream associated with "
                                       "output unit number " +
                                       std::to_string(unit_number) + ".");
        } else {
          *(iter->second) << rec << std::endl;
        }
      }

    private:
      void initialise_advisory_message_unit(std::ostream &os_to_register) {
        unit_store_o[adv_unit_number] = &os_to_register;
      }
      void initialise_advisory_message_unit(void) {
        initialise_advisory_message_unit(std::cout);
      }
      void initialise_error_message_unit(std::ostream &os_to_register) {
        unit_store_o[err_unit_number] = &os_to_register;
      }
      void initialise_error_message_unit(void) {
        initialise_error_message_unit(std::cerr);
      }
      void reset_standard_channels(types::f77_integer unit_number) {
        if (unit_number == adv_unit_number) {
          reset_advisory_message_unit();
        } else if (unit_number == err_unit_number) {
          reset_error_message_unit();
        }
      }
      template <typename IOST, typename MAPT>
      types::f77_integer
        register_stream(IOST &ios_to_register, MAPT &unit_store,
                        bool is_istream, types::f77_integer &max_registered,
                        const types::f77_integer min_unit_number_value,
                        const types::f77_integer max_unit_number_value) {
        // register an IO stream to a unit number
        // returns the unit number
        types::f77_integer to_use =
          unit_from_stream(ios_to_register, unit_store);
        if (to_use) {
          // the stream is already registered
          return to_use;
        }

        if (max_registered < max_unit_number_value) {
          max_registered++;
          to_use = max_registered;

        } else {
          // we have registered at least max_unit_store streams
          // find one that has been freed up
          std::vector<types::f77_integer> key_list;
          for (auto iter = unit_store.begin(); iter != unit_store.end();
               ++iter) {
            key_list.push_back(iter->first);
          }
          std::sort(key_list.begin(), key_list.end());
          to_use = -1;
          auto iter = key_list.begin();
          for (; iter != key_list.end() &&
                 ((*iter) == adv_unit_number || (*iter) == err_unit_number);
               ++iter)
            ;
          types::f77_integer pvalue = (*iter);
          for (++iter; iter != key_list.end(); ++iter) {
            if ((*iter) == adv_unit_number || (*iter) == err_unit_number) {
              continue;
            }
            if ((*iter) != pvalue + 1) {
              to_use = pvalue + 1;
              break;
            } else {
              pvalue = (*iter);
            }
          }
          if (to_use < min_unit_number_value ||
              to_use > max_unit_number_value) {
            // no spare slots available
            throw error_handler::ErrorException(
              "IOManager.register_stream",
              "All " +
                std::to_string(max_unit_number_value - min_unit_number_value +
                               1) +
                " unit numbers for " + ((is_istream) ? "input" : "output") +
                " streams are in use, you must deregister some before "
                "registering more.",
              error_handler::ErrorType::GeneralError,
              error_handler::IERR_IOMANAGER_TOO_MANY_UNIT_NUMBERS,
              error_handler::IERR_IOMANAGER_TOO_MANY_UNIT_NUMBERS, 0);
          }
        }

        unit_store[to_use] = &ios_to_register;
        return to_use;
      }
      template <typename IOST, typename MAPT>
      static types::f77_integer unit_from_stream(IOST &ios_of_interest,
                                                 MAPT &unit_store) {
        // returns the unit number associated with a stream
        // searches backwards - so will (usually) be the last added
        // copy of a stream if it has been added multiple times, however
        // this is not guaranteed
        // returns 0 if the stream is not registered
        types::f77_integer unit_number = 0;
        for (auto iter = unit_store.rbegin(); iter != unit_store.rend();
             ++iter) {
          if (iter->second == &ios_of_interest) {
            unit_number = iter->first;
            break;
          }
        }
        return unit_number;
      }
      template <typename MAPT>
      types::f77_integer deregister_stream(types::f77_integer unit_number,
                                           MAPT &unit_store) {
        // deregister a stream
        if (unit_number > 0) {
          unit_store.erase(unit_number);
        }
        return unit_number;
      }
      template <typename IOST, typename MAPT>
      types::f77_integer deregister_stream(IOST &ios_to_deregister,
                                           MAPT &unit_store) {
        // deregister a stream
        types::f77_integer unit_number =
          unit_from_stream(ios_to_deregister, unit_store);
        if (unit_number > 0) {
          unit_store.erase(unit_number);
        }
        return unit_number;
      }
    };

    // the global IO manager
    std::shared_ptr<IOManagerBase> GLOBAL_IOMANAGER =
      std::make_shared<IOManager>();
  }
}
#endif
