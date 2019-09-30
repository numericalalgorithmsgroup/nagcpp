#ifndef NAG_MY_MATRIX_H
#define NAG_MY_MATRIX_H
// example of a very simple matrix class ...
// the data classes can be anything, as long as they
// have some standard methods
#include <vector>

template <typename DT>
class MyMatrix {
private:
  size_t n1;
  size_t n2;
  DT *raw_data;

public:
  MyMatrix(void) : n1(0), n2(0), raw_data(nullptr) {}
  MyMatrix(const size_t n1_, const size_t n2_) : MyMatrix() {
    // for cases where we need to pre-allocate an array
    resize(n1_, n2_);
  }
  MyMatrix(const size_t n1_, const size_t n2_, const std::vector<DT> &raw_data_)
    : MyMatrix() {
    resize(n1_, n2_);

    // as it is clearer in the example to display the hardcoded data by rows
    // and the recommendation for calling the library is by column we are going
    // to copy the data (and transpose as we are doing so), rather than work
    // directly with the data as stored in raw_data
    for (size_t i = 0, p = 0; i < n1; ++i) {
      for (size_t j = 0; j < n2; ++j, ++p) {
        (*this)(i, j) = raw_data_[p];
      }
    }
  }
  ~MyMatrix(void) {
    if (raw_data) {
      delete[] raw_data;
    }
  }

  // disable the default copy constructor and operator as we are
  // using raw pointers and have not implemented them
  MyMatrix &operator=(const MyMatrix &) = delete;
  MyMatrix(const MyMatrix &) = delete;

  // resize the matrix
  // this method is called by a library routine in two places
  //  a) It is called on all output arrays prior to calling the engine routine
  //  b) It is called on some output arrays after calling the engine routine.
  //     resize is called after the engine routine if only part of an output
  //     array is populated, in which case the resize must be done preserving
  //     the contents (if you don't resize in this situation then only the top
  //     left hand corner of the array will be populated).
  // it is recommended that at least (a) is implemented, otherwise you would
  // need to preallocate any memory used before calling the library routine
  void resize(const size_t n1_, const size_t n2_) {
    if (raw_data) {
      DT *ptmp = new DT[n1_ * n2_];

      // no bounds checks are done, so make sure we don't go out of bounds
      size_t cn1 = std::min(n1, n1_);
      size_t cn2 = std::min(n2, n2_);

      size_t i, j, p;
      for (j = 0, p = 0; j < cn2; ++j) {
        for (i = 0; i < cn1; ++i, ++p) {
          ptmp[p] = (*this)(i, j);
        }
        // initialise any row oversizes with zeros
        for (; i < n1_; ++i, ++p) {
          ptmp[p] = 0;
        }
      }
      // initialise any column oversizes with zeros
      for (; j < n2_; ++j) {
        for (i = 0; i < n1_; ++i, ++p) {
          ptmp[p] = 0;
        }
      }
      delete[] raw_data;
      raw_data = ptmp;

    } else {
      raw_data = new DT[n1_ * n2_];
    }
    n1 = n1_;
    n2 = n2_;
  }
  // return true if the raw data is stored in column major order
  // if this method is not supplied then the routine will
  // assume column major order
  bool is_col_major(void) const { return true; }

  // number of rows (size1) and columns (size2)
  // these are required methods for a data class that will
  // hold a 2D array (or matrix)
  // the return type is anything that can be statically cast
  // into a nagcpp:types::f77_integer
  size_t size1(void) const { return n1; }
  size_t size2(void) const { return n2; }

  // pointer to the raw data
  // required method for all data classes passed to a
  // library routine
  DT *data(void) { return raw_data; }
  DT *data(void) const { return raw_data; }

  // not required, but makes the example easier to read
  // allows element A_ij of the matrix to be accessed using
  // a(i-1, j-1)
  template <typename IT1, typename IT2>
  DT &operator()(const IT1 i, const IT2 j) {
    return raw_data[array_position(i, j)];
  }
  template <typename IT1, typename IT2>
  DT &operator()(const IT1 i, const IT2 j) const {
    return raw_data[array_position(i, j)];
  }

private:
  template <typename IT1, typename IT2>
  size_t array_position(const IT1 i, const IT2 j) const {
    // this is the layout for column major order
    // if using row major, the layout would be
    // (i * n2 + j)
    return (j * n1 + i);
  }
};
// ... example of a simple data class
#endif
