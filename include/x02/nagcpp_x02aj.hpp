// Header for nagcpp::machine::precision (x02aj)

// Copyright 2023, Numerical Algorithms Group Ltd, Oxford, UK.
// Generated by cpp-ft-wrapper.xsl
// Version 29.0.0.0
#ifndef NAGCPP_X02AJ_HPP
#define NAGCPP_X02AJ_HPP

#include "utility/nagcpp_consts.hpp"
#include "utility/nagcpp_engine_routines.hpp"
#include "utility/nagcpp_engine_types.hpp"

namespace nagcpp {
  namespace machine {
    // precision (x02aj)
    // The machine precision.
    // machine::precision (x02aj) returns epsilon, the value machine precision.
    // returns: double, scalar
    //   epsilon, the value machine precision

    extern "C" {
#if defined(_WIN32) && defined(USE_STDCALL)
#define x02ajft_(en_data, eps) X02AJFT(en_data, eps)
#elif defined(_WIN32) || defined(_WIN64)
#define x02ajft_ X02AJFT
#else
#define X02AJFT x02ajft_
#endif
    extern void NAG_CALL X02AJFT(types::engine_data &en_data, double &eps);
    }

    double precision(void) {
      types::engine_data en_data;
      engine_routines::y90haan_(en_data);
      en_data.allocate_workspace = constants::NAG_ED_YES;

      double local_eps;

      x02ajft_(en_data, local_eps);

      return local_eps;
    }
  }
}
#define x02aj machine::precision
#endif
