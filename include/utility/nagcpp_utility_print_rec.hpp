#ifndef NAGCPP_UTILITY_PRINT_REC_HPP
#define NAGCPP_UTILITY_PRINT_REC_HPP

#include "nagcpp_engine_routines.hpp"
#include "nagcpp_engine_types.hpp"
#include "nagcpp_error_handler.hpp"
#include "nagcpp_iomanager.hpp"
#include <iostream>

namespace nagcpp {
  namespace utility {

#ifndef NAG_PRINT_RECH
#define NAG_PRINT_RECH                                                      \
  void(NAG_CALL * print_rech)(void *print_rec, types::engine_data &en_data, \
                              CONST types::f77_integer &nout,               \
                              CONST char *rec NAG_STDCALL_LEN(length_rec),  \
                              types::f77_integer &ierr NAG_NSTDCALL_LEN(length_rec))
#endif

    void NAG_CALL
      print_rech(void *print_rec, types::engine_data &en_data,
                 CONST types::f77_integer &nout,
                 CONST char *rec NAG_STDCALL_LEN(length_rec),
                 types::f77_integer &ierr NAG_NSTDCALL_LEN(length_rec)) {
      error_handler::ExceptionPointer *ep =
        static_cast<error_handler::ExceptionPointer *>(en_data.wrapptr1);
      std::string this_line(rec, length_rec);
      std::shared_ptr<iomanager::IOManagerBase> *iomanager =
        static_cast<std::shared_ptr<iomanager::IOManagerBase> *>(print_rec);
      ierr = 0;
      try {
        (*iomanager)->print_rec(nout, this_line);
      } catch (...) {
        // callback threw an exception
        en_data.hlperr = error_handler::HLPERR_PRINT_REC_EXCEPTION;
        ep->eptr = std::current_exception();
      }
    }
  }
}

#endif

/*
// #ifndef NAG_READ_RECH
// #define NAG_READ_RECH \
//   void(NAG_CALL * read_rech)( \
//     NAG_READ_REC, types::engine_data REFPTR, CONST types::f77_integer REFPTR,

//     char *,STDCALLLEN, char *,STDCALLLEN, \
//     types::f77_integer REFPTR, NSTDCALLLEN, NSTDCALLLEN)
// #endif

// #ifndef NAG_NONADV_READ_RECH
// #define NAG_NONADV_READ_RECH                           \
//   void(NAG_CALL * nonadv_read_rech)(                   \
//     NAG_NONADV_READ_REC, types::engine_data REFPTR,    \
//     CONST types::f77_integer REFPTR, char *,STDCALLLEN, \
//     types::f77_integer REFPTR, types::f77_integer REFPTR, NSTDCALLLEN)
// #endif

//     extern void NAG_CALL x04bazth(void *print_rec,
//                                   types::engine_data REFPTR en_data,
//                                   CONST types::f77_integer REFPTR nout,
//                                   CONST char *rec
// #if defined(_WIN32) && defined(USE_STDCALL)
//                                   ,
//                                   CONST types::f77_charlen length_rec
// #endif
//                                   ,
//                                   types::f77_integer REFPTR ierr
// #if !defined(_WIN32) || !defined(USE_STDCALL)
//                                   ,
//                                   CONST types::f77_charlen length_rec
// #endif
//     );
*/
