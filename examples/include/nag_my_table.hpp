#ifndef NAG_MY_TABLE_H
#define NAG_MY_TABLE_H
// example of a very simple table class ...
// (here we are defining a table as a 3D array)
// the data classes can be anything, as long as they
// have some standard methods
#include <vector>

template <typename DT>
class MyTable {
private:
  size_t n1;
  size_t n2;
  size_t n3;
  DT *raw_data;

public:
  MyTable(void) : n1(0), n2(0), n3(0), raw_data(nullptr) {}
  MyTable(size_t n1_, size_t n2_, size_t n3_) : MyTable() {
    // for cases where we need to pre-allocate an array
    resize(n1_, n2_, n3_);
  }
  MyTable(size_t n1_, size_t n2_, size_t n3_, const std::vector<DT> &raw_data_)
    : MyTable() {
    resize(n1_, n2_, n3_);

    // as it is clearer in the example to display the hardcoded data as a series
    // of matrices (one for each table), with the matrices displayed by rows
    // that is the way we assume the data is stored in raw_data (NB: this is
    // neither row major or column major - it is a mixture of both)

    // the recommendation for calling the library is by column
    // loop over tables
    for (size_t k = 0, p = 0; k < n3; ++k) {
      // loop over matrices within table, with the matrices
      // being stored in row major order
      for (size_t i = 0; i < n1; ++i) {
        for (size_t j = 0; j < n2; ++j, ++p) {
          (*this)(i, j, k) = raw_data_[p];
        }
      }
    }
  }
  ~MyTable(void) {
    if (raw_data) {
      delete[] raw_data;
    }
  }

  // disable the default copy constructor and operator as we are
  // using raw pointers and have not implemented them
  MyTable &operator=(const MyTable &) = delete;
  MyTable(const MyTable &) = delete;

  // resize the table
  // this method is called by a library routine in two places
  //  a) It is called on all output arrays prior to calling the engine routine
  //  b) It is called on some output arrays after calling the engine routine.
  //     resize is called after the engine routine if only part of an output
  //     array is populated, in which case the resize must be done preserving
  //     the contents (if you don't resize in this situation then only the top
  //     left hand corner of the table will be populated for the first layers).
  // it is recommended that at least (a) is implemented, otherwise you would
  // need to preallocate any memory used before callin the library routine
  void resize(size_t n1_, size_t n2_, size_t n3_) {
    if (raw_data) {
      DT *ptmp = new DT[n1_ * n2_ * n3_];
      // no bounds checks are done, so make sure we don't go out of bounds
      size_t cn1 = std::min(n1, n1_);
      size_t cn2 = std::min(n2, n2_);
      size_t cn3 = std::min(n3, n3_);

      size_t i, j, k, p;
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
        for (; j < n2_; ++j) {
          for (i = 0; i < n1_; ++i, ++p) {
            ptmp[p] = 0;
          }
        }
      }
      // initialise any table oversizes with zeros
      for (; k < n3_; ++k) {
        for (j = 0; j < n2_; ++j) {
          for (i = 0; i < n1_; ++i, ++p) {
            ptmp[p] = 0;
          }
        }
      }
      delete[] raw_data;
      raw_data = ptmp;

    } else {
      raw_data = new DT[n1_ * n2_ * n3_];
    }
    n1 = n1_;
    n2 = n2_;
    n3 = n3_;
  }
  // return true if the raw data is stored in column major order
  // if this method is not supplied then the routine will
  // assume column major order
  bool is_col_major(void) const { return true; }

  // number of rows (size1), columns (size2) and tables (size3)
  // these are required methods for a data class that will
  // hold a 2D array (or table)
  // the return type is anything that can be statically cast
  // into a nagcpp:types::f77_integer
  size_t size1(void) const { return n1; }
  size_t size2(void) const { return n2; }
  size_t size3(void) const { return n3; }

  // pointer to the raw data
  // required method for all data classes passed to a
  // library routine
  DT *data(void) { return raw_data; }
  DT *data(void) const { return raw_data; }

  // not required, but makes the example easier to read
  // allows element A_ijk of the table to be accessed using
  // a(i-1, j-1, k-1)
  template <typename IT1, typename IT2, typename IT3>
  DT &operator()(const IT1 i, const IT2 j, const IT3 k) {
    return raw_data[array_position(i, j, k)];
  }
  template <typename IT1, typename IT2, typename IT3>
  DT &operator()(const IT1 i, const IT2 j, const IT3 k) const {
    return raw_data[array_position(i, j, k)];
  }

private:
  template <typename IT1, typename IT2, typename IT3>
  size_t array_position(const IT1 i, const IT2 j, const IT3 k) const {
    // this is the layout for column major order
    // if using row major, the layout would be
    // (i * n2 * n3 + j * n3 + k)
    size_t n12 = n1 * n2;
    return (k * n12 + j * n1 + i);
  }
};
// ... example of a very simple table class
#endif
