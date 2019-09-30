#ifndef NAGCPP_ENGINE_TYPES_HPPS
#define NAGCPP_ENGINE_TYPES_HPPS

#ifdef NAG_OLD_SCHOOL
#include "nag_engine_defs.h"
#else
#include "nag_basic_types.h"
#endif

#ifdef NAG_ENGINE_DATA
#define REDEFINE_NAG_ENGINE_DATA
#undef NAG_ENGINE_DATA
#endif

namespace nagcpp {
  namespace types {
#include "nag_engine_data.h"
    typedef Integer f77_integer;
    typedef Charlen f77_charlen;
    typedef logical f77_logical;
    typedef f77_integer size_type;
    typedef int c_int;
  }
}

#ifndef REDEFINE_NAG_ENGINE_DATA
#undef NAG_ENGINE_DATA
#endif
#undef REDEFINE_NAG_ENGINE_DATA

#endif
