// unit tests for code in iomanager
// see also ut_iomanager_through_engine.cpp
#include "include/cxxunit_testing.hpp"
#include "utility/nagcpp_iomanager.hpp"
#include <iostream>
#include <sstream>
#include <string>

// XXX CURRENTLY THIS DOES NOT TEST THE ADVISORY / ERROR UNITS:
//   register_to_advisory_message_unit
//   reset_advisory_message_unit
//   register_to_error_message_unit
//   reset_error_message_unit
//  b) need to test work through a routine
//  c) need to test can override global iomanager with local iomanager
//  d) need to test can supply own iomanager class

using namespace nagcpp;

struct test_with_ostream : public TestCase {
  void run() override {
    {
      SUB_TITLE("local IOManager : string stream (IO)");
      iomanager::IOManager io;
      std::stringstream this_stream;
      run_this(io, this_stream);
    }
    {
      SUB_TITLE("local IOManager : string stream (O)");
      iomanager::IOManager io;
      std::stringstream this_stream(std::ios::out);
      run_this(io, this_stream);
    }
    {
      SUB_TITLE("global IOManager: string stream (IO)");
      std::stringstream this_stream;
      run_this(*iomanager::GLOBAL_IOMANAGER, this_stream);
    }
    {
      SUB_TITLE("global IOManager: string stream (O)");
      std::stringstream this_stream(std::ios::out);
      run_this(*iomanager::GLOBAL_IOMANAGER, this_stream);
    }
  }

  template <typename IO, typename STREAM>
  void run_this(IO &io, STREAM &this_stream) {
    {
      types::f77_integer nout = io.register_ostream(this_stream);
      {
        SUB_TEST("unit_from_ostream ties up with unit returned by constructor");
        types::f77_integer query_nout1 = io.unit_from_ostream(this_stream);
        ASSERT_EQUAL(nout, query_nout1);
        ASSERT_NOT_EQUAL(query_nout1, 0);
      }
      {
        SUB_TEST("register the same stream twice, should get the same unit "
                 "number back");
        types::f77_integer query_nout2 = io.register_ostream(this_stream);
        ASSERT_EQUAL(nout, query_nout2);
      }
      {
        SUB_TEST("check stream not registered as an istream");
        types::f77_integer query_nout3 = io.unit_from_istream(this_stream);
        ASSERT_EQUAL(query_nout3, 0);
      }
      {
        SUB_TEST("check print_rec works");
        io.print_rec(nout, "HELLO THERE");
        io.print_rec(nout, "HOW ARE THINGS");
        // NB: print_rec adds a new line after each call
        ASSERT_MULTI_LINE_STRING_EQUAL(this_stream.str(),
                                       std::string("HELLO THERE\nHOW ARE "
                                                   "THINGS\n"));
      }
      {
        SUB_TEST("call read_rec on an ostream");
        std::string out_str;
        ASSERT_THROWS(std::ios_base::failure, io.read_rec(nout, out_str));
        try {
          (void)io.read_rec(nout, out_str);
        } catch (const std::exception &e) {
          std::string error_msg = e.what();
          ASSERT_HAS_KEYWORD(error_msg, "No registered istream");
          ASSERT_HAS_KEYWORD(error_msg, "unit number " + std::to_string(nout));
        }
      }
      io.deregister_ostream(this_stream);
      {
        SUB_TEST("check deregister has removed the stream");
        types::f77_integer query_nout4 = io.unit_from_ostream(this_stream);
        ASSERT_EQUAL(query_nout4, 0);
      }
      {
        SUB_TEST("deregister a non-existent stream");
        ASSERT_THROWS_NOTHING(io.deregister_ostream(this_stream));
      }
      {
        SUB_TEST("call print_rec on a non-existent stream");
        ASSERT_THROWS(std::ios_base::failure, io.print_rec(nout, "THIS SHOULD "
                                                                 "FAIL"));
        try {
          io.print_rec(nout, "THIS SHOULD FAIL");
        } catch (const std::exception &e) {
          std::string error_msg = e.what();
          ASSERT_HAS_KEYWORD(error_msg, "No registered ostream");
          ASSERT_HAS_KEYWORD(error_msg, "unit number " + std::to_string(nout));
        }
      }
      types::f77_integer nout2 = io.register_ostream(this_stream);
      {
        SUB_TEST("check that after deregistering and re-registering print_rec "
                 "appends");
        types::f77_integer query_nout5 = io.unit_from_ostream(this_stream);
        // double check that the unit number has been set
        ASSERT_EQUAL(nout2, query_nout5);
        ASSERT_NOT_EQUAL(query_nout5, 0);

        io.print_rec(nout2, "ANOTHER LINE");
        ASSERT_MULTI_LINE_STRING_EQUAL(this_stream.str(),
                                       std::string("HELLO THERE\nHOW ARE "
                                                   "THINGS\nANOTHER LINE\n"));
      }
      {
        SUB_TEST("check that we can write directly to the stream");
        io.ostream_from_unit(nout2) << "- INJECTED DIRECT TEXT -";
        io.print_rec(nout2, "END");
        ASSERT_MULTI_LINE_STRING_EQUAL(this_stream.str(),
                                       std::string("HELLO THERE\nHOW ARE "
                                                   "THINGS\nANOTHER LINE\n- "
                                                   "INJECTED DIRECT TEXT "
                                                   "-END\n"));
      }
      {
        SUB_TEST("try and get stream from non-existent unit");
        ASSERT_THROWS(std::ios_base::failure, io.ostream_from_unit(999));
        types::f77_integer this_nout = 999;
        try {
          (void)io.ostream_from_unit(this_nout);
        } catch (const std::exception &e) {
          std::string error_msg = e.what();
          ASSERT_HAS_KEYWORD(error_msg, "No registered ostream");
          ASSERT_HAS_KEYWORD(error_msg,
                             "unit number " + std::to_string(this_nout));
        }
      }
      io.deregister_ostream(nout2);
      {
        SUB_TEST("check deregister by unit number has removed the stream");
        types::f77_integer query_nout6 = io.unit_from_ostream(this_stream);
        ASSERT_EQUAL(query_nout6, 0);
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_with_ostream, "Test functionality with ostream");
// clang-format on

struct test_with_istream : public TestCase {
  void run() override {
    std::string initial_value =
      "THIS IS LINE1\nAND THIS IS LINE2\nLINE3\nLINE4 IS NEXT\nLINE5 FOLLOWS "
      "ALONG\rNEXT BIT\r\nMORE\nAND MORE AND THEN SOME";
    {
      SUB_TITLE("local IOManager : string stream (IO)");
      iomanager::IOManager io;
      std::stringstream this_stream(initial_value);
      run_this(io, this_stream);
    }
    {
      SUB_TITLE("local IOManager : string stream (I)");
      iomanager::IOManager io;
      std::stringstream this_stream(initial_value, std::ios::in);
      run_this(io, this_stream);
    }
    {
      SUB_TITLE("global IOManager: string stream (IO)");
      std::stringstream this_stream(initial_value);
      run_this(*iomanager::GLOBAL_IOMANAGER, this_stream);
    }
    {
      SUB_TITLE("global IOManager: string stream (I)");
      std::stringstream this_stream(initial_value, std::ios::in);
      run_this(*iomanager::GLOBAL_IOMANAGER, this_stream);
    }
  }

  template <typename IO, typename STREAM>
  void run_this(IO &io, STREAM &this_stream) {
    {
      // NB: these tests will not pass if run out of sequence
      // as they involve sequential reads from this_stream
      types::f77_integer nin = io.register_istream(this_stream);
      {
        SUB_TEST("unit_from_istream ties up with unit returned by constructor");
        types::f77_integer query_nin1 = io.unit_from_istream(this_stream);
        ASSERT_EQUAL(nin, query_nin1);
        ASSERT_NOT_EQUAL(query_nin1, 0);
      }
      {
        SUB_TEST("register the same stream twice, should get the same unit "
                 "number back");
        types::f77_integer query_nin2 = io.register_istream(this_stream);
        ASSERT_EQUAL(nin, query_nin2);
      }
      {
        SUB_TEST("check stream not registered as an ostream");
        types::f77_integer query_nin3 = io.unit_from_ostream(this_stream);
        ASSERT_EQUAL(query_nin3, 0);
      }
      {
        SUB_TEST("check read_rec works");
        std::string line1;
        types::f77_integer nchar1 = io.read_rec(nin, line1);
        std::string line2;
        types::f77_integer nchar2 = io.read_rec(nin, line2);
        ASSERT_STRINGS_EQUAL(line1, std::string("THIS IS LINE1"));
        ASSERT_EQUAL(nchar1, 13);
        ASSERT_STRINGS_EQUAL(line2, std::string("AND THIS IS LINE2"));
        ASSERT_EQUAL(nchar2, 17);
      }
      {
        SUB_TEST("call print_rec on an ostream");
        ASSERT_THROWS(std::ios_base::failure, io.print_rec(nin, "HELLO"));
        try {
          io.print_rec(nin, "HELLO");
        } catch (const std::exception &e) {
          std::string error_msg = e.what();
          ASSERT_HAS_KEYWORD(error_msg, "No registered ostream");
          ASSERT_HAS_KEYWORD(error_msg, "unit number " + std::to_string(nin));
        }
      }
      io.deregister_istream(this_stream);
      {
        SUB_TEST("check deregister has removed the stream");
        types::f77_integer query_nin4 = io.unit_from_istream(this_stream);
        ASSERT_EQUAL(query_nin4, 0);
      }
      {
        SUB_TEST("deregister a non-existent stream");
        ASSERT_THROWS_NOTHING(io.deregister_istream(this_stream));
      }
      {
        SUB_TEST("call read_rec on a non-existent stream");
        std::string line;
        ASSERT_THROWS(std::ios_base::failure, io.read_rec(nin, line));
        try {
          (void)io.read_rec(nin, line);
        } catch (const std::exception &e) {
          std::string error_msg = e.what();
          ASSERT_HAS_KEYWORD(error_msg, "No registered istream");
          ASSERT_HAS_KEYWORD(error_msg, "unit number " + std::to_string(nin));
        }
      }
      types::f77_integer nin2 = io.register_istream(this_stream);
      {
        SUB_TEST("check that after deregistering and re-registering read_rec "
                 "continues to read");
        types::f77_integer query_nin5 = io.unit_from_istream(this_stream);
        // double check that the unit number has been set
        ASSERT_EQUAL(nin2, query_nin5);
        ASSERT_NOT_EQUAL(query_nin5, 0);

        std::string line3;
        types::f77_integer nchar = io.read_rec(nin2, line3);
        ASSERT_STRINGS_EQUAL(line3, std::string("LINE3"));
        ASSERT_EQUAL(nchar, 5);
      }
      {
        SUB_TEST("check reading a few characters at a time");
        std::string part1, part2, part3;
        types::f77_integer nchar1 = io.read_rec(nin2, part1, 7);
        types::f77_integer nchar2 = io.read_rec(nin2, part2, 10);
        types::f77_integer nchar3 = io.read_rec(nin2, part3, 8);
        ASSERT_STRINGS_EQUAL(part1, "LINE4 I");
        ASSERT_EQUAL(nchar1, 7);
        ASSERT_STRINGS_EQUAL(part2, "S NEXT\nLIN");
        // NB: the actual number of characters read should not include
        // carriage returns
        ASSERT_EQUAL(nchar2, 9);
        ASSERT_STRINGS_EQUAL(part3, "E5 FOLLO");
        ASSERT_EQUAL(nchar3, 8);
      }
      {
        SUB_TEST("check CRLF and LF are behaving as expected");
        std::string part1, part2, part3;
        types::f77_integer nchar1 = io.read_rec(nin2, part1, 13);
        types::f77_integer nchar2 = io.read_rec(nin2, part2, 15);
        ASSERT_STRINGS_EQUAL(part1, "WS ALONG\nNEXT");
        ASSERT_EQUAL(nchar1, 12);
        ASSERT_STRINGS_EQUAL(part2, " BIT\nMORE\nAND M");
        ASSERT_EQUAL(nchar2, 13);
      }
      {
        SUB_TEST("check that we can read directly from the stream");
        std::string part1;
        std::string part2;
        io.istream_from_unit(nin2) >> part1;
        types::f77_integer nchar = io.read_rec(nin2, part2);
        ASSERT_STRINGS_EQUAL(part1, "ORE");
        ASSERT_STRINGS_EQUAL(part2, " AND THEN SOME");
        ASSERT_EQUAL(nchar, 14);
      }
      {
        SUB_TEST("try and get stream from non-existent unit");
        ASSERT_THROWS(std::ios_base::failure, io.istream_from_unit(999));
        types::f77_integer this_nin = 999;
        try {
          (void)io.istream_from_unit(this_nin);
        } catch (const std::exception &e) {
          std::string error_msg = e.what();
          ASSERT_HAS_KEYWORD(error_msg, "No registered istream");
          ASSERT_HAS_KEYWORD(error_msg,
                             "unit number " + std::to_string(this_nin));
        }
      }
      io.deregister_istream(nin2);
      {
        SUB_TEST("check deregister by unit number has removed the stream");
        types::f77_integer query_nin6 = io.unit_from_istream(this_stream);
        ASSERT_EQUAL(query_nin6, 0);
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_with_istream, "Test functionality with istream");
// clang-format on

struct test_compare_istream_ostream : public TestCase {
  void run() override {
    {
      SUB_TITLE("local IOManager");
      iomanager::IOManager io;
      run_this(io);
    }
    {
      SUB_TITLE("global IOManager");
      run_this(*iomanager::GLOBAL_IOMANAGER);
    }
  }
  template <typename IO>
  void run_this(IO &io) {
    {
      SUB_TEST("expect the unit numbers returned for istream and those for "
               "ostream to be in a different range");
      std::stringstream this_stream;
      types::f77_integer nin = io.register_istream(this_stream);
      types::f77_integer nout = io.register_ostream(this_stream);
      ASSERT_NOT_EQUAL(nin, nout);
    }
  }
};
// clang-format off
REGISTER_TEST(test_compare_istream_ostream, "Compare istream and ostream registration");
// clang-format on

struct test_lots_of_istreams : public TestCase {
  void run() override {
    {
      SUB_TITLE("local IOManager");
      iomanager::IOManager io;
      run_this(io);
    }
    {
      SUB_TITLE("global IOManager");
      run_this(*iomanager::GLOBAL_IOMANAGER);
    }
  }
  template <typename IO>
  void run_this(IO &io) {
    std::vector<types::f77_integer> unit_no;
    // want to keep both arrays of streams in the top scope
    std::vector<std::unique_ptr<std::stringstream>> streams;
    std::vector<std::unique_ptr<std::stringstream>> new_streams;
    {
      SUB_TEST("fill up the stream storage");
      try {
        for (size_t i = 0; i < 1000; ++i) {
          // create a stream to register
          streams.push_back(
            std::unique_ptr<std::stringstream>(new std::stringstream));

          // try and register the stream
          unit_no.push_back(io.register_ostream(*streams[i]));
        }
      } catch (error_handler::ErrorException &e) {
        std::string error_msg = e.what();
        ASSERT_HAS_KEYWORD(error_msg, "deregister some");
        ASSERT_HAS_KEYWORD(error_msg, "output");
      }
      ASSERT_THROWS(error_handler::ErrorException,
                    io.register_ostream(*(streams.back())));
    }
    {
      SUB_TEST("check that we can add new streams if we delete some old ones");
      std::vector<size_t> id_to_drop = {10, 2, 18, 17, 22};

      types::f77_integer prev_nout = -1;
      for (auto id : id_to_drop) {
        // create a new stream to register
        new_streams.push_back(
          std::unique_ptr<std::stringstream>(new std::stringstream));

        // drop an existing stream, based on its unit number
        types::f77_integer this_nout = unit_no[id];
        io.deregister_ostream(this_nout);

        // try adding the new stream
        types::f77_integer new_nout;
        try {
          new_nout = io.register_ostream(*(new_streams.back()));
        } catch (...) {
          ASSERT_THROWS_NOTHING(io.register_ostream(*(new_streams.back())));
          break;
        }

        // the only space available is the one we just vacated, so the nout's
        // should be the same
        ASSERT_EQUAL(new_nout, this_nout);
        // want to make sure that the nout's have changed
        ASSERT_NOT_EQUAL(prev_nout, this_nout);
        prev_nout = this_nout;
      }
    }
  }
};
// clang-format off
REGISTER_TEST(test_lots_of_istreams, "Test the class can cleanly handle lots of istreams");
// clang-format on
