#ifndef NAGCPP_UTILITY_COMM_HPP
#define NAGCPP_UTILITY_COMM_HPP

#include "utility/nagcpp_engine_types.hpp"
#include "utility/nagcpp_error_handler.hpp"

namespace nagcpp {
  namespace utility {
    class NoneCopyableComm {
      // class that holds handle based communication information
      // when there is no associated copy routine
    public:
      void *handle;
      bool initialized;

    public:
      NoneCopyableComm() : handle(nullptr), initialized(false) {}
      virtual ~NoneCopyableComm() {}
      NoneCopyableComm(void *handle_) : handle(handle_), initialized(false) {}
      NoneCopyableComm(const NoneCopyableComm &) = delete;
      NoneCopyableComm &operator=(const NoneCopyableComm &) = delete;
      bool check(void) const { return initialized; }
    };

    class CopyableComm {
    public:
      void *handle;
      double *rcomm;
      types::f77_integer lrcomm;
      types::f77_integer *icomm;
      types::f77_integer licomm;
      char *ccomm;
      types::f77_integer lccomm;
      types::f77_charlen ccomm_length;
      types::f77_integer *lcomm;
      types::f77_integer llcomm;
      double *zcomm;
      types::f77_integer lzcomm;

      double *rcomm2;
      types::f77_integer lrcomm2;

      types::f77_integer *icomm2;
      types::f77_integer licomm2;

      double srcomm;

      bool initialized;

    public:
      CopyableComm()
        : handle(nullptr), rcomm(nullptr), lrcomm(0), icomm(nullptr), licomm(0),
          ccomm(nullptr), lccomm(0), ccomm_length(0), lcomm(nullptr), llcomm(0),
          zcomm(nullptr), lzcomm(0), rcomm2(nullptr), lrcomm2(0),
          icomm2(nullptr), licomm2(0), srcomm(0), initialized(false) {}
      virtual ~CopyableComm() { deallocate(); }
      CopyableComm(const CopyableComm &from) : CopyableComm() {
        copyfrom(from);
      }
      CopyableComm &operator=(const CopyableComm &from) {
        copyfrom(from);
        return *this;
      }
      void deallocate() {
        if (rcomm) {
          delete[] rcomm;
          rcomm = nullptr;
        }
        lrcomm = 0;
        if (icomm) {
          delete[] icomm;
          icomm = nullptr;
        }
        licomm = 0;
        if (ccomm) {
          delete[] ccomm;
          ccomm = nullptr;
        }
        lccomm = 0;
        ccomm_length = 0;
        if (lcomm) {
          delete[] lcomm;
          lcomm = nullptr;
        }
        llcomm = 0;
        if (zcomm) {
          delete[] zcomm;
          zcomm = nullptr;
        }
        lzcomm = 0;
        if (rcomm2) {
          delete[] rcomm2;
          rcomm2 = nullptr;
        }
        licomm2 = 0;
        if (icomm2) {
          delete[] icomm2;
          rcomm2 = nullptr;
        }
        licomm2 = 0;

        initialized = false;
      }
      void allocate(error_handler::ErrorHandler &fail,
                    types::f77_integer lrcomm_, types::f77_integer licomm_ = 0,
                    types::f77_integer lccomm_ = 0,
                    types::f77_integer llcomm_ = 0,
                    types::f77_integer lzcomm_ = 0,
                    types::f77_integer lrcomm2_ = 0,
                    types::f77_integer licomm2_ = 0) {
        try {
          allocate(lrcomm_, licomm_, lccomm_, llcomm_, lzcomm_, lrcomm2_,
                   licomm2_);
        } catch (...) {
          fail.raise_error_allocation_failure();
        }
      }
      void allocate(types::f77_integer lrcomm_, types::f77_integer licomm_ = 0,
                    types::f77_integer lccomm_ = 0,
                    types::f77_integer llcomm_ = 0,
                    types::f77_integer lzcomm_ = 0,
                    types::f77_integer lrcomm2_ = 0,
                    types::f77_integer licomm2_ = 0) {
        deallocate();

        lrcomm = lrcomm_;
        licomm = licomm_;
        lccomm = lccomm_;
        llcomm = llcomm_;
        lzcomm = lzcomm_;
        lrcomm2 = lrcomm2_;
        licomm2 = licomm2_;

        if (lrcomm > 0) {
          rcomm = new double[lrcomm];
        }
        if (licomm > 0) {
          icomm = new types::f77_integer[licomm];
        }
        if (lccomm > 0) {
          ccomm = new char[lccomm];
          ccomm_length = 1;
        }
        if (llcomm > 0) {
          lcomm = new types::f77_integer[llcomm];
        }
        if (lzcomm > 0) {
          zcomm = new double[2 * lzcomm];
        }
        if (lrcomm2 > 0) {
          rcomm2 = new double[lrcomm2];
        }
        if (licomm2 > 0) {
          icomm2 = new types::f77_integer[licomm2];
        }
      }

      bool check(types::f77_integer lrcomm_ = 0, types::f77_integer licomm_ = 0,
                 types::f77_integer lccomm_ = 0, types::f77_integer llcomm_ = 0,
                 types::f77_integer lzcomm_ = 0,
                 types::f77_integer lrcomm2_ = 0,
                 types::f77_integer licomm2_ = 0) const {
        // partial check on a comm class
        // only checks that the wrapper itself will not cause an array
        // out of bounds error. The algorithmic code should do a more
        // comprehensive check on any communication arrays
        return (initialized && lrcomm >= lrcomm_ && licomm >= licomm_ &&
                lccomm >= lccomm_ && llcomm >= llcomm_ && lzcomm >= lzcomm_ &&
                lrcomm2 >= lrcomm2_ && licomm2 >= licomm2_);
      }

    private:
      void copyfrom(const CopyableComm &comm) {
        deallocate();
        allocate(comm.lrcomm, comm.licomm, comm.lccomm, comm.llcomm,
                 comm.lzcomm, comm.lrcomm2, comm.licomm2);
        for (types::f77_integer i = 0; i < lrcomm; i++) {
          rcomm[i] = comm.rcomm[i];
        }
        for (types::f77_integer i = 0; i < licomm; i++) {
          icomm[i] = comm.icomm[i];
        }
        for (types::f77_integer i = 0; i < lccomm; i++) {
          ccomm[i] = comm.ccomm[i];
        }
        ccomm_length = comm.ccomm_length;
        for (types::f77_integer i = 0; i < llcomm; i++) {
          lcomm[i] = comm.lcomm[i];
        }
        for (types::f77_integer i = 0; i < 2 * lzcomm; i++) {
          zcomm[i] = comm.zcomm[i];
        }
        for (types::f77_integer i = 0; i < lrcomm2; i++) {
          rcomm2[i] = comm.rcomm2[i];
        }
        for (types::f77_integer i = 0; i < licomm2; i++) {
          icomm2[i] = comm.icomm2[i];
        }
      }
    };
  }
}

#endif
