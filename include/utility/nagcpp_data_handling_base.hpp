#ifndef NAGCPP_DATA_HANDLING_BASE_HPP
#define NAGCPP_DATA_HANDLING_BASE_HPP

#include "nagcpp_consts.hpp"
#include "nagcpp_data_handling_array_info.hpp"
#include "nagcpp_engine_types.hpp"
#include "nagcpp_error_handler.hpp"
#include <type_traits>

namespace nagcpp {
  namespace data_handling {
    // enum used only for specializing transformation templates
    enum ArgIntent { IntentIN, IntentOUT, IntentINOUT };

    // test value of the INOUT enum ...
    template <enum ArgIntent inout>
    struct is_in : public std::false_type {};
    template <>
    struct is_in<IntentIN> : public std::true_type {};
    template <enum ArgIntent inout>
    struct is_out : public std::false_type {};
    template <>
    struct is_out<IntentOUT> : public std::true_type {};
    template <enum ArgIntent inout>
    struct is_inout : public std::false_type {};
    template <>
    struct is_inout<IntentINOUT> : public std::true_type {};
    // ... test value of the INOUT enum

    // if inout = data_handling::IntentIN, then add const to RT ...
    template <typename RT, enum ArgIntent inout>
    struct add_const_if_in {
      typedef RT type;
    };
    template <typename RT>
    struct add_const_if_in<RT, IntentIN> {
      typedef const RT type;
    };
    // ... if inout = data_handling::IntentIN, then add const to RT

    // convert boolean flag indicating column major storage
    // order to numeric value used in engine
    types::f77_integer set_sorder(bool is_col_major) {
      return ((is_col_major) ? constants::NAG_ED_COL_MAJOR
                             : constants::NAG_ED_ROW_MAJOR);
    }
    bool set_is_col_major(types::f77_integer sorder) {
      return (sorder == constants::NAG_ED_COL_MAJOR) ? true : false;
    }

    // base class used when converting user supplied data
    // types into something that can be used in the wrappers
    template <typename RT, enum ArgIntent inout>
    class BaseRawData {
      using CRT = typename add_const_if_in<RT, inout>::type;
      public : CRT * data;

      protected : array_info<size_t>
        ndims;
      array_info<size_t>
        size1;
      array_info<size_t>
        size2;
      array_info<size_t>
        size3;
      array_info<bool>
        is_col_major;
      bool col_major_is_default;

      bool allocated;
      array_info<size_t>
        nelements;
      RT * ldata;

      protected : BaseRawData() : data(nullptr),
      ndims(0),
      size1(0),
      size2(0),
      size3(0),
      col_major_is_default(true),
      allocated(false),
      nelements(0),
      ldata(nullptr){}

      virtual ~BaseRawData(){deallocate();}

    // disable the copy constructor and operator as we are
    // using raw pointers and have not implemented them
    BaseRawData &operator=(const BaseRawData &) = delete;
    BaseRawData(const BaseRawData &) = delete;

    // copy data back from BaseRawData to array_container
    template <typename AC>
    void copy_back(AC &&array_container) {
      throw error_handler::NotImplementedException("copy_back method");
    }

    // copy data back and resize ...
    template <typename AC>
    void copy_back(AC &&array_container, types::f77_integer size1_) {
      throw error_handler::NotImplementedException("copy_back and resize "
                                                   "method: 1 dimension");
    }
    template <typename AC>
    void copy_back(AC &&array_container, types::f77_integer size1_,
                   types::f77_integer size2_) {
      throw error_handler::NotImplementedException("copy_back and resize "
                                                   "method: 2 dimension");
    }
    template <typename AC>
    void copy_back(AC &&array_container, types::f77_integer size1_,
                   types::f77_integer size2_, types::f77_integer size3_) {
      throw error_handler::NotImplementedException("copy_back and resize "
                                                   "method: 3 dimension");
    }
    // ... copy data back and resize

    // get data from array_container into BaseRawData
    template <typename AC>
    void get_data(AC &&array_container) {
      throw error_handler::NotImplementedException("get_data method");
    }

    // resize the array_container whose contents are held BaseRawData ...
    template <typename AC>
    void resize(AC &&array_container, types::f77_integer size1_) {
      throw error_handler::NotImplementedException("resize method: 1 "
                                                   "dimension");
    }
    template <typename AC>
    void resize(AC &&array_container, types::f77_integer size1_,
                types::f77_integer size2_) {
      throw error_handler::NotImplementedException("resize method: 2 "
                                                   "dimensions");
    }
    template <typename AC>
    void resize(AC &&array_container, types::f77_integer size1_,
                types::f77_integer size2_, types::f77_integer size3_) {
      throw error_handler::NotImplementedException("resize method: 3 "
                                                   "dimensions");
    }
    // ... resize the array_container whose contents are held BaseRawData

    void set_ndims(void) {
      if (size3.set) {
        ndims = 3;
      } else if (size2.set) {
        ndims = 2;
      } else if (size1.set) {
        ndims = 1;
      }
    }

    void allocate(void) {
      deallocate();
      if (nelements.value > 0) {
        allocated = true;
        ldata = new RT[nelements.value];
      }
      data = ldata;
    }

  private:
    void deallocate(void) {
      if (allocated) {
        delete[] ldata;
        allocated = false;
        ldata = nullptr;
      }
      data = nullptr;
    }

  public:
    // allow for local arrays in wrappers ...
    void allocate_local(types::f77_integer size1_) {
      ndims = 1;
      size1 = size1_;
      nelements = std::max(static_cast<types::f77_integer>(0), size1_);
      allocate();
    }
    void allocate_local(types::f77_integer size1_, types::f77_integer size2_) {
      ndims = 2;
      size1 = size1_;
      size2 = size2_;
      nelements = std::max(static_cast<types::f77_integer>(0), size1_) *
                  std::max(static_cast<types::f77_integer>(0), size2_);
      allocate();
    }
    void allocate_local(types::f77_integer size1_, types::f77_integer size2_,
                        types::f77_integer size3_) {
      ndims = 3;
      size1 = size1_;
      size2 = size2_;
      size3 = size3_;
      nelements = std::max(static_cast<types::f77_integer>(0), size1_) *
                  std::max(static_cast<types::f77_integer>(0), size2_) *
                  std::max(static_cast<types::f77_integer>(0), size3_);
      allocate();
    }
    // ... allow for local arrays in wrappers

    // lead, second and third dimensions of multi-dimensional arrays ...
    types::f77_integer get_LD(types::f77_integer sorder,
                              types::f77_integer min_ld = 0) const {
      types::f77_integer ld = 0;
      if (ndims == 2) {
        if (sorder == constants::NAG_ED_COL_MAJOR) {
          return std::max(size1.value, min_ld);
        } else {
          return std::max(size2.value, min_ld);
        }
      } else if (ndims == 3) {
        if (sorder == constants::NAG_ED_COL_MAJOR) {
          return std::max(size1.value, min_ld);
        } else {
          return std::max(size3.value, min_ld);
        }
      }
      return ld;
    }
    types::f77_integer get_SD(types::f77_integer sorder) const {
      types::f77_integer sd = 0;
      if (ndims == 2) {
        if (sorder == constants::NAG_ED_COL_MAJOR) {
          sd = size2.value;
        } else {
          sd = size1.value;
        }
      } else if (ndims == 3) {
        sd = size2.value;
      }
      return sd;
    }
    types::f77_integer get_TD(types::f77_integer sorder) const {
      types::f77_integer td = 0;
      if (ndims == 3) {
        if (sorder == constants::NAG_ED_COL_MAJOR) {
          td = size3.value;
        } else {
          td = size1.value;
        }
      }
      return td;
    }
    // ... lead, second and third dimensions of multi-dimensional arrays

    // check that the raw data is of the expected size ...
    void check(error_handler::ErrorHandler &error_handler,
               const std::string &argname, bool must_be_supplied,
               types::f77_integer esize) const {
      if (data) {
        error_handler.is_error_array_size(argname, ndims, size1, esize);
      } else if (must_be_supplied) {
        error_handler.raise_error_array_null(argname);
      }
    }
    void check(error_handler::ErrorHandler &error_handler,
               const std::string &argname, bool must_be_supplied,
               types::f77_integer esorder, types::f77_integer esize1,
               types::f77_integer esize2) const {
      if (data) {
        error_handler.is_error_array_size(argname, ndims, size1, esize1, size2,
                                          esize2);
        if (!error_handler.error_thrown && is_col_major.set) {
          types::f77_integer this_sorder = set_sorder(is_col_major.value);
          if (this_sorder != esorder) {
            error_handler.raise_error_array_sorder(argname, esorder,
                                                   this_sorder);
          }
        }
      } else if (must_be_supplied) {
        error_handler.raise_error_array_null(argname);
      }
    }
    void check(error_handler::ErrorHandler &error_handler,
               const std::string &argname, bool must_be_supplied,
               types::f77_integer esorder, types::f77_integer esize1,
               types::f77_integer esize2, types::f77_integer esize3) const {
      if (data) {
        error_handler.is_error_array_size(argname, ndims, size1, esize1, size2,
                                          esize2, size3, esize3);
        if (!error_handler.error_thrown && is_col_major.set) {
          types::f77_integer this_sorder = set_sorder(is_col_major.value);
          if (this_sorder != esorder) {
            error_handler.raise_error_array_sorder(argname, esorder,
                                                   this_sorder);
          }
        }
      } else if (must_be_supplied) {
        error_handler.raise_error_array_null(argname);
      }
    }
    // ... check that the raw data is of the expected size

    // element access, via indices ...
    // this does no bounds checking
    template <typename IT1>
    inline CRT &operator[](const IT1 i) const {
      return data[i];
    }
    template <typename IT1>
    inline CRT &operator()(const IT1 i) const {
      return data[i];
    }
    template <typename IT1, typename IT2>
    inline CRT &operator()(const IT1 i, const IT2 j) const {
      bool this_col_major;
      if (is_col_major.set) {
        this_col_major = is_col_major.value;
      } else {
        this_col_major = col_major_is_default;
      }
      if (this_col_major) {
        return data[j * size1.value + i];
      } else {
        return data[i * size2.value + j];
      }
    }
    template <typename IT1, typename IT2, typename IT3>
    inline CRT &operator()(const IT1 i, const IT2 j, const IT3 k) const {
      bool this_col_major;
      if (is_col_major.set) {
        this_col_major = is_col_major.value;
      } else {
        this_col_major = col_major_is_default;
      }
      if (this_col_major) {
        return data[k * (size1.value * size2.value) + j * size1.value + i];
      } else {
        return data[i * (size3.value * size2.value) + j * size3.value + k];
      }
    }
    // ... element access, via indices

    void set_default_storage(bool col_major_is_default_) {
      col_major_is_default = col_major_is_default_;
    }

    template <typename RD>
    friend void get_size(bool &all_null, bool &set, types::f77_integer &size,
                         const RD &raw_data, int dimno);
    template <typename RD>
    friend void get_storage_order(bool &set, types::f77_integer &sorder,
                                  const RD &raw_data);
  };

  // static functions that used to obtain aggregate information from multiple BaseRawDatas ...

  // return the storage order a wrapper will be using ...
  // this is defined either as the first explicit storage order supplied
  // in a BaseRawData, or the default if no explicit storage order is set
  template <typename RD>
  void get_storage_order(bool &set, types::f77_integer &sorder,
                         const RD &raw_data) {
    if (raw_data.is_col_major.set) {
      set = true;
      sorder = set_sorder(raw_data.is_col_major.value);
    }
  }
  template <typename RD, typename... Targs>
  void get_storage_order(bool &set, types::f77_integer &sorder,
                         const RD &raw_data, const Targs &... Fargs) {
    get_storage_order(set, sorder, raw_data);
    if (!set) {
      get_storage_order(set, sorder, Fargs...);
    }
  }
  template <typename... Targs>
  types::f77_integer get_storage_order(bool default_to_col_major,
                                       const Targs &... Fargs) {
    bool set = false;
    types::f77_integer sorder = set_sorder(default_to_col_major);
    get_storage_order(set, sorder, Fargs...);
    return sorder;
  }
  // ... return the storage order a wrapper will be using

  // get the size from series of BaseRawDatas ...
  template <typename RD>
  void get_size(bool &all_null, bool &set, types::f77_integer &size,
                const RD &raw_data, int dimno) {

    int ndims = (!raw_data.ndims.set) ? raw_data.ndims.value : 99;
    if (raw_data.data) {
      all_null = false;
      if (dimno == 1) {
        if (raw_data.size1.set) {
          set = true;
          size = static_cast<types::f77_integer>(raw_data.size1.value);
        }
      } else if (dimno == 2 && ndims >= 2) {
        if (raw_data.size2.set) {
          set = true;
          size = static_cast<types::f77_integer>(raw_data.size2.value);
        }
      } else {
        if (raw_data.size3.set && ndims >= 3) {
          set = true;
          size = static_cast<types::f77_integer>(raw_data.size3.value);
        }
      }
    }
  }
  template <typename RD, typename... Targs>
  void get_size(bool &all_null, bool &set, types::f77_integer &size,
                const RD &raw_data, int dimno, const Targs &... Fargs) {
    get_size(all_null, set, size, raw_data, dimno);

    if (!set) {
      get_size(all_null, set, size, Fargs...);
    }
  }

  template <typename... Targs>
  types::f77_integer get_size(error_handler::ErrorHandler &error_handler,
                              const std::string &argname,
                              const Targs &... Fargs) {
    // return the size of an array, the function expects pairs of values
    // as Fargs
    // raw_data_1, dimno_1, raw_data_2, dimno_2
    // etc
    // the size is taken from dimension dimno_n of array container
    // raw_data_n, if that is not present it moves on to n+1
    // the size is taken from the first array container it can
    // if all arrays are null, then size of zero is assumed
    // an error is thrown if all arrays are not null and the size isn't found
    bool set = false;
    bool all_null = true;
    types::f77_integer size = 0;
    error_handler.reset();

    get_size(all_null, set, size, Fargs...);
    if (!set && !all_null) {
      error_handler.raise_error_no_size_info(argname);
    }
    return size;
  }
  // ... get the size from series of BaseRawDatas

  // ... static functions that used to obtain aggregate information from multiple BaseRawDatas

  // code to convert NAG array types to user types ...

  // each user types needs a specialization of this template ...
  // (unless it contains the default methods - in which case the
  // default template in nagcpp_data_handling_default will do)
  template <typename NAT, enum ArgIntent inout, typename UAT>
  struct convert_nag_array_to_user_t;
  // ... each user types needs a specialization of this template

  template <typename NAT, enum ArgIntent inout, typename UAT>
  auto convert_nag_array_to_user(NAT &nag_array) -> decltype(
    convert_nag_array_to_user_t<
      NAT, inout,
      typename std::remove_const<
        typename std::remove_reference<UAT>::type>::type>::get(nag_array)) {
    return convert_nag_array_to_user_t<
      NAT, inout,
      typename std::remove_const<
        typename std::remove_reference<UAT>::type>::type>::get(nag_array);
  }

  // handle case of a NAG array to NAG array conversion ...
  // (i.e. user is using the NAG arrays in their callback)

  // saves reference to object passed to the constructor
  // returns it back via the get method
  template <typename NAT>
  class nag_array_to_nag_array {
  private:
    NAT &nag_array;

  public:
    nag_array_to_nag_array(NAT &nag_array_) : nag_array(nag_array_) {}
    NAT &get(void) { return nag_array; }
  };

  template <typename NAT, enum ArgIntent inout, typename UAT>
  struct convert_nag_array_to_user_t {
    static nag_array_to_nag_array<NAT> get(NAT &nag_array){
      return nag_array_to_nag_array<NAT>(nag_array);}
};
// ... handle case of a NAG array to NAG array conversion

// ... code to convert NAG array types to user types
struct CallbackAddresses {
  void **address;
  CallbackAddresses(size_t n) { address = new void *[n]; }
  ~CallbackAddresses() { delete[] address; }
};
}
}
#endif
