#ifndef NAG_MY_VECTOR_H
#define NAG_MY_VECTOR_H
// example of a very simple vector class ...
// the data classes can be anything, as long as they
// have some standard methods
#include <vector>

template <typename DT>
class MyVector {
private:
  size_t n1;
  DT *raw_data;

public:
  MyVector(void) : n1(0), raw_data(nullptr) {}
  MyVector(const size_t n1_) : MyVector() {
    // for cases where we need to pre-allocate an array
    resize(n1_);
  }
  MyVector(const size_t n1_, const std::vector<DT> &raw_data_) : MyVector() {
    resize(n1_);

    // as it is clearer in the example to display the hardcoded data by rows
    // and the recommendation for calling the libraries by column we are going
    // to copy the data (and transpose as we are doing so), rather than work
    // directly with the data as stored in raw_data
    for (size_t i = 0; i < n1; ++i) {
      (*this)(i) = raw_data_[i];
    }
  }
  ~MyVector(void) {
    if (raw_data) {
      delete[] raw_data;
    }
  }

  // disable the default copy constructor and operator as we are
  // using raw pointers and have not implemented them
  MyVector &operator=(const MyVector &) = delete;
  MyVector(const MyVector &) = delete;

  // resize the vector
  // this method is called by a library routine in two places
  //  a) It is called on all output arrays prior to calling the engine routine
  //  b) It is called on some output arrays after calling the engine routine.
  //     resize is called after the engine routine if only part of an output
  //     array is populated, in which case the resize must be done preserving
  //     the contents (if you don't resize in this situation then only the
  //     first elements of the vector will be populated).
  // it is recommended that at least (a) is implemented, otherwise you would
  // need to preallocate any memory used before callin the library routine
  void resize(const size_t n1_) {
    if (raw_data) {
      DT *ptmp = new DT[n1_];
      // no bounds checks are done, so make sure we don't go out of bounds
      size_t cn1 = std::min(n1, n1_);
      size_t i;
      for (i = 0; i < cn1; ++i) {
        ptmp[i] = (*this)(i);
      }
      // initialise any oversizes with zeros
      for (; i < n1_; ++i) {
        ptmp[i] = 0;
      }
      delete[] raw_data;
      raw_data = ptmp;

    } else {
      raw_data = new DT[n1_];
    }
    n1 = n1_;
  }

  // number of elements
  // the return type is anything that can be statically cast
  // into a nagcpp:types::f77_integer
  size_t size(void) const { return n1; }

  // pointer to the raw data
  // required method for all data classes passed to a
  // library routine
  DT *data(void) { return raw_data; }
  DT *data(void) const { return raw_data; }

  // not required, but included as it keeps notation in examples
  // consistent with the 2D case
  template <typename IT1>
  DT &operator()(const IT1 i) {
    return raw_data[i];
  }
  template <typename IT1>
  DT &operator()(const IT1 i) const {
    return raw_data[i];
  }
};
// ... example of a very simple vector class
#endif
