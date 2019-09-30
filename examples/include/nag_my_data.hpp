#ifndef NAG_MY_DATA_H
#define NAG_MY_DATA_H
// example of a very simple data class ...
// (this class can be used for 1, 2 or 3D arrays)
// the data classes can be anything, as long as they
// have some standard methods
#include <vector>

template <typename DT>
class MyData {
private:
  size_t n1;
  size_t n2;
  size_t n3;
  size_t ndim;
  DT *raw_data;

public:
  MyData(void) : n1(0), n2(0), n3(0), raw_data(nullptr) {}
  // for cases where we need to pre-allocate an array ...
  MyData(const size_t n1_) : MyData() { resize(n1_); }
  MyData(const size_t n1_, const size_t n2_) : MyData() { resize(n1_, n2_); }
  MyData(const size_t n1_, const size_t n2_, const size_t n3_) : MyData() {
    resize(n1_, n2_, n3_);
  }
  // ... for cases where we need to pre-allocate an array
  MyData(const size_t n1_, const std::vector<DT> &raw_data_) : MyData() {
    resize(n1_);
    populate(raw_data_);
  }
  MyData(const size_t n1_, const size_t n2_, const std::vector<DT> &raw_data_)
    : MyData() {
    resize(n1_, n2_);
    populate(raw_data_);
  }
  MyData(const size_t n1_, const size_t n2_, const size_t n3_,
         const std::vector<DT> &raw_data_)
    : MyData() {
    resize(n1_, n2_, n3_);
    populate(raw_data_);
  }

  ~MyData(void) {
    if (raw_data) {
      delete[] raw_data;
    }
  }

  // disable the default copy constructor and operator as we are
  // using raw pointers and have not implemented them
  MyData &operator=(const MyData &) = delete;
  MyData(const MyData &) = delete;

  // resize the data
  // this method is called by a library routine in two places
  //  a) It is called on all output arrays prior to calling the engine routine
  //  b) It is called on some output arrays after calling the engine routine.
  //     resize is called after the engine routine if only part of an output
  //     array is populated, in which case the resize must be done preserving
  //     the contents (if you don't resize in this situation then only the top
  //     left hand corner of the data will be populated for the first layers).
  // it is recommended that at least (a) is implemented, otherwise you would
  // need to preallocate any memory used before callin the library routine
  void resize(const size_t n1_) {
    ndim = 1;
    resize_this(n1_, 1, 1);
  }
  void resize(const size_t n1_, const size_t n2_) {
    ndim = 2;
    resize_this(n1_, n2_, 1);
  }
  void resize(const size_t n1_, const size_t n2_, const size_t n3_) {
    ndim = 3;
    resize_this(n1_, n2_, n3_);
  }

  // return true if the raw data is stored in column major order
  // if this method is not supplied then the routine will
  // assume column major order
  bool is_col_major(void) const { return true; }

  // number of rows (size1) and columns (size2)
  // these are required methods for a data class that will
  // hold a 2D array (or data)
  // the return type is anything that can be statically cast
  // into a nagcpp:types::f77_integer
  size_t size1(void) const { return n1; }
  size_t size2(void) const { return n2; }
  size_t size3(void) const { return n3; }
  size_t ndims(void) const { return ndim; }

  // pointer to the raw data
  // required method for all data classes passed to a
  // library routine
  DT *data(void) { return raw_data; }
  DT *data(void) const { return raw_data; }

  // not required, but makes the example easier to read
  // allows element A_ijk of the data to be accessed using
  // a(i-1, j-1, k-1)
  template <typename IT1>
  inline DT &operator()(const IT1 i) {
    return raw_data[array_position(i, 0, 0)];
  }
  template <typename IT1, typename IT2>
  inline DT &operator()(const IT1 i, const IT2 j) {
    return raw_data[array_position(i, j, 0)];
  }
  template <typename IT1, typename IT2, typename IT3>
  inline DT &operator()(const IT1 i, const IT2 j, const IT3 k) {
    return raw_data[array_position(i, j, k)];
  }
  template <typename IT1>
  inline DT &operator()(const IT1 i) const {
    return raw_data[array_position(i, 0, 0)];
  }
  template <typename IT1, typename IT2>
  inline DT &operator()(const IT1 i, const IT2 j) const {
    return raw_data[array_position(i, j, 0)];
  }
  template <typename IT1, typename IT2, typename IT3>
  inline DT &operator()(const IT1 i, const IT2 j, const IT3 k) const {
    return raw_data[array_position(i, j, k)];
  }

private:
  template <typename IT1, typename IT2, typename IT3>
  size_t array_position(const IT1 i, const IT2 j, const IT3 k) const {
    // this is the layout for column major order
    // if using row major, the layout would be
    // (i * un2 * un3) + j * n3 + k)
    size_t un2 = (ndim > 1) ? n2 : 1;
    size_t n12 = n1 * un2;
    return (k * n12 + j * n1 + i);
  }

  void populate(const std::vector<DT> &raw_data_) {
    // as it is clearer in the example to display the hardcoded data as a series
    // of matrices (one for each table), with the matrices displayed by rows
    // that is the way we assume the data is stored in raw_data (NB: this is
    // neither row major or column major - it is a mixture of both)

    // the recommendation for calling the library is by column
    // loop over tables
    size_t un2 = (ndim > 1) ? n2 : 1;
    size_t un3 = (ndim > 2) ? n3 : 1;
    for (size_t k = 0, p = 0; k < un3; ++k) {
      for (size_t i = 0; i < n1; ++i) {
        for (size_t j = 0; j < un2; ++j, ++p) {
          (*this)(i, j, k) = raw_data_[p];
        }
      }
    }
  }

  void resize_this(size_t n1_, size_t n2_, size_t n3_) {
    size_t un2 = (ndim > 1) ? n2_ : 1;
    size_t un3 = (ndim > 2) ? n3_ : 1;
    if (raw_data) {
      DT *ptmp = new DT[n1_ * un2 * un3];
      // no bounds checks are done, so make sure we don't go out of bounds
      size_t cn1 = std::min(n1, n1_);
      size_t cn2 = (ndim > 1) ? std::min(n2, un2) : 1;
      size_t cn3 = (ndim > 2) ? std::min(n3, un3) : 1;
      size_t k, i, j, p;
      for (k = 0, p = 0; k < cn3; ++k) {
        for (j = 0; j < cn2; ++j) {
          for (i = 0; i < cn1; ++i, ++p) {
            ptmp[p] = (*this)(i, j, k);
          }
          // initialise any row oversizes with zeros
          for (; i < n1_; ++i, ++p) {
            ptmp[p] = 0;
          }
        }
        // initialise any column oversizes with zeros
        for (; j < un2; ++j) {
          for (i = 0; i < n1_; ++i, ++p) {
            ptmp[p] = 0;
          }
        }
      }
      // initialise any table oversizes with zeros
      for (; k < un3; ++k) {
        for (j = 0; j < un2; ++j) {
          for (i = 0; i < n1_; ++i, ++p) {
            ptmp[p] = 0;
          }
        }
      }
      delete[] raw_data;
      raw_data = ptmp;

    } else {
      raw_data = new DT[n1_ * un2 * un3];
    }
    n1 = n1_;
    if (ndim > 1) {
      n2 = n2_;
    }
    if (ndim > 2) {
      n3 = n3_;
    }
  }
};
// ... example of a very simple data class
#endif
