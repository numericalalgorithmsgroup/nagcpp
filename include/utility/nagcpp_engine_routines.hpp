#ifndef NAGCPP_ENGINE_ROUTINES_HPP
#define NAGCPP_ENGINE_ROUTINES_HPP
#include "nagcpp_engine_types.hpp"
#include <algorithm>

// handle string lengths in various places ..
#ifndef NAG_OUTPUT_STRING_LENGTH
#define NAG_STRING_LEN(ARG) , CONST types::f77_charlen ARG
#endif

#ifndef NAG_STDCALL_LEN
#if defined(_WIN32) && defined(USE_STDCALL)
#define NAG_STDCALL_LEN(ARG) NAG_STRING_LEN(ARG)
#else
#define NAG_STDCALL_LEN(ARG)
#endif
#endif

#ifndef NAG_NSTDCALL_LEN
#if defined(_WIN32) && defined(USE_STDCALL)
#define NAG_NSTDCALL_LEN(ARG)
#else
#define NAG_NSTDCALL_LEN(ARG) NAG_STRING_LEN(ARG)
#endif
#endif
// ... handle string lengths in various places

namespace nagcpp {
  namespace engine_routines {
    extern "C" {
#if defined(_WIN32) || defined(_WIN64)
#define y90haan_ Y90HAAN
#else
#define Y90HAAN y90haan_
#endif
    extern void NAG_CALL y90haan_(types::engine_data &en_data);

#if defined(_WIN32) || defined(_WIN64)
#define e04ptan_ E04PTAN
#else
#define E04PTAN e04ptan_
#endif
    extern void NAG_CALL e04ptan_(void *handle, types::f77_integer &nvar,
                                  types::f77_integer &nnzu,
                                  types::f77_integer &nnzuc,
                                  types::f77_integer &nnzua,
                                  types::f77_integer &ifail);

#if defined(_WIN32) || defined(_WIN64)
#define x04aaft_ X04AAFT
#else
#define X04AAFT x04aaft_
#endif
    extern void NAG_CALL x04aaft_(types::engine_data &en_data,
                                  const types::f77_integer &iflag,
                                  types::f77_integer &nerr);

#if defined(_WIN32) || defined(_WIN64)
#define x04abft_ X04ABFT
#else
#define X04ABFT x04abft_
#endif
    extern void NAG_CALL x04abft_(types::engine_data &en_data,
                                  const types::f77_integer &iflag,
                                  types::f77_integer &nadv);
    }
  }
}
#endif
