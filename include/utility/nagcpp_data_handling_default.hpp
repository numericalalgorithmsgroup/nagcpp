#ifndef NAGCPP_DATA_HANDLING_DEFAULT_HPP
#define NAGCPP_DATA_HANDLING_DEFAULT_HPP

#include "nagcpp_data_handling_array_info.hpp"
#include "nagcpp_data_handling_base.hpp"
#include <type_traits>

// construct way of testing whether a class contains a method (with no
// arguments) DEFINE_HAS_METHOD0(aaa) would create a structure has_aaa that
// tests for the method T1 aaa(void) via (has_aaa<T1, int>()) which resolved to
// true if the method T1.aaa(void) exits the int is required to resolve template
// clashes
#define DEFINE_HAS_METHOD0(NAME)                        \
  template <typename T1, typename Arg>                  \
  static auto test_##NAME(int)                          \
    ->sfinae_true<decltype(std::declval<T1>().NAME())>; \
  template <typename T1, typename Arg>                  \
  static auto test_##NAME(long)->std::false_type;       \
  template <typename T1, typename Arg>                  \
  struct has_##NAME : public decltype(test_##NAME<T1, Arg>(0)) {};

namespace nagcpp {
  namespace data_handling {

    template <class>
    struct sfinae_true : public std::true_type {};
    // has size()
    DEFINE_HAS_METHOD0(size)
    // has size1()
    DEFINE_HAS_METHOD0(size1)
    // has size2()
    DEFINE_HAS_METHOD0(size2)
    // has size3()
    DEFINE_HAS_METHOD0(size3)
    // has is_col_major()
    DEFINE_HAS_METHOD0(is_col_major)
    // has data()
    DEFINE_HAS_METHOD0(data)
    // has ndims()
    DEFINE_HAS_METHOD0(ndims)

    // length of vector of class V ...
    // looks for V.size() first, then V.size1()
    template <typename V>
    inline auto getDim(V &v, int) -> array_info<decltype(v.size())> {
      return array_info<decltype(v.size())>(true, v.size());
    }
    template <typename V, typename D>
    inline auto getDim(V &v, D d) -> array_info<decltype(v.size1())> {
      return array_info<decltype(v.size1())>(true, v.size1());
    }
    template <typename V>
    inline auto getDim(V &v, long) -> array_info<types::f77_integer> {
      return array_info<types::f77_integer>(false);
    }
    // ... length of vector of class V

    // size of first dimension in multi-dimensional array of class M ...
    // looks for M.size1() first, then M.size()
    template <typename M>
    inline auto getDim1(M &m, int) -> array_info<decltype(m.size1())> {
      return array_info<decltype(m.size1())>(true, m.size1());
    }
    template <typename M, typename D>
    inline auto getDim1(M &m, D d) -> array_info<decltype(m.size())> {
      return array_info<decltype(m.size())>(true, m.size());
    }
    template <typename M>
    inline auto getDim1(M &m, long) -> array_info<types::f77_integer> {
      return array_info<types::f77_integer>(false);
    }
    // ... size of first dimension in multi-dimensional array of class M

    // size of second dimension in multi-dimensional array of class M ...
    template <typename M>
    inline auto getDim2(M &m, int) -> array_info<decltype(m.size2())> {
      return array_info<decltype(m.size2())>(true, m.size2());
    }
    template <typename M>
    inline auto getDim2(M &m, long) -> array_info<types::f77_integer> {
      return array_info<types::f77_integer>(false);
    }
    // ... size of second dimension in multi-dimensional array of class M

    // size of the third dimension in multi-dimensional array of class M ...
    template <typename M>
    inline auto getDim3(M &m, int) -> array_info<decltype(m.size3())> {
      return array_info<decltype(m.size3())>(true, m.size3());
    }
    template <typename M>
    inline auto getDim3(M &m, long) -> array_info<types::f77_integer> {
      return array_info<types::f77_integer>(false);
    }
    // ... size of the third dimension in multi-dimensional array of class M

    // number of dimensions in multi-dimensional array of class M ...
    template <typename M>
    inline auto getNDims(M &m, int) -> array_info<decltype(m.ndims())> {
      return array_info<decltype(m.ndims())>(true, m.ndims());
    }
    template <typename M>
    inline auto getNDims(M &m, long) -> array_info<types::f77_integer> {
      // use the presence of size1, size2 and size3 to ascertain
      // the number of dimensions
      auto d1 = getDim1(m, 0);
      types::f77_integer ndims = 0;
      if (d1.set) {
        ndims = 1;
        auto d2 = getDim2(m, 0);
        if (d2.set) {
          ndims = 2;
          auto d3 = getDim3(m, 0);
          if (d3.set) {
            ndims = 3;
          }
        }
      }
      return array_info<types::f77_integer>(d1.set, ndims);
    }
    // ... number of dimensions in multi-dimensional array of class M

    // storage order for multi-dimensional array of class M ...
    // returns NAG_ED_COL_MAJOR or NAG_ED_ROW_MAJOR
    template <typename M>
    inline auto getStorageOrder(M &m, int)
      -> array_info<decltype(m.is_col_major())> {
      array_info<decltype(m.is_col_major())> this_ans(true);
      this_ans.value = m.is_col_major();
      return this_ans;
    }
    template <typename M>
    inline auto getStorageOrder(M &m, long) -> array_info<bool> {
      return array_info<bool>(false);
    }
    // ... storage order for multi-dimensional array of class M

    // resize an array ...
    template <typename V>
    inline auto resize1D(V &v, types::size_type d1, int)
      -> decltype(v.resize(d1)) {
      return v.resize(d1);
    }
    template <typename V>
    inline auto resize1D(V &v, types::size_type d1, long) -> void {}

    template <typename V>
    inline auto resize2D(V &v, types::size_type d1, types::size_type d2, int)
      -> decltype(v.resize(d1, d2)) {
      return v.resize(d1, d2);
    }
    template <typename V>
    inline auto resize2D(V &v, types::size_type d1, types::size_type d2, long)
      -> void {}

    template <typename V>
    inline auto resize3D(V &v, types::size_type d1, types::size_type d2,
                         types::size_type d3, int)
      -> decltype(v.resize(d1, d2, d3)) {
      return v.resize(d1, d2, d3);
    }
    template <typename V>
    inline auto resize3D(V &v, types::size_type d1, types::size_type d2,
                         types::size_type d3, long) -> void {}
    // ... resize an array

    // pointer to the raw data of class V ...
    template <typename T, typename V>
    inline auto getData(V &v, int) -> decltype(v.data()) {
      return v.data();
    }
    template <typename T>
    inline auto getData(std::nullptr_t, long) -> T * {
      return nullptr;
    }
    template <typename T, typename V>
    inline auto getData(V &v, long) -> T * {
      return nullptr;
    }
    // ... pointer to the raw data of class V

    // default RawData class ...
    // RT   : type for the data pointer in BaseRawData
    //        currently expecting RT to be either double / types::f77_integer / complex / char
    //        or const double / const types::f77_integer etc
    // inout: whether the data is IN, OUT or INOUT (used to specialize the class)
    // AC   : users array container type (used to specialize the class)
    template <typename RT, enum ArgIntent inout, typename AC = std::nullptr_t>
    class RawData : public BaseRawData<RT, inout> {
      using CRT = typename add_const_if_in<RT, inout>::type;

    public:
      RawData() {}

      RawData(const AC &array_container) { get_data(array_container); }

      // allow for local arrays via constructor in wrappers ...
      // (this type of construction will only happen with AC
      // at its default - so only required in this default
      // version of RawData - not required for any specializations)
      RawData(types::f77_integer size1_) { this->allocate_local(size1_); }
      RawData(types::f77_integer size1_, types::f77_integer size2_) {
        this->allocate_local(size1_, size2_);
      }
      RawData(types::f77_integer size1_, types::f77_integer size2_,
              types::f77_integer size3_) {
        this->allocate_local(size1_, size2_, size3_);
      }
      // ... allow for local arrays via constructor in wrappers

      virtual ~RawData(void) {}

      void get_data(const AC &array_container) {
        // NB: getData requires the data method to be implemented, we
        // do not check that it is, i.e. using a static_assert with
        // has_data<AC, int> == true as the condition
        // because we want to allow arrays to be passed as nulltpr
        // in some circumstances - so checks for null data have
        // to be runtime and not compile time
        auto users_raw_data = getData<CRT>(array_container, 0);
        if (users_raw_data) {
          this->ndims = getNDims(array_container, 0);
          this->size1 = getDim1(array_container, 0);
          this->nelements = this->size1;
          if (this->ndims > 1) {
            this->size2 = getDim2(array_container, 0);
            auto sorder = getStorageOrder(array_container, 0);
            if (sorder.set) {
              this->is_col_major = sorder.value;
            }
            this->nelements *= this->size2;
            if (this->ndims > 2) {
              this->size3 = getDim3(array_container, 0);
              this->nelements *= this->size3;
            }
          }
          convert_to_rt(users_raw_data);
        }
      }

      // resize the array container ...
      // this should resize this->data, as opposed to array_container
      // (i.e. if there is a local array (in say this->ldata) and
      // this->data = this->ldata, then you need only resize this->ldata
      // you can save the resizing of the array_container until the
      // copy_back method is called
      void resize(AC &array_container, types::f77_integer size1_) {
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        resize1D(array_container, rn1, 0);
        // update the class to point to the resized array container
        this->get_data(array_container);
      }
      void resize(AC &array_container, types::f77_integer size1_,
                  types::f77_integer size2_) {
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        types::f77_integer rn2 = (size2_ < 0) ? 0 : size2_;
        resize2D(array_container, rn1, rn2, 0);
        // update the class to point to the resized array container
        this->get_data(array_container);
      }
      void resize(AC &array_container, types::f77_integer size1_,
                  types::f77_integer size2_, types::f77_integer size3_) {
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        types::f77_integer rn2 = (size2_ < 0) ? 0 : size2_;
        types::f77_integer rn3 = (size3_ < 0) ? 0 : size3_;
        resize3D(array_container, rn1, rn2, rn3, 0);
        // update the class to point to the resized array container
        this->get_data(array_container);
      }
      // ... resize the array container

      // copy data back into the users container
      template <typename DUMMY = void>
      auto copy_back(AC &array_container) ->
        typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {
        auto users_raw_data = getData<CRT>(array_container, 0);
        copy_back_and_cast(users_raw_data);
      }

      // resize output container and copy back data ...
      // (if no local copies of the data exist, i.e.
      // this->data = getData<CRT>(array_container, 0), then this
      // only works if the resize operation preserves contents when it
      // resizes the array_container
      template <typename DUMMY = void>
      auto copy_back(AC &array_container, types::f77_integer size1_) ->
        typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {
        // copyback into the full array container
        copy_back<DUMMY>(array_container);
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        resize1D(array_container, rn1, 0);
      }
      template <typename DUMMY = void>
      auto copy_back(AC &array_container, types::f77_integer size1_,
                     types::f77_integer size2_) ->
        typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {
        // copyback into the full array container
        copy_back<DUMMY>(array_container);
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        types::f77_integer rn2 = (size2_ < 0) ? 0 : size2_;
        resize2D(array_container, rn1, rn2, 0);
      }
      template <typename DUMMY = void>
      auto copy_back(AC &array_container, types::f77_integer size1_,
                     types::f77_integer size2_, types::f77_integer size3_) ->
        typename std::enable_if<!is_in<inout>::value, DUMMY>::type const {
        // copyback into the full array container
        copy_back<DUMMY>(array_container);
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        types::f77_integer rn2 = (size2_ < 0) ? 0 : size2_;
        types::f77_integer rn3 = (size3_ < 0) ? 0 : size3_;
        resize3D(array_container, rn1, rn2, rn3, 0);
      }
      // ... resize output container and copy back data

    private:
      void convert_to_rt(RT *const user_raw_data) {
        this->data = user_raw_data;
      }

      template <typename URT>
      void convert_to_rt(const URT *const user_raw_data) {
        if (this->nelements.set && user_raw_data) {
          this->allocate();
          for (types::f77_integer i = 0; i < this->nelements.value; i++) {
            this->ldata[i] = static_cast<URT>(user_raw_data[i]);
          }
        }
      }

      template <typename URT>
      void copy_back_and_cast(URT *const user_raw_data) const {
        if (this->allocated && user_raw_data) {
          for (types::f77_integer i = 0; i < this->nelements.value; i++) {
            user_raw_data[i] = static_cast<URT>(this->ldata[i]);
          }
        }
      }
    };
    // ... default RawData class

    // default StringRawData class ...
    // XXXXX WE NEED TO EXTEND THIS TO WORK WITH ARRAY1D AND UTILITIY::ARRAY2D
    // class for preparing character / string data for passing
    // to the engine
    // NB: the array of chars pointed to by data is NOT null terminated
    template <enum ArgIntent inout, typename AC = std::nullptr_t>
    class StringRawData : public BaseRawData<char, inout> {

    public:
      types::f77_charlen string_length;

    public:
      StringRawData(const std::string &str) {
        string_length = str.length();
        this->nelements = string_length;
        BaseRawData<char, inout>::allocate();
        std::memcpy(this->ldata, str.c_str(),
                    this->nelements.value * sizeof(char));
      }
      StringRawData(const types::f77_charlen length) {
        string_length = length;
        this->nelements = string_length;
        allocate();
      }
      StringRawData(const std::vector<std::string> &str,
                    const types::f77_charlen maxlen = -1) {
        // for a vector of strings, say {"123", "12345678", "12345"} and maxlen
        // = 10 creates a char array holding: '123         12345678  12345     '
        // (i.e. a char array of length 30, with the three different strings
        // evenly spaced along it). If maxlen is less than the maximum string
        // length the string is truncated, if maxlen is -ve then it is taken as
        // the maximum length of any supplied string
        if (maxlen < 0) {
          string_length = 0;
          for (std::vector<std::string>::const_iterator it = str.begin();
               it != str.end(); ++it) {
            types::f77_charlen this_length =
              static_cast<types::f77_charlen>((*it).length());
            string_length = std::max(string_length, this_length);
          }
        } else {
          string_length = maxlen;
        }
        this->ndims = 1;
        this->size1 = str.size();
        this->nelements = this->size1.value * string_length;
        allocate();

        char *pdata = this->ldata;
        for (std::vector<std::string>::const_iterator it = str.begin();
             it != str.end(); ++it) {
          types::f77_charlen this_length =
            static_cast<types::f77_charlen>((*it).length());
          this_length = std::min(this_length, string_length);
          std::memcpy(pdata, (*it).c_str(), this_length * sizeof(char));
          pdata += string_length;
        }
      }
      ~StringRawData() {}

      // resize the array container ...
      // this should resize this->data, as opposed to array_container
      // (i.e. if there is a local array (in say this->ldata) and
      // this->data = this->ldata, then you need only resize this->ldata
      // you can save the resizing of the array_container until the
      // copy_back method is called
      void resize(std::vector<std::string> &str, types::f77_integer size1_) {
        // resize the underlying array container
        types::f77_integer rn1 = (size1_ < 0) ? 0 : size1_;
        resize1D(str, rn1, 0);
        // update class to point to the resized array container
        this->get_data(str);
      }
      // ... resize the array container

      void copy_back(std::string &str) {
        copy_char_to_string(this->nelements.value, this->ldata, str);
      }
      void copy_back(std::vector<std::string> &str) {
        char *pdata = this->ldata;
        str.resize(this->size1.value);
        for (std::vector<std::string>::iterator it = str.begin();
             it != str.end(); ++it) {
          copy_char_to_string(string_length, pdata, (*it));
          pdata += string_length;
        }
      }

      // resize output container and copy back data ...
      void copy_back(std::vector<std::string> &str, types::f77_integer size1_) {
        resize(str, size1_);
        copy_back(str);
      }
      // ... resize output container and copy back data

    private:
      void allocate() {
        BaseRawData<char, inout>::allocate();
        memset(this->ldata, ' ', this->nelements.value * sizeof(char));
      }

      static void copy_char_to_string(std::size_t length,
                                      const char *const pdata,
                                      std::string &str) {
        std::size_t this_length = 0;
        for (std::size_t i = length - 1; i > 0; i--) {
          if (pdata[i] != ' ') {
            this_length = i + 1;
            break;
          }
        }

        str.resize(this_length);
        for (std::size_t i = 0; i < this_length; i++) {
          str[i] = pdata[i];
        }
      }
    };
    // ... default StringRawData class

  }
}
#endif
